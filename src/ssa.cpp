#include "ssa.h"

//#include "../casting.hpp"
#include "ast.h"
#include "ir.h"
#include <typeinfo>
#include "../include/dbg.h"
void SsaContext::convert_expr(Expr *expr) {

    ExprVisitor exprVisitor(this);

    expr->Accept(&exprVisitor);

}

Value *SsaContext::get_expr(Expr *expr) {
    ret_val = nullptr;
    convert_expr(expr);
    return ret_val;
}

void SsaContext::convert_stmt(Stmt *stmt) {
    StmtVisitor stmtVisitor(this);
    stmt->Accept(&stmtVisitor);
}


IrProgram *convert_ssa(Program &p) {
    IrProgram *ret = new IrProgram;
//    for (Func &builtin: Func::BUILTIN) {
//        IrFunc *func = new IrFunc;
//        func->builtin = true;
//        func->func = &builtin;
//        builtin.irfunc = func;
//        ret->func.insertAtEnd(func);
//    }
    for (auto &g: p.func_or_decl) {
        if (Func *f = std::get_if<0>(&g)) {
            IrFunc *func = new IrFunc;
            func->builtin = false;
            func->func = f;
            f->irfunc = func;
            ret->func.insertAtEnd(func);
        }
    }


    for (auto &g: p.func_or_decl) {
        if (Func *f = std::get_if<0>(&g)) {
            IrFunc *func = f->irfunc;
            BasicBlock *entryBB = new BasicBlock;
            func->bb.insertAtEnd(entryBB);

            // setup params
            for (auto &p: f->params) {
                if (p.dims.empty()) {
                    // alloca for each non-array param
                    auto inst = new AllocaInst(&p, entryBB);
                    p.value = inst;
                    // then copy param into it
                    new StoreInst(&p, inst, new ParamRef(&p), ConstValue::get(0), entryBB);
                } else {
                    // there is no need to alloca for array param
                    p.value = new ParamRef(&p);
                }
            }

            SsaContext ctx = {ret, func, entryBB};


            for (auto &stmt: f->body.stmts) {
                ctx.convert_stmt(stmt);
            }

            // add extra return statement to avoid undefined behavior
            if (!ctx.bb->valid()) {
                if (func->func->is_int) {
                    new ReturnInst(ConstValue::get(0), ctx.bb);
                } else {
                    new ReturnInst(nullptr, ctx.bb);
                }
            }

            for (BasicBlock *bb = func->bb.head; bb; bb = bb->next) {
                bb->pred.clear();
            }
            for (BasicBlock *bb = func->bb.head; bb; bb = bb->next) {
                for (BasicBlock *x: bb->succ()) {
                    if (x) x->pred.push_back(bb);
                }
            }
        } else {
            dbg("global");
            Decl *d = std::get_if<Decl>(&g);
            ret->glob_decl.push_back(d);
            d->value = new GlobalRef(d);
        }
    }
    return ret;
}


void StmtVisitor::Visit(Assign *x) {
    // evaluate dims first
    std::vector<Value *> dims;
    dims.reserve(x->dims.size());
    for (auto &expr: x->dims) {
        auto dim = ctx->get_expr(expr);
        dims.push_back(dim);
    }
    // rhs
    auto rhs = ctx->get_expr(x->rhs);

    if (x->dims.empty()) {
        new StoreInst(x->decl, x->decl->value, rhs, ConstValue::get(0), ctx->bb);
    } else {
        // all levels except last level, emit GetElementPtr
        auto last = x->decl->value;
        for (int i = 0; i < x->dims.size(); i++) {
            int size = i + 1 < x->decl->dims.size() ? x->decl->dims[i + 1]->result : 1;
            if (i + 1 < x->dims.size()) {
                auto inst = new GetElementPtrInst(x->decl, last, dims[i], size, ctx->bb);
                last = inst;
            } else {
                new StoreInst(x->decl, last, rhs, dims[i], ctx->bb);
            }
        }
    }
}

void StmtVisitor::Visit(If *x) {
    // 1. check `cond`
    // 2. branch to `then` or `else`
    // 3. jump to `end` at the end of `then` and `else`
    auto cond = ctx->get_expr(x->cond);
    BasicBlock *bb_then = new BasicBlock;
    BasicBlock *bb_else = new BasicBlock;
    BasicBlock *bb_end = new BasicBlock;
    ctx->func->bb.insertAtEnd(bb_then);
    ctx->func->bb.insertAtEnd(bb_else);
    ctx->func->bb.insertAtEnd(bb_end);

    new BranchInst(cond, bb_then, bb_else, ctx->bb);

    // then
    ctx->bb = bb_then;
    ctx->convert_stmt(x->on_true);
    // jump to end bb
    if (!ctx->bb->valid()) {
        new JumpInst(bb_end, ctx->bb);
    }
    // else
    ctx->bb = bb_else;
    if (x->on_false) {
        ctx->convert_stmt(x->on_false);
    }
    // jump to end bb
    if (!ctx->bb->valid()) {
        new JumpInst(bb_end, ctx->bb);
    }

    ctx->bb = bb_end;
}

