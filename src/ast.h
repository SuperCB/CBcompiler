//
// Created by supercb on 22-6-20.
//
#pragma once

#include <cstdint>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>
#include "visitor.h"

#include "common.h"

class Decl;

class Func;

class Expr;

class Binary;


class Stmt {
public:
    virtual void Accept(StmtBaseVisitor *basevisitor) {};
};


class Expr {
public:
    int result;  // 保存解析出来的结果，typeck阶段计算它，后续用它
    Expr() : result(0) {};


    enum class ExprType {
        VOID,
        INT,
        POINT
    };

    ExprType type;

    virtual void Accept(ExprBaseVisitor *exprBaseVisitor) {};
};

// 操作符保存在Expr::tag中
class Binary : public Expr {
public:


    OpType optype;
    Expr *lhs;
    Expr *rhs;

    Binary(OpType optype_, Expr *lhs_, Expr *rhs_) : optype(optype_), lhs(lhs_), rhs(rhs_) {};

    virtual void Accept(ExprBaseVisitor *visitor) {
        visitor->Visit(this);
    };

//    ~Binary() {
//        delete lhs;
//        delete rhs;
//    }
};

class Index : public Expr {
public:
    std::string_view name;
    // dims为空时即是直接访问普通变量

    std::vector<Expr *> dims;

    Decl *decl;  // typeck前是nullptr，若typeck成功则非空

    Index() = default;

    Index(std::string_view name_, std::vector<Expr *> dims_) : name(name_), dims(dims_) {

    }


    void Accept(ExprBaseVisitor *visitor) {
        visitor->Visit(this);
    };

};

class IntConstant : public Expr {

private:


    //单例模式专用的析构函数
    class Deletor {
    public:
        ~Deletor() {
            if (IntConstant::ZERO != nullptr)
                delete IntConstant::ZERO;
        }
    };

    static Deletor deletor;
public:

    int val;

    IntConstant() = default;

    IntConstant(int val_) : val(val_) {};

    virtual void Accept(ExprBaseVisitor *visitor) {
        visitor->Visit(this);
    };

    static IntConstant *ZERO;
public:
    static IntConstant *getZero() {
        if (IntConstant::ZERO == nullptr) {
            IntConstant::ZERO = new IntConstant();
        }
        return IntConstant::ZERO;
    }

};




class Call : public Expr {
public:

    //这个Call感觉还是归到Stmt里比较好，但是TrivialCompiler的作者将它归到了Expr里面，
    //后面就不好改了

    std::string_view func;
    std::vector<Expr *> args;
    Func *f;  // typeck前是nullptr，若typeck成功则非空

    Call(std::string_view func_, std::vector<Expr *> args_) : func(func_), args(args_), f(nullptr) {}

    virtual void Accept(ExprBaseVisitor *visitor) {
        visitor->Visit(this);
    };

//    // do some simple preprocess in conclass or
//    explicit Call(std::string_view func, std::vector<Expr *> args, u32 line_no) :  func(func) {
//        // map some builtin function names
//        constexpr static std::pair<std::string_view, std::string_view> func_mapping[3]{
//                {"starttime", "_sysy_starttime"},
//                {"stoptime",  "_sysy_stoptime"},
//                {"putf",      "printf"}
//        };
//
//        for (auto [origin, replace]: func_mapping) {
//            if (func == origin) {
//                auto replace_func_name =
//                        "Function name replaced from " + std::string(func) + " to " + std::string(replace);
//                dbg(replace_func_name);
//                this->func = replace;
//            }
//        }
//
//        // modify parameters
//        if (this->func == "_sysy_starttime" || this->func == "_sysy_stoptime") {
//            // manually add line number as parameter
//            this->args.push_back(new ::IntConst{Tag::IntConst, 0, (i32) line_no});
//        } else {
//            this->args = std::move(args);
//        }
//    }

};

class InitList {
public:  // val1为nullptr时val2有效，逻辑上相当于std::variant<Expr *, std::vector<InitList>>，但是stl这一套实在是不好用

    Expr *single_val;  // nullable
    std::vector<InitList> vals;


    InitList() : single_val(nullptr) {};

    InitList(Expr *val1_, std::vector<InitList> val2_) : single_val(val1_), vals(std::move(val2_)) {};

//    ~InitList() {
//        delete val1;
//    }

};

class Value;

class Decl {
public:
    bool is_const;
    bool has_init;  // 配合init使用
    bool is_glob;
    std::string_view name;


