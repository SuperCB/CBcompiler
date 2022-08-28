//
// Created by supercb on 22-6-20.
//

#pragma once


#include <array>
#include <cassert>
#include <cstdint>
#include <map>
#include <set>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <fstream>
#include "visitor.h"
#include "common.h"
#include "ast.h"
#include <sstream>


class Func;

class Decl;

class Instruction;

class IrFunc;

class Use;

class MemPhiInst;

class BasicBlock;

class InstructionVisitor;


struct IrFunc {
    IrFunc *prev, *next;
    Func *func;


    ilist<BasicBlock> bb;
    // functions called by this function
    std::set<IrFunc *> callee_func;
    // functions calling this function
    std::set<IrFunc *> caller_func;


    bool builtin;
    bool load_global;
    // has_side_effect: 修改了全局变量/传入的数组参数，或者调用了has_side_effect的函数
    // no side effect函数的没有user的调用可以删除


    bool has_side_effect;
    bool can_inline;

    // pure函数的参数相同的调用可以删除
    bool pure() const { return !(load_global || has_side_effect); }

    // 将所有bb的vis置false
//    void clear_all_vis() {
//        for (BasicBlock *b = bb.head; b; b = b->next) b->vis = false;
//    }
};

struct IrProgram {
    ilist<IrFunc> func;
    std::vector<Decl *> glob_decl;

    friend std::ostream &operator<<(std::ostream &os, const IrProgram &dt);

    void printvalue(std::ostream &os, Value *x);
};


class Value {
public:
    ilist<Use> uses;

    void addUse(Use *u) { uses.insertAtEnd(u); }

    void killUse(Use *u) { uses.remove(u); }

    // 将对自身所有的使用替换成对v的使用
    inline void replaceAllUseWith(Value *v);

    // 调用deleteValue语义上相当于delete掉它，但是按照现在的实现不能直接delete它
    virtual void deleteValue() {};
//    virtual void Accept(){};

};

class Use {
public:
    Use *prev;
    Use *next;

    Value *value;
    Instruction *user;


    // 这个构造函数没有初始化prev和next，这没有关系
    // 因为prev和next永远不会从一个Use开始被主动使用，而是在遍历Use链表的时候用到
    // 而既然这个Use已经被加入了一个链表，它的prev和next也就已经被赋值了

    Use() : prev(nullptr), next(nullptr), value(nullptr), user(nullptr) {}

    Use(Value *v, Instruction *u) : value(v), user(u), prev(nullptr), next(nullptr) {

        if (v) v->addUse(this);
    }

    // 没有必要定义移动构造函数/拷贝运算符，语义没有区别
    // 一般不会用到它们，只在类似vector内部构造临时变量又析构的场景中用到
    Use(const Use &rhs) : value(rhs.value), user(rhs.user), prev(rhs.prev), next(rhs.next) {
        if (value) value->addUse(this);
    }

    Use &operator=(const Use &rhs) {
        if (this != &rhs) {
            assert(user == rhs.user);
            set(rhs.value);
        }
        return *this;
    }

    // 注意不要写.value = xxx, 而是用.set(xxx), 因为需要记录被use的关系
    void set(Value *v) {
        if (value) value->killUse(this);
        value = v;
        if (v) v->addUse(this);
    }


    ~Use() {
        if (value) value->killUse(this);
    }
};

void Value::replaceAllUseWith(Value *v) {
    // head->set会将head从链表中移除
    while (uses.head) uses.head->set(v);
}

class Module {
    ilist<IrFunc> func;
    std::vector<Decl *> glob_decl;

//    friend std::ostream &operator<<(std::ostream &os, const IrProgram &dt);
};


class BasicBlock : public Value {
public:
    BasicBlock *prev;
    BasicBlock *next;

    std::vector<BasicBlock *> pred;
    BasicBlock *idom;
    std::unordered_set<BasicBlock *> dom_by;  // 支配它的节点集
    std::vector<BasicBlock *> doms;           // 它支配的节点集
    uint dom_level;                            // dom树中的深度，根深度为0
    bool vis;  // 各种算法中用到，标记是否访问过，算法开头应把所有vis置false(调用IrFunc::clear_all_vis)
    ilist<Instruction> insts;
    ilist<Instruction> mem_phis;  // 元素都是MemPhiInst

    inline std::array<BasicBlock *, 2> succ();

    inline std::array<BasicBlock **, 2> succ_ref();  // 想修改succ时使用
    inline bool valid();
};


class ConstValue : public Value {