void StmtVisitor::Visit(While *x) {
    // four bb:
    // cond1: loop or end
    // loop: cond2
    // cond2 : loop or end
    // end
    BasicBlock *bb_cond1 = new BasicBlock;
    BasicBlock *bb_loop = new BasicBlock;
    BasicBlock *bb_cond2 = new BasicBlock;
    BasicBlock *bb_end = new BasicBlock;
    ctx->func->bb.insertAtEnd(bb_cond1);
    ctx->func->bb.insertAtEnd(bb_loop);

    // jump to cond1 bb
    new JumpInst(bb_cond1, ctx->bb);

    // cond1
    ctx->bb = bb_cond1;
    auto cond = ctx->get_expr(x->cond);
    new BranchInst(cond, bb_loop, bb_end, ctx->bb);

    // loop
    ctx->bb = bb_loop;
    ctx->loop_stk.emplace_back(bb_cond2, bb_end);
    ctx->convert_stmt(x->body);
    ctx->loop_stk.pop_back();
    // jump to cond2 bb
    if (!ctx->bb->valid()) {
        new JumpInst(bb_cond2, ctx->bb);
    }

    // cond2
    ctx->func->bb.insertAtEnd(bb_cond2);
    ctx->bb = bb_cond2;
    cond = ctx->get_expr(x->cond);
    new BranchInst(cond, bb_loop, bb_end, ctx->bb);

    ctx->func->bb.insertAtEnd(bb_end);
    ctx->bb = bb_end;
}

void StmtVisitor::Visit(Block *x) {
    for (auto &stmt: x->stmts) {
        ctx->convert_stmt(stmt);

//这个优化似乎应该集成到pass里面去
        if (dynamic_cast<Continue *>(stmt) || dynamic_cast<Return *>(stmt) || dynamic_cast<Break *>(stmt))
            break;
    }
}

void StmtVisitor::Visit(Return *x) {
    if (x->expr) {
        auto value = ctx->get_expr(x->expr);

        new ReturnInst(value, ctx->bb);
    } else {
        new ReturnInst(nullptr, ctx->bb);
    }
}

void StmtVisitor::Visit(DeclStmt *x) {
    for (auto &decl: x->decls) {
        // local variables
        auto inst = new AllocaInst(&decl, ctx->bb);
        decl.value = inst;

        // handle init expr
        if (decl.has_init) {
            if (decl.init.single_val) {
                // assign variable to expr


                ctx->get_expr(decl.init.single_val);
                auto init = ctx->ret_val;

                new StoreInst(&decl, inst, init, ConstValue::get(0), ctx->bb);
            } else {
                // assign each element of flatten_init
                // heuristic: count how many elements are zero
                int num_zeros = 0;
                std::vector<Value *> values;
                values.reserve(decl.flatten_init.size());
                for (unsigned int i = 0; i < decl.flatten_init.size(); i++) {


                    ctx->get_expr(decl.flatten_init[i]);
                    Value *init = ctx->ret_val;

                    values.push_back(init);
                    if (auto x = dynamic_cast<ConstValue *>(init)) {
                        if (x->imm == 0) {
                            num_zeros++;
                        }
                    }
                }

                bool emit_memset = false;
//                if (num_zeros > 10) {
//                    emit_memset = true;
//                    auto call_inst = new CallInst(Func::BUILTIN[8].irfunc, ctx->bb);
//                    call_inst->args.reserve(3);
//                    // arr
//                    call_inst->args.emplace_back(inst, call_inst);
//                    // ch
//                    call_inst->args.emplace_back(ConstValue::get(0), call_inst);
//                    // count = num * 4
//                    call_inst->args.emplace_back(ConstValue::get(decl.dims[0]->result * 4), call_inst);
//                }

                for (unsigned int i = 0; i < decl.flatten_init.size(); i++) {
                    // skip safely
                    if (auto x = dynamic_cast<ConstValue *>(values[i])) {
                        if (emit_memset && x->imm == 0) {
                            continue;
                        }
                    }

                    new StoreInst(&decl, inst, values[i], ConstValue::get(i), ctx->bb);
                }
            }
        }
    }
}

void StmtVisitor::Visit(ExprStmt *x) {
    if (x->val) {
        ctx->get_expr(x->val);
    }
}