    // 基本类型总是int，所以不记录，只记录数组维度
    // dims[0]可能是nullptr，当且仅当Decl用于Func::params，且参数形如int a[][10]时；其他情况下每个元素都非空
    // 经过typeck后，每个维度保存的result是包括它在内右边所有维度的乘积，例如int[2][3][4]就是{24, 12, 4}
    std::vector<Expr *> dims;
    InitList init;  // 配合has_init，逻辑上相当于std::optional<InitList>，但是stl这一套实在是不好用
    std::vector<Expr *> flatten_init;  // parse完后为空，typeck阶段填充，是完全展开+补0后的init

    // ast->ir阶段赋值，每个Decl拥有属于自己的Value，Value *的地址相等等价于指向同一个的变量
    // 一开始全局变量：GlobalRef，参数中的数组：ParamRef，参数中的int/局部变量：AllocaInst
    // 经过mem2reg后，参数和局部变量中的int将不再需要这个AllocaInst

    Value *value;

    bool is_param_array() const {
        return !dims.empty() && dims[0] == nullptr;
    }

    Decl()=default;
    Decl(bool is_const_, bool has_init_, bool is_glob_, std::string_view name_, std::vector<Expr *> dims_,
         InitList init_) :
            is_const(is_const_), has_init(has_init_), is_glob(is_glob_), name(name_), dims(dims_), init(init_) {}

//    ~Decl() {
//        for (auto item: dims)
//            delete item;
//    }
};


class Assign : public Stmt {
public:
    std::string_view id;
    std::vector<Expr *> dims;
    Expr *rhs;
    Decl *decl;  // typecheck的目的就是为了找到这个赋值语句的定义所在


    Assign(std::string_view id_, std::vector<Expr *> dims_, Expr *rhs_) : id(id_), dims(std::move(dims_)), rhs(rhs_) {

    };

//    ~Assign() {
//        delete rhs;
//        for (auto expr: dims) {
//            delete expr;
//        }
//    }
    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
};

class ExprStmt : public Stmt {

public:
    Expr *val;  // nullable，为空时就是一条分号
    ExprStmt(Expr *val_) : val(val_) {};


    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
//    ~ExprStmt() {
//        delete expr;
//    }
};

class DeclStmt : public Stmt {
public:
    std::vector<Decl> decls;  // 一条语句可以定义多个变量
    DeclStmt(std::vector<Decl> decls_) : decls(decls_) {}

    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
};

class Block : public Stmt {
public:
    std::vector<Stmt *> stmts;

    Block() = default;

    Block(std::vector<Stmt *> stmts_) : stmts(stmts_) {}

    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
};

class If : public Stmt {
public:
    Expr *cond;
    Stmt *on_true;
    Stmt *on_false;  // nullable
    If(Expr *cond_, Stmt *on_true_, Stmt *on_false_) : cond(cond_), on_true(on_true_), on_false(on_false_) {}

    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
//    ~If() {
//        delete cond;
//        delete on_true;
//        delete on_false;
//    }
};

class While : public Stmt {
public:
    Expr *cond;
    Stmt *body;

    While(Expr *cond_, Stmt *body_) : cond(cond_), body(body_) {}

    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
//
//    ~While() {
//        delete cond;
//        delete body;
//    }
};

class Break : public Stmt {
public:
// 因为Break和Continue不保存任何信息，用单例来节省一点内存
    static Break *INSTANCE;

    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
};


class Continue : public Stmt {
public:
    static Continue *INSTANCE;

    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
};




class Return : public Stmt {
public:
    Expr *expr;  // nullable
    Return(Expr *expr_) : expr(expr_) {}

    void Accept(StmtBaseVisitor *basevisitor) {
        basevisitor->Visit(this);
    };
};

class IrFunc;

class Func {
public:
    // 返回类型只能是int/void，因此只记录是否是int
    bool is_int;
    std::string_view name;
    // 只是用Decl来复用一下代码，其实不能算是Decl，is_const / is_glob / has_init总是false
    std::vector<Decl> params;
    Block body;

    Func() = default;
    Func(bool isInt_, const std::string_view &name_) : is_int(isInt_), name(name_) {}

    Func(bool is_int_, std::string_view name_, std::vector<Decl> params_, Block body_) :
            is_int(is_int_), name(name_), params(params_), body(body_) {}

    // ast->ir阶段赋值
    IrFunc *irfunc;

    // BUILTIN[8]是memset，这个下标在ssa.cpp会用到，修改时需要一并修改
    static Func BUILTIN[9];


};

class Program {
public:
    // 我并不想用variant的，把函数和变量放在两个vector里更好，这样做是为了记录相对位置关系
    std::vector<std::variant<Func, Decl>> func_or_decl;

    Program() {

    }

};