    static std::unordered_map<int, ConstValue *> POOL;

public:
    static ConstValue *get(int imm) {
        auto [it, inserted] = POOL.insert({imm, nullptr});
        if (inserted) it->second = new ConstValue(imm);
        return it->second;
    }

    const int imm;
private:
    // use ConstValue::get instead
    explicit ConstValue(int imm) : Value(), imm(imm) {}


};


class GlobalRef : public Value {
public:
    Decl *decl;

    GlobalRef(Decl *decl) : Value(), decl(decl) {}
};

class ParamRef : public Value {

public:
    ParamRef(Decl *decl) : Value(), decl(decl) {}

    Decl *decl;
};

class UndefValue : Value {

    UndefValue() : Value() {}

    // 这是一个全局可变变量，不过反正也不涉及多线程，不会有冲突
    static UndefValue INSTANCE;
};


class Instruction : public Value {
    // inclass ion linked list
    // basic block
public:
    BasicBlock *bb;
    Instruction *prev, *next;

    // insert this inst before `insertBefore`
    Instruction(Instruction *insertBefore) : Value(), bb(insertBefore->bb) {
        bb->insts.insertBefore(this, insertBefore);
    }

    // insert this inst at the end of `insertAtEnd`
    Instruction(BasicBlock *insertAtEnd) : Value(), bb(insertAtEnd) { bb->insts.insertAtEnd(this); }

    // 只初始化tag，没有加入到链表中，调用者手动加入
    Instruction() : Value() {}

    // 返回的指针对是一个左闭右开区间，表示这条指令的所有操作数，.value可能为空
    std::pair<Use *, Use *> operands();

    inline bool has_side_effect();

    virtual void Accept(InstructionVisitor *v) {};
};

class BinaryInst : public Instruction {
public:
    // operands
    // loop unroll pass里用到了lhs和rhs的摆放顺序，不要随便修改



    OpType optype;
    Use lhs;
    Use rhs;

    BinaryInst(OpType optype_, Value *lhs, Value *rhs, BasicBlock *insertAtEnd)
            : optype(optype_), Instruction(insertAtEnd), lhs(lhs, this), rhs(rhs, this) {}

    BinaryInst(OpType optype_, Value *lhs, Value *rhs, Instruction *insertBefore)
            : optype(optype_), Instruction(insertBefore), lhs(lhs, this), rhs(rhs, this) {}

//    bool rhsCanBeImm() {
//        // Add, Sub, Rsb, Mul, Div, Mod, Lt, Le, Ge, Gt, Eq, Ne, And, Or
//        return (tag >= Tag::Add && tag <= Tag::Rsb) || (tag >= Tag::Lt && tag <= Tag::Or);
//    }
    void Accept(InstructionVisitor *x) override;

    constexpr static const char *LLVM_OPS[14] = {
            /* Add = */ "add",
            /* Sub = */ "sub",
            /* Mul = */ "mul",
            /* Div = */ "sdiv",
            /* Mod = */ "srem",
            /* Lt = */ "icmp slt",
            /* Le = */ "icmp sle",
            /* Ge = */ "icmp sge",
            /* Gt = */ "icmp sgt",
            /* Eq = */ "icmp eq",
            /* Ne = */ "icmp ne",
            /* And = */ "and",
            /* Or = */ "or",
    };

//    constexpr static std::pair<Tag, Tag> swapableOperators[11] = {
//            {Tag::Add, Tag::Add},
//            {Tag::Sub, Tag::Rsb},
//            {Tag::Mul, Tag::Mul},
//            {Tag::Lt,  Tag::Gt},
//            {Tag::Le,  Tag::Ge},
//            {Tag::Gt,  Tag::Lt},
//            {Tag::Ge,  Tag::Le},
//            {Tag::Eq,  Tag::Eq},
//            {Tag::Ne,  Tag::Ne},
//            {Tag::And, Tag::And},
//            {Tag::Or,  Tag::Or},
//    };

//    bool swapOperand() {
//        for (auto [before, after]: swapableOperators) {
//            if (tag == before) {
//                // note:
//                // Use是被pin在内存中的，不能直接swap它们。如果未来希望这样做，需要实现配套的设施，基本上就是把下面的逻辑在构造函数/拷贝运算符中实现
//                tag = after;
//                Value *l = lhs.value, *r = rhs.value;
//                l->killUse(&lhs);
//                r->killUse(&rhs);
//                l->addUse(&rhs);
//                r->addUse(&lhs);
//                std::swap(lhs.value, rhs.value);
//                return true;
//            }
//        }
//        return false;
//    }
//
//    Value *optimizedValue() {
//        // imm on rhs
//        if (auto r = dyn_cast<ConstValue>(rhs.value)) {
//            switch (tag) {
//                case Tag::Add:
//                case Tag::Sub:
//                    return r->imm == 0 ? lhs.value : nullptr;  // ADD or SUB 0
//                case Tag::Mul:
//                    if (r->imm == 0) return ConstValue::get(0);  // MUL 0
//                    [[fallthrough]];
//                case Tag::Div:
//                    if (r->imm == 1) return lhs.value;  // MUL or DIV 1
//                case Tag::Mod:
//                    return r->imm == 1 ? ConstValue::get(0) : nullptr;  // MOD 1
//                case Tag::And:
//                    if (r->imm == 0) return ConstValue::get(0);  // AND 0
//                    return r->imm == 1 ? lhs.value : nullptr;    // AND 1
//                case Tag::Or:
//                    if (r->imm == 1) return ConstValue::get(1);  // OR 1
//                    return r->imm == 0 ? lhs.value : nullptr;    // OR 0
//                default:
//                    return nullptr;
//            }
//        }
//        return nullptr;
//    }
};

