//
// Created by supercb on 22-8-24.
//

#pragma once

//#include "ast.h"

class Assign;

class DeclStmt;


class If;

class While;

class Return;

class ExprStmt;

class Assign;

class Continue;

class Break;

class Block;

class StmtBaseVisitor {
public:
//    virtual void Visit(Stmt *stmt){}
    virtual void Visit(Assign *x) {};

    virtual void Visit(DeclStmt *x) {};

    virtual void Visit(If *x) {};

    virtual void Visit(While *x) {};

    virtual void Visit(Return *x) {};

    virtual void Visit(ExprStmt *x) {};

    virtual void Visit(Continue *x) {};

    virtual void Visit(Break *x) {};

    virtual void Visit(Block *x) {};

};



class Binary;
class Call;
class Index;
class IntConstant;
class ExprBaseVisitor {
public:


    virtual void Visit(Binary *x) {};

    virtual void Visit(Call*x) {};

    virtual void Visit(Index*x) {};

    virtual void Visit(IntConstant*x) {};


};




