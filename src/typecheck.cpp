#include "typecheck.h"

void ExprTypecheckVisitor::Visit(Binary *x) {
    context->check_expr(x->lhs);
    context->check_expr(x->rhs);

    if (x->lhs->type != Expr::ExprType::INT && x->rhs->type != Expr::ExprType::INT) {
        ERR("binary operator expect int operands");
    }

}

void ExprTypecheckVisitor::Visit(IntConstant *x) {
    x->result = x->val;
    x->type = Expr::ExprType::INT;
}

void ExprTypecheckVisitor::Visit(Index *x) {
    // 这里允许不完全解引用数组
    Decl *d = context->lookup_decl(x->name);
    x->decl = d;
    if (x->dims.size() > d->dims.size()) {
        ERR("index operator expect array operand");
    }
    for (Expr *e: x->dims) {
        context->check_expr(e);
        if (e->type == Expr::ExprType::INT) {
            ERR("index operator expect int operand");
        }
    }
//    return d->dims.empty() ? empty : std::pair{d->dims.data() + x->dims.size(), d->dims.data() + d->dims.size()};
}

void ExprTypecheckVisitor::Visit(Call *x) {
    Func *f = context->lookup_func(x->func);
    x->f = f;
    if (f->params.size() != x->args.size()) {
        ERR("function call argc mismatch");
    }
    for (uint i = 0; i < x->args.size(); ++i) {
        context->check_expr(x->args[i]);
        std::vector<Expr *> &p = f->params[i].dims;
        // 跳过第一个维度的检查，因为函数参数的第一个维度为空
        bool ok = true;
        if (Index *indexPtr = dynamic_cast<Index *>(x)) {
            ok = (indexPtr->decl->dims.size() - indexPtr->dims.size()) == p.size();
            for (int j = 1, end = p.size(); ok && j < end; ++j) {
                if (indexPtr->decl->dims[indexPtr->dims.size() + j]->result != p[j]->result) {
                    ok = false;
                }
            }
        }
        if (!ok) {
            ERR("function call arg mismatch", f->name, i + 1, f->params[i].name);
        }
    }
}

void StmtTypecheckVisitor::Visit(Assign *x) {
    Decl *d = context->lookup_decl(x->id);
    x->decl = d;
    if (d->is_const) {
        ERR("can't assign to const decl");
    }
}

void StmtTypecheckVisitor::Visit(DeclStmt *x) {
    auto &top = context->local_stk.back();
    for (Decl &d: x->decls) {
        context->check_decl(d);
        if (!top.insert({d.name, &d}).second) {
            ERR("duplicate local decl", d.name);
        }
    }
}

void StmtTypecheckVisitor::Visit(If *x) {

    context->check_expr(x->cond);
    if (x->cond->type == Expr::ExprType::INT) {
        ERR("cond isn't int type");
    }
    context->check_stmt(x->on_true);
    if (x->on_false) {
        context->check_stmt(x->on_false);
    }
}

void StmtTypecheckVisitor::Visit(While *x) {
    context->check_expr(x->cond);
    if (x->cond->type != Expr::ExprType::INT) {
        ERR("cond isn't int type");
    }
    ++context->loop_cnt;
    context->check_stmt(x->body);
    --context->loop_cnt;
}

void StmtTypecheckVisitor::Visit(Return *x) {

    context->check_expr(x->expr);
    if (!((context->cur_func->is_int && x->expr->type == Expr::ExprType::INT) ||
          (!context->cur_func->is_int && x->expr->type != Expr::ExprType::INT))) {
        ERR("return type mismatch");
    }
}

void StmtTypecheckVisitor::Visit(Block *x) {
    context->local_stk.emplace_back();
    for (Stmt *s: x->stmts) {
        context->check_stmt(s);
    }
    context->local_stk.pop_back();
}

void StmtTypecheckVisitor::Visit(Break *x) {
    if (!context->loop_cnt) {
        ERR("break out of loop");
    }
}

void StmtTypecheckVisitor::Visit(Continue *x) {
    if (!context->loop_cnt) {
        ERR("continue out of loop");
    }
}

void StmtTypecheckVisitor::Visit(ExprStmt *x) {
    if (x->val)context->check_expr(x->val);
}


void type_check(Program &p) {

    for (auto g: p.func_or_decl) {
        if (Func *f = std::get_if<0>(&g)) {
            SymContext::getOneInstance()->check_func(f);
        } else if (Decl *d = std::get_if<1>(&g)) {
            SymContext::getOneInstance()->check_decl(*d);
            // 变量定义在检查后加入符号表，不允许定义时引用自身
            if (!SymContext::getOneInstance()->symtable.insert({d->name, d}).second) {
                ERR("duplicate decl", d->name);
            }
        }

    }

}

SymContext *SymContext::context = nullptr;