class BranchInst : Instruction {

public:
    BranchInst(Value *cond, BasicBlock *left, BasicBlock *right, BasicBlock *insertAtEnd)
            : Instruction(insertAtEnd), cond(cond, this), left(left), right(right) {}

    void Accept(InstructionVisitor *x) override;

// true
    BasicBlock *left;
// false
    BasicBlock *right;
    Use cond;
};

class JumpInst : Instruction {

public:
    JumpInst(BasicBlock *next, BasicBlock *insertAtEnd) : Instruction(insertAtEnd), next(next) {}

    void Accept(InstructionVisitor *x) override;

    BasicBlock *next;
};

class ReturnInst : public Instruction {
    Use ret;

public:
    ReturnInst(Value *ret_, BasicBlock *insertAtEnd) : Instruction(insertAtEnd), ret(ret_, this) {}

    void Accept(InstructionVisitor *x) override;

    friend InstructionVisitor;
};

class AccessInst : public Instruction {
public:
    Decl *lhs_sym;
    Use arr;
    Use index;

    AccessInst(Decl *lhs_sym, Value *arr, Value *index, BasicBlock *insertAtEnd)
            : Instruction(insertAtEnd), lhs_sym(lhs_sym), arr(arr, this), index(index, this) {}


};

class GetElementPtrInst : public AccessInst {
public:
    int multiplier;

    GetElementPtrInst(Decl *lhs_sym, Value *arr, Value *index, int multiplier, BasicBlock *insertAtEnd)
            : AccessInst(lhs_sym, arr, index, insertAtEnd), multiplier(multiplier) {}

    void Accept(InstructionVisitor *x) override;

};

class LoadInst : public AccessInst {
public:
    Use mem_token;  // 由memdep pass计算
    LoadInst(Decl *lhs_sym, Value *arr, Value *index, BasicBlock *insertAtEnd)
            : AccessInst(lhs_sym, arr, index, insertAtEnd), mem_token(nullptr, this) {}

    void Accept(InstructionVisitor *x) override;

};

class StoreInst : public AccessInst {
public:
    Use data;

    StoreInst(Decl *decl, Value *arr, Value *data, Value *index, BasicBlock *insertAtEnd)
            : AccessInst(decl, arr, index, insertAtEnd), data(data, this) {}

    void Accept(InstructionVisitor *x) override;

};

class CallInst : public Instruction {
public:
    IrFunc *func;
    std::vector<Use> args;

    CallInst(IrFunc *func, BasicBlock *insertAtEnd) : Instruction(insertAtEnd), func(func) {}

    void Accept(InstructionVisitor *x) override;

};

class AllocaInst : public Instruction {
public:

    Decl *sym;

    AllocaInst(Decl *sym, BasicBlock *insertBefore) : Instruction(insertBefore), sym(sym) {}

    void Accept(InstructionVisitor *x) override;

};

class PhiInst : public Instruction {
public:
//    DEFINE_CLASSOF(Value, p
//    ->tag == Tag::Phi);
    std::vector<Use> incoming_values;

    std::vector<BasicBlock *> &incoming_bbs() { return bb->pred; }

    explicit PhiInst(BasicBlock *insertAtFront) : Instruction() {
        bb = insertAtFront;
        bb->insts.insertAtBegin(this);
        unsigned int n = incoming_bbs().size();
        incoming_values.reserve(n);
        for (unsigned int i = 0; i < n; ++i) {
            // 在new PhiInst的时候还不知道它用到的value是什么，先填nullptr，后面再用Use::set填上
            incoming_values.emplace_back(nullptr, this);
        }
    }

