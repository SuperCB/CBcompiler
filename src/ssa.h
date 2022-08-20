#pragma once

#include "ast.h"
#include "ir.h"

struct SsaContext {
    IrProgram *program;
    IrFunc *func;
    BasicBlock *bb;
    // bb stack for (continue, break)
    std::vector<std::pair<BasicBlock *, BasicBlock *>> loop_stk;
};

IrProgram *convert_ssa(Program &p);

class ExprVisitor {
public:
    void Visit(Expr *expr) {};
};


class StmtVisitor {
public:

    void Visit(Assign *assignst);

    void Visit(DeclStmt *declst);

    void Visit(Binary *binst);

    void Visit(If *ifst);

    void Visit(While *whilest);

    void Visit(Return *returnst);

    void Visit(ExprStmt *exprst);

    void Visit(Continue *continst);

    void Visit(Break *breakst);

};