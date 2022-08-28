//
// Created by supercb on 22-8-24.
//

#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <variant>
#include "ir.h"
#include "ast.h"
#include "../include/dbg.h"
#include "visitor.h"

#define ERR(...) dbg(__VA_ARGS__)

// 有两种可能的符号：函数和变量，逻辑上需要一个variant<Func *, Decl *>，但是这太浪费空间了
// 这两种指针都至少是按4对齐的，所以最后两位不可能是1/2，就用这做discriminant
class SymContext;


class StmtTypecheckVisitor : public StmtBaseVisitor {
private:
    SymContext *context;

public:

    StmtTypecheckVisitor(SymContext *context_) : context(context_) {}

    void Visit(Assign *x) override;

    void Visit(DeclStmt *x) override;


    void Visit(If *x) override;

    void Visit(While *x) override;

    void Visit(Return *x) override;

    void Visit(ExprStmt *x) override;

    void Visit(Continue *continst) override;

    void Visit(Break *breakst) override;

    void Visit(Block *x) override;
};

class ExprTypecheckVisitor : public ExprBaseVisitor {

private:
    SymContext *context;

public:
    ExprTypecheckVisitor(SymContext *context_) : context(context_) {}

    void Visit(Binary *x) override;

    void Visit(Call *x) override;

    void Visit(Index *x) override;


    void Visit(IntConstant *x) override;

};

class SymContext {

private:
    class Deletor {
    public:
        ~Deletor() {
            if (SymContext::context != nullptr)
                delete SymContext::context;
        }
    };
    static Deletor deletor;
    using Symbol = std::variant<Func *, Decl *>;
    using uint = unsigned int;

// symtableal symbols
//存储全局函数与全局定义
    static SymContext *context;
public:




    std::unordered_map<std::string_view, Symbol> symtable;
// stacks of local decls
    std::vector<std::unordered_map<std::string_view, Decl *>> local_stk;

    Func *cur_func;

//用于检测不合规矩的循环语法
    uint loop_cnt;

    SymContext() = default;
    static SymContext *getOneInstance() {
        if (SymContext::context == nullptr) {
            SymContext::context = new SymContext();
        }
        return SymContext::context;
    }


    Func *lookup_func(std::string_view name) {
        auto res = symtable.find(name);
        if (res != symtable.end()) {
            if (Func *f = std::get<Func *>(res->second)) {
                return f;
            }
        }
        ERR("no such func", name);
    }

    Decl *lookup_decl(std::string_view name) {
        //如果能够在局部的定义域中找到相应的变量定义，就不需要继续查找全局变量定义
        for (auto it = local_stk.rbegin(), end = local_stk.rend(); it < end; ++it) {
            auto res = it->find(name);
            if (res != it->end()) {
                return res->second;
            }
        }

        auto res = symtable.find(name);
        if (res != symtable.end()) {
            if (Decl *d = std::get<Decl *>(res->second)) {
                return d;
            }
        }
        ERR("no such variable", name);
        return nullptr;
    }


    void check_func(Func *f) {
        cur_func = f;
        if (!symtable.insert({f->name, f}).second) {
            ERR("duplicate function", f->name);
        }
        local_stk.emplace_back();  // 参数作用域就是第一层局部变量的作用域
        for (Decl &d: f->params) {
            check_decl(d);
            if (!local_stk[0].insert({d.name, &d}).second) {
                ERR("duplicate param decl", d.name);
            }
        }
        for (Stmt *s: f->body.stmts) {
            check_stmt(s);
        }
        local_stk.pop_back();
    }

// 数组和标量的初始化都会以flatten_init的形式存储
// 即使没有初始化，全局变量也会以0初始化，而局部变量的flatten_init这时是空的
    void check_decl(Decl &d) {
        // 每个维度保存的result是包括它在内右边所有维度的乘积

        for (auto begin = d.dims.rbegin(), it = begin, end = d.dims.rend(); it < end; ++it) {
            Expr *e = *it;
            if (e) {  // 函数参数中dims[0]为nullptr
                const_eval(e);
                if (e->result < 0) {
                    ERR("array dim < 0");
                }

                if (it != begin) {
                    e->result *= it[-1]->result;
                }
            }
        }
        if (d.has_init) {
            if (d.dims.empty() && d.init.single_val) {  // 形如int x = 1
                check_expr(d.init.single_val);
                if (d.is_const || d.is_glob) {
                    const_eval(d.init.single_val);
                }
                d.flatten_init.push_back(d.init.single_val);
            } else if (!d.init.single_val) {  // 形如int x[1] = {}
                flatten_init(d.init.vals, d.dims.data(), d.dims.data() + d.dims.size(), d.is_const | d.is_glob,
                             d.flatten_init);
            } else {  // 另外两种搭配
                ERR("incompatible type and initialization");
            }
        } else if (d.is_const) {
            ERR("const decl has no initialization");
        } else if (d.is_glob) {
            d.flatten_init.resize(d.dims.empty() ? 1 : d.dims[0]->result, IntConstant::getZero());
        }
    }