    explicit PhiInst(Instruction *insertBefore) : Instruction(insertBefore) {
        unsigned int n = incoming_bbs().size();
        incoming_values.reserve(n);
        for (unsigned int i = 0; i < n; ++i) {
            incoming_values.emplace_back(nullptr, this);
        }
    }

    void Accept(InstructionVisitor *x) override;

};

//class MemOpInst : Instruction {
//public:
//    Use mem_token;
//    LoadInst *load;
//
//    MemOpInst(LoadInst *load, Instruction *insertBefore)
//            : Instruction(insertBefore), mem_token(nullptr, this), load(load) {}
//};
//
//// 它的前几个字段和PhiInst是兼容的，所以可以当成PhiInst用(也许理论上有隐患，但是实际上应该没有问题)
//// 我不希望让它继承PhiInst，这也许会影响以前的一些对PhiInst的使用
//class MemPhiInst : public Instruction {
//public:
//    std::vector<Use> incoming_values;
//
//    std::vector<BasicBlock *> &incoming_bbs() { return bb->pred; }
//
//    // load依赖store和store依赖load两种依赖用到的MemPhiInst不一样
//    // 前者的load_or_arr来自于load的数组地址，类型是Decl *，后者的load_or_arr来自于LoadInst
//    void *load_or_arr;
//
////    explicit MemPhiInst(void *load_or_arr, BasicBlock *insertAtFront) : Instruction(), load_or_arr(load_or_arr) {
////        bb = insertAtFront;
////        bb->mem_phis.insertAtBegin(this);
////        unsigned int n = incoming_bbs().size();
////        incoming_values.reserve(n);
////        for (unsigned int i = 0; i < n; ++i) {
////            incoming_values.emplace_back( this);
////        }
////    }
//};

//bool Instruction::has_side_effect() {
//    if (isa<BranchInst>(this) || isa<JumpInst>(this) || isa<ReturnInst>(this) || isa<StoreInst>(this)) return true;
//    if (auto x = dyn_cast<CallInst>(this); x && x->func->has_side_effect) return true;
//    return false;
//}

std::array<BasicBlock *, 2> BasicBlock::succ() {
    Instruction *end = insts.tail;  // 必须非空
    if (auto x = dynamic_cast<BranchInst *>(end))
        return {x->left, x->right};
    else if (auto x = dynamic_cast<JumpInst *>(end))
        return {x->next, nullptr};
    else if (auto x = dynamic_cast<ReturnInst *>(end))
        return {nullptr, nullptr};
    else {}
//        UNREACHABLE();
    return {nullptr, nullptr};
}

//std::array<BasicBlock **, 2> BasicBlock::succ_ref() {
//    Instruction *end = insts.tail;
//    if (auto x = dyn_cast<BranchInst>(end))
//        return {&x->left, &x->right};
//    else if (auto x = dyn_cast<JumpInst>(end))
//        return {&x->next, nullptr};
//    else if (isa<ReturnInst>(end))
//        return {nullptr, nullptr};
//    else
//        UNREACHABLE();
//}
//
bool BasicBlock::valid() {
    Instruction *end = insts.tail;
    return end && (dynamic_cast<BranchInst *>(end) || dynamic_cast<JumpInst *>(end) || dynamic_cast<ReturnInst *>(end));
}


class InstructionVisitor {
private:
    std::ostream &os;
    IndexMapper<Value> *v_index;
    std::map<BasicBlock *, u32> *bb_index;


public:

    InstructionVisitor(std::ostream &os, IndexMapper<Value> *vIndex, std::map<BasicBlock *, u32> *bbIndex) : os(os),
                                                                                                             v_index(vIndex),
                                                                                                             bb_index(
                                                                                                                     bbIndex) {}

    void Visit(LoadInst *x);

    void Visit(AllocaInst *x);

    void Visit(BinaryInst *x);

    void Visit(StoreInst *x);

    void Visit(ReturnInst *x);

    void Visit(GetElementPtrInst *x);

    void Visit(CallInst *x);

    void Visit(JumpInst *x);

    void Visit(PhiInst *x);

    void Visit(BranchInst *x);


//    void Visit(ConstValue *x);
//
//    void Visit(ParamRef *x);
//
//    void Visit(UndefValue *x);
//
//    void Visit(GlobalRef *x);

};