void ExprVisitor::Visit(Binary *x) {
    auto lhs = ctx->get_expr(x->lhs);


    if (x->optype == OpType::Mod) {
        auto rhs = ctx->get_expr(x->rhs);


        // a % b := a - b * a / b (ARM has no MOD instruction)
//        auto quotient = new BinaryInst(Value::optype::Div, lhs, rhs, ctx->bb);
//        auto multiple = new BinaryInst(Value::optype::Mul, rhs, quotient, ctx->bb);
//        auto remainder = new BinaryInst(Value::optype::Sub, lhs, multiple, ctx->bb);
//        return remainder;
    } else if (x->optype == OpType::And || x->optype == OpType::Or) {
        auto rhs_bb = new BasicBlock, after_bb = new BasicBlock;
        ctx->func->bb.insertAtEnd(rhs_bb);
        if (x->optype == OpType::And) {
            new BranchInst(lhs, rhs_bb, after_bb, ctx->bb);
        } else {
            auto inv = new BinaryInst(OpType::Eq, lhs, ConstValue::get(0), ctx->bb);
            new BranchInst(inv, rhs_bb, after_bb, ctx->bb);
        }
        // 这里需要pred的大小为2，真正维护pred在最后才做，可以保证是[当前bb, rhs的实际计算bb]的顺序
        // 注意rhs的实际计算bb不一定就是rhs_bb，因为rhs也可能是&& ||
        after_bb->pred.resize(2);
        ctx->bb = rhs_bb;
        auto rhs = ctx->get_expr(x->rhs);
        new JumpInst(after_bb, ctx->bb);
        ctx->func->bb.insertAtEnd(after_bb);
        ctx->bb = after_bb;
        auto inst = new PhiInst(ctx->bb);
        inst->incoming_values[0].set(lhs);
        inst->incoming_values[1].set(rhs);
        ctx->ret_val = inst;

    } else {
        auto rhs = ctx->get_expr(x->rhs);
        // happened to have same optype values
        auto inst = new BinaryInst(x->optype, lhs, rhs, ctx->bb);
        ctx->ret_val = inst;
    }
}

void ExprVisitor::Visit(Index *x) {
    // evalulate dims first
    std::vector<Value *> dims;
    dims.reserve(x->dims.size());
    for (auto &p: x->dims) {
        auto value = ctx->get_expr(p);
        dims.push_back(value);
    }

    if (x->dims.size() == x->decl->dims.size()) {
        // access to element
        if (x->dims.empty()) {
            // direct access
            auto inst = new LoadInst(x->decl, x->decl->value, ConstValue::get(0), ctx->bb);
            ctx->ret_val = inst;
        } else {
            // all levels except last level, emit GetElementPtr
            Value *val = x->decl->value;
            Instruction *res = nullptr;
            for (unsigned int i = 0; i < x->dims.size(); i++) {
                int size = i + 1 < x->decl->dims.size() ? x->decl->dims[i + 1]->result : 1;
                if (i + 1 < x->dims.size()) {
                    auto inst = new GetElementPtrInst(x->decl, val, dims[i], size, ctx->bb);
                    res = inst;
                    val = inst;
                } else {
                    auto inst = new LoadInst(x->decl, val, dims[i], ctx->bb);
                    res = inst;
                }
            }
            ctx->ret_val = res;

//            return res;
        }
    } else if (x->dims.size()) {
        // access to sub array
        // emit GetElementPtr for each level
        Value *val = x->decl->value;
        Instruction *res = nullptr;
        for (unsigned int i = 0; i < x->dims.size(); i++) {
            int size = i + 1 < x->decl->dims.size() ? x->decl->dims[i + 1]->result : 1;
            auto inst = new GetElementPtrInst(x->decl, val, dims[i], size, ctx->bb);
            res = inst;
            val = inst;
        }
        ctx->ret_val = res;
    } else {
        // access to array itself
        auto inst = new GetElementPtrInst(x->decl, x->decl->value, ConstValue::get(0), 0, ctx->bb);
        ctx->ret_val = inst;
    }
}

void ExprVisitor::Visit(Call *x) {
    // must evaluate args before calling
    std::vector<Value *> args;
    args.reserve(x->args.size());
    for (auto &p: x->args) {
        auto value = ctx->get_expr(p);

        args.push_back(value);
    }


    auto inst = new CallInst(x->f->irfunc, ctx->bb);

    // args
    inst->args.reserve(x->args.size());
    for (auto &value: args) {

        inst->args.emplace_back(value, inst);
    }
    ctx->ret_val = inst;
}

void ExprVisitor::Visit(IntConstant *x) {
    ctx->ret_val = ConstValue::get(x->val);
}