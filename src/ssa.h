#pragma once

#include "ast.h"
#include "ir.h"
#include "visitor.h"

class SsaContext;

class ExprVisitor : public ExprBaseVisitor {

private:
    SsaContext *ctx;
public:

    explicit ExprVisitor(SsaContext *ctx_) : ctx(ctx_) {}

    void Visit(Binary *x);

    void Visit(Call *x);

    void Visit(Index *x);

    void Visit(IntConstant *x);
};


class StmtVisitor : public StmtBaseVisitor {
private:
    SsaContext *ctx;
public:
    explicit StmtVisitor(SsaContext *ctx_) : ctx(ctx_) {}

public:
    void Visit(Assign *x);

    void Visit(DeclStmt *x);

    void Visit(If *x);

    void Visit(While *x);

    void Visit(Return *x);

    void Visit(ExprStmt *x);

    void Visit(Continue *x) {};

    void Visit(Break *x) {};

    void Visit(Block *x);


};

class SsaContext {

public:



    Value *ret_val;

    void convert_stmt(Stmt *stmt);

    void convert_expr(Expr *expr);

    Value *get_expr(Expr *expr);

    SsaContext(IrProgram *program_, IrFunc *func_, BasicBlock *bb_) : program(program_), func(func_), bb(bb_) {}

    BasicBlock *bb;
private:
    IrProgram *program;
    IrFunc *func;
    // bb stack for (continue, break)
    std::vector<std::pair<BasicBlock *, BasicBlock *>> loop_stk;


//   if (isa<Continue>(stmt)) {
//        new JumpInst(ctx->loop_stk.back().first, ctx->bb);
//    } else if (isa<Break>(stmt)) {
//        new JumpInst(ctx->loop_stk.back().second, ctx->bb);
//    }
    friend StmtVisitor;
    friend ExprVisitor;
};

IrProgram *convert_ssa(Program &p);