    void check_stmt(Stmt *s) {
        StmtTypecheckVisitor stmtTypecheckVisitor(getOneInstance());
        s->Accept(&stmtTypecheckVisitor);
    }

// src应该都是没有eval过的；这里只处理必须是列表形式的src，不处理单独expr形式的
// [dims, dims_end)组成一个非空slice；dims应该符合Decl::dims的描述，且已经求值完毕
// flatten_init可以用于常量和非常量的初始化，由need_eval控制
    void flatten_init(std::vector<InitList> &src, Expr **dims, Expr **dims_end, bool need_eval,
                      std::vector<Expr *> &dst) {
        unsigned int elem_size = dims + 1 < dims_end ? dims[1]->result : 1, expect = dims[0]->result;
        unsigned cnt = 0, old_len = dst.size();
        for (InitList &l: src) {
            if (l.single_val) {
                check_expr(l.single_val);
                if (need_eval) {
                    const_eval(l.single_val);
                }
                dst.push_back(l.single_val);
                if (++cnt == elem_size) {
                    cnt = 0;
                }
            } else {
                // 遇到了一个新的列表，它必须恰好填充一个元素
                // 给前一个未填满的元素补0
                if (cnt != 0) {
                    dst.resize(dst.size() + elem_size - cnt, IntConstant::getZero());
                    cnt = 0;
                }
                if (dims < dims_end) {
                    flatten_init(l.vals, dims + 1, dims_end, need_eval, dst);
                } else {
                    ERR("initializer list has too many dimensions");
                }
            }
        }
        unsigned int actual = dst.size() - old_len;
        if (actual <= expect) {
            dst.resize(dst.size() + expect - actual, IntConstant::getZero());
        } else {
            ERR("too many initializing values", expect, actual);
        }
    }


    void check_expr(Expr *e) {
        ExprTypecheckVisitor exprTypecheckVisitor(getOneInstance());
        e->Accept(&exprTypecheckVisitor);

    }

// 能够成功eval的必然是int，所以eval中就不必检查操作数的类型
    void const_eval(Expr *e) {
        if (auto x = dynamic_cast<Binary *>(e)) {
            const_eval(x->lhs), const_eval(x->rhs);
            x->result = binary_eval(x->optype, x->lhs->result, x->rhs->result);


        } else if (auto x = dynamic_cast<Call *>(e)) {
            // 常量表达式中不能包含函数调用
            ERR("function call in const expression");
        } else if (auto x = dynamic_cast<Index *>(e)) {


            Decl *d = lookup_decl(x->name);
            if (!d->is_const) {
                ERR("non-constant variable", x->name, "used in constant expr");
            }
            // 常量表达式中必须完全解引用数组
            if (d->dims.size() != x->dims.size()) {
                ERR("index expression array dim mismatch");
            }
            unsigned int off = 0;
            // 因为没有保存每个维度的长度，所以没法在每一个下标处都检查了，不过这也没什么关系
            for (unsigned int i = 0, end = x->dims.size(); i < end; ++i) {
                Expr *idx = x->dims[i];
                const_eval(idx);
                off += (i + 1 == end ? 1 : d->dims[i + 1]->result) * idx->result;
            }
            if (off >= d->flatten_init.size()) {
                ERR("constant index out of range");
            }
            x->result = d->flatten_init[off]->result;
        } else if (auto x = dynamic_cast<IntConstant *>(e)) {
            e->result = x->val;
        } else {
//            UNREACHABLE();
        }
    }


//    eval(OpType op, int l, int r)
    int binary_eval(OpType op, int l, int r) {
        switch (op) {
            case OpType::Add:
                return l + r;
            case OpType::Sub:
                return l - r;

            case OpType::Mul:
                return l * r;
                // 除0就随它去吧，反正我们对于错误都是直接退出的
            case OpType::Div:
                return l / r;
            case OpType::Mod:
                return l % r;
            case OpType::Lt:
                return l < r;
            case OpType::Le:
                return l <= r;
            case OpType::Ge:
                return l >= r;
            case OpType::Gt:
                return l > r;
            case OpType::Eq:
                return l == r;
            case OpType::Ne:
                return l != r;
            case OpType::And:
                return l && r;
            case OpType::Or:
                return l || r;
            default:

                break;
        }

        return 0;
    }


};





void type_check(Program &p);
