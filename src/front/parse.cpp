

#include <vector>
#include <utility>
#include "lex.h"
#include<stack>
#include <iostream>
#include <cassert>
#include "../ast.h"
#include "../include/dbg.h"
using uint = unsigned int;

struct Act {
    enum : uint {
        Shift, Reduce, Accept, Err
    } kind;
    uint val;
};
using StackItem = std::variant<Token, Program, std::vector<Decl>, Decl, InitList, std::vector<InitList>, Func, Block,
        Stmt *, std::vector<Stmt *>, Expr *, std::vector<Expr *>>;

//从表达式编号到非终结符编号
uint expres2nonter[]={0,1,1,1,1,2,2,3,3,4,4,4,4,5,5,5,6,6,7,7,7,7,8,8,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,14,14,15,15,16,16,}
;

const static Act ACTION[147][35]={{{Act::Shift,1},{Act::Shift,2},{Act::Shift,4},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,7},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,9},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Reduce,4},{Act::Reduce,4},{Act::Reduce,4},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,4}},
                                  {{Act::Err,0},{Act::Shift,11},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Reduce,3},{Act::Reduce,3},{Act::Reduce,3},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,3}},
                                  {{Act::Shift,1},{Act::Shift,2},{Act::Shift,4},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Accept,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,14},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,8},{Act::Reduce,8},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,17},{Act::Reduce,12},{Act::Reduce,12},{Act::Err,0},{Act::Shift,16},{Act::Err,0},{Act::Shift,15},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,19},{Act::Shift,20},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,21},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Reduce,2},{Act::Reduce,2},{Act::Reduce,2},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,2}},
                                  {{Act::Reduce,1},{Act::Reduce,1},{Act::Reduce,1},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,1}},
                                  {{Act::Err,0},{Act::Shift,23},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,25},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Shift,23},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,34},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,37},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,39},{Act::Reduce,10},{Act::Reduce,10},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,40},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,21},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Err,0},{Act::Err,0},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6},{Act::Reduce,6}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,17},{Act::Reduce,12},{Act::Reduce,12},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,15},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,19},{Act::Shift,42},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,43},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,25},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,25},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,46},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,47},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Reduce,47},{Act::Err,0},{Act::Reduce,47},{Act::Reduce,47},{Act::Err,0},{Act::Err,0},{Act::Reduce,47},{Act::Err,0},{Act::Reduce,47},{Act::Err,0},{Act::Reduce,47},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Err,0},{Act::Reduce,46},{Act::Reduce,46},{Act::Err,0},{Act::Shift,49},{Act::Reduce,46},{Act::Shift,15},{Act::Reduce,46},{Act::Err,0},{Act::Reduce,46},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,64},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,46},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,69},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Reduce,15},{Act::Reduce,15},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,15},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,37},{Act::Shift,71},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,11},{Act::Reduce,11},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,37},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,7},{Act::Reduce,7},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Err,0},{Act::Err,0},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5},{Act::Reduce,5}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,49},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,49},{Act::Shift,75},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Shift,80},{Act::Shift,4},{Act::Shift,86},{Act::Shift,79},{Act::Err,0},{Act::Shift,87},{Act::Shift,88},{Act::Shift,90},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,89},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Shift,77},{Act::Shift,82},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Reduce,21},{Act::Reduce,21},{Act::Reduce,21},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,21}},
                                  {{Act::Err,0},{Act::Shift,23},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,93},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Shift,95},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Err,0},{Act::Reduce,45},{Act::Reduce,45},{Act::Err,0},{Act::Err,0},{Act::Reduce,45},{Act::Shift,40},{Act::Reduce,45},{Act::Err,0},{Act::Reduce,45},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Reduce,41},{Act::Err,0},{Act::Reduce,41},{Act::Reduce,41},{Act::Err,0},{Act::Err,0},{Act::Reduce,41},{Act::Err,0},{Act::Reduce,41},{Act::Err,0},{Act::Reduce,41},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,40},{Act::Reduce,40},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Reduce,40},{Act::Reduce,40},{Act::Reduce,40},{Act::Reduce,40},{Act::Reduce,40},{Act::Reduce,40},{Act::Reduce,40},{Act::Reduce,40},{Act::Err,0},{Act::Reduce,40},{Act::Reduce,40},{Act::Err,0},{Act::Err,0},{Act::Reduce,40},{Act::Err,0},{Act::Reduce,40},{Act::Err,0},{Act::Reduce,40},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,39},{Act::Reduce,39},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Reduce,39},{Act::Reduce,39},{Act::Reduce,39},{Act::Reduce,39},{Act::Reduce,39},{Act::Reduce,39},{Act::Reduce,39},{Act::Reduce,39},{Act::Err,0},{Act::Reduce,39},{Act::Reduce,39},{Act::Err,0},{Act::Err,0},{Act::Reduce,39},{Act::Err,0},{Act::Reduce,39},{Act::Err,0},{Act::Reduce,39},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Err,0},{Act::Err,0},{Act::Reduce,70},{Act::Reduce,70},{Act::Reduce,70},{Act::Err,0},{Act::Reduce,70},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Reduce,20},{Act::Reduce,20},{Act::Reduce,20},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,20}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,17},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,17},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,14},{Act::Reduce,14},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,14},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,112},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,111},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,9},{Act::Reduce,9},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,113},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,114},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,48},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,48},{Act::Shift,115},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Err,0},{Act::Err,0},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23},{Act::Reduce,23}},
                                  {{Act::Err,0},{Act::Shift,80},{Act::Shift,4},{Act::Shift,86},{Act::Shift,79},{Act::Err,0},{Act::Shift,87},{Act::Shift,88},{Act::Shift,90},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,89},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Shift,116},{Act::Shift,82},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,118},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,21},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Err,0},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Err,0},{Act::Err,0},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Reduce,64},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Reduce,46},{Act::Shift,119},{Act::Err,0},{Act::Reduce,46},{Act::Err,0},{Act::Shift,49},{Act::Err,0},{Act::Shift,15},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Err,0},{Act::Err,0},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Reduce,54},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Shift,121},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Err,0},{Act::Err,0},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Reduce,55},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,122},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,123},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,125},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Err,0},{Act::Err,0},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Reduce,53},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,126},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,24},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,24},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Reduce,19},{Act::Reduce,19},{Act::Reduce,19},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,19}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Reduce,42},{Act::Err,0},{Act::Reduce,42},{Act::Reduce,42},{Act::Err,0},{Act::Err,0},{Act::Reduce,42},{Act::Err,0},{Act::Reduce,42},{Act::Err,0},{Act::Reduce,42},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Reduce,66},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,66},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Reduce,44},{Act::Err,0},{Act::Reduce,44},{Act::Reduce,44},{Act::Err,0},{Act::Err,0},{Act::Reduce,44},{Act::Err,0},{Act::Reduce,44},{Act::Err,0},{Act::Reduce,44},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,127},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,128},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Reduce,28},{Act::Err,0},{Act::Reduce,28},{Act::Reduce,28},{Act::Err,0},{Act::Err,0},{Act::Reduce,28},{Act::Err,0},{Act::Reduce,28},{Act::Err,0},{Act::Reduce,28},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,26},{Act::Reduce,26},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Reduce,26},{Act::Reduce,26},{Act::Reduce,26},{Act::Reduce,26},{Act::Reduce,26},{Act::Reduce,26},{Act::Reduce,26},{Act::Reduce,26},{Act::Err,0},{Act::Reduce,26},{Act::Reduce,26},{Act::Err,0},{Act::Err,0},{Act::Reduce,26},{Act::Err,0},{Act::Reduce,26},{Act::Err,0},{Act::Reduce,26},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Reduce,32},{Act::Reduce,32},{Act::Reduce,32},{Act::Reduce,32},{Act::Reduce,32},{Act::Reduce,32},{Act::Reduce,32},{Act::Reduce,32},{Act::Err,0},{Act::Reduce,32},{Act::Reduce,32},{Act::Err,0},{Act::Err,0},{Act::Reduce,32},{Act::Err,0},{Act::Reduce,32},{Act::Err,0},{Act::Reduce,32},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Reduce,36},{Act::Reduce,36},{Act::Reduce,36},{Act::Reduce,36},{Act::Err,0},{Act::Reduce,36},{Act::Reduce,36},{Act::Err,0},{Act::Err,0},{Act::Reduce,36},{Act::Err,0},{Act::Reduce,36},{Act::Err,0},{Act::Reduce,36},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Reduce,37},{Act::Reduce,37},{Act::Err,0},{Act::Reduce,37},{Act::Reduce,37},{Act::Err,0},{Act::Err,0},{Act::Reduce,37},{Act::Err,0},{Act::Reduce,37},{Act::Err,0},{Act::Reduce,37},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Reduce,31},{Act::Reduce,31},{Act::Reduce,31},{Act::Reduce,31},{Act::Reduce,31},{Act::Reduce,31},{Act::Reduce,31},{Act::Reduce,31},{Act::Err,0},{Act::Reduce,31},{Act::Reduce,31},{Act::Err,0},{Act::Err,0},{Act::Reduce,31},{Act::Err,0},{Act::Reduce,31},{Act::Err,0},{Act::Reduce,31},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Reduce,35},{Act::Reduce,35},{Act::Reduce,35},{Act::Reduce,35},{Act::Err,0},{Act::Reduce,35},{Act::Reduce,35},{Act::Err,0},{Act::Err,0},{Act::Reduce,35},{Act::Err,0},{Act::Reduce,35},{Act::Err,0},{Act::Reduce,35},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Reduce,34},{Act::Reduce,34},{Act::Reduce,34},{Act::Reduce,34},{Act::Reduce,34},{Act::Reduce,34},{Act::Reduce,34},{Act::Reduce,34},{Act::Err,0},{Act::Reduce,34},{Act::Reduce,34},{Act::Err,0},{Act::Err,0},{Act::Reduce,34},{Act::Err,0},{Act::Reduce,34},{Act::Err,0},{Act::Reduce,34},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Reduce,29},{Act::Err,0},{Act::Reduce,29},{Act::Reduce,29},{Act::Err,0},{Act::Err,0},{Act::Reduce,29},{Act::Err,0},{Act::Reduce,29},{Act::Err,0},{Act::Reduce,29},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Reduce,30},{Act::Err,0},{Act::Reduce,30},{Act::Reduce,30},{Act::Err,0},{Act::Err,0},{Act::Reduce,30},{Act::Err,0},{Act::Reduce,30},{Act::Err,0},{Act::Reduce,30},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Reduce,33},{Act::Reduce,33},{Act::Reduce,33},{Act::Reduce,33},{Act::Reduce,33},{Act::Reduce,33},{Act::Reduce,33},{Act::Reduce,33},{Act::Err,0},{Act::Reduce,33},{Act::Reduce,33},{Act::Err,0},{Act::Err,0},{Act::Reduce,33},{Act::Err,0},{Act::Reduce,33},{Act::Err,0},{Act::Reduce,33},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,27},{Act::Reduce,27},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Reduce,27},{Act::Reduce,27},{Act::Reduce,27},{Act::Reduce,27},{Act::Reduce,27},{Act::Reduce,27},{Act::Reduce,27},{Act::Reduce,27},{Act::Err,0},{Act::Reduce,27},{Act::Reduce,27},{Act::Err,0},{Act::Err,0},{Act::Reduce,27},{Act::Err,0},{Act::Reduce,27},{Act::Err,0},{Act::Reduce,27},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Reduce,38},{Act::Err,0},{Act::Reduce,38},{Act::Reduce,38},{Act::Err,0},{Act::Err,0},{Act::Reduce,38},{Act::Err,0},{Act::Reduce,38},{Act::Err,0},{Act::Reduce,38},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Reduce,18},{Act::Reduce,18},{Act::Reduce,18},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,18}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,13},{Act::Reduce,13},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,13},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,37},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Err,0},{Act::Err,0},{Act::Reduce,69},{Act::Reduce,69},{Act::Reduce,69},{Act::Err,0},{Act::Reduce,69},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,68},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,68},{Act::Reduce,68},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Err,0},{Act::Err,0},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22},{Act::Reduce,22}},
                                  {{Act::Err,0},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Err,0},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Err,0},{Act::Err,0},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Reduce,63},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Reduce,45},{Act::Shift,133},{Act::Err,0},{Act::Reduce,45},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,40},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Err,0},{Act::Err,0},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Reduce,52},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Err,0},{Act::Err,0},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Reduce,62},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Shift,135},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Err,0},{Act::Err,0},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Reduce,59},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Err,0},{Act::Err,0},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Reduce,60},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Reduce,43},{Act::Err,0},{Act::Reduce,43},{Act::Reduce,43},{Act::Err,0},{Act::Err,0},{Act::Reduce,43},{Act::Err,0},{Act::Reduce,43},{Act::Err,0},{Act::Reduce,43},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,16},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,16},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,137},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,138},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Shift,139},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,29},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,141},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Err,0},{Act::Err,0},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Reduce,61},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Reduce,65},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,65},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,67},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,67},{Act::Reduce,67},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Shift,80},{Act::Shift,4},{Act::Shift,86},{Act::Shift,79},{Act::Err,0},{Act::Shift,87},{Act::Shift,88},{Act::Shift,90},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,89},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Err,0},{Act::Shift,82},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Err,0},{Act::Err,0},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Reduce,51},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,55},{Act::Shift,66},{Act::Shift,54},{Act::Shift,62},{Act::Shift,63},{Act::Shift,59},{Act::Shift,56},{Act::Shift,65},{Act::Shift,61},{Act::Shift,60},{Act::Shift,57},{Act::Shift,58},{Act::Shift,67},{Act::Err,0},{Act::Err,0},{Act::Shift,143},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Shift,80},{Act::Shift,4},{Act::Shift,86},{Act::Shift,79},{Act::Err,0},{Act::Shift,87},{Act::Shift,88},{Act::Shift,90},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,89},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Err,0},{Act::Shift,82},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Shift,145},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Err,0},{Act::Err,0},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Reduce,56},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Err,0},{Act::Err,0},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Reduce,50},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Err,0},{Act::Err,0},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Reduce,58},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Shift,80},{Act::Shift,4},{Act::Shift,86},{Act::Shift,79},{Act::Err,0},{Act::Shift,87},{Act::Shift,88},{Act::Shift,90},{Act::Shift,32},{Act::Shift,31},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,89},{Act::Shift,30},{Act::Shift,27},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Shift,44},{Act::Err,0},{Act::Shift,82},{Act::Shift,28},{Act::Err,0}},
                                  {{Act::Err,0},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Err,0},{Act::Err,0},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Err,0},{Act::Err,0},{Act::Err,0},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Reduce,57},{Act::Err,0}},
};
const static uint Goto [147][17]={{ 0,6,5,0,0,0,0,3,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,10,8,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,13,0,0,0,0,12,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,22,8,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,26,0,24,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,33,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,35,0,24,0,0,0,0,0},
                                  { 0,0,0,0,0,38,0,0,0,0,36,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,41,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,45,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,48,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,50},
                                  { 0,0,0,0,0,0,0,0,0,0,51,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,52,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,53,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,70,72,0,0,0,36,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,73,0,0,0,0,36,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,74,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,76,0},
                                  { 0,0,83,0,0,0,0,0,85,0,84,0,81,78,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,91,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,92,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,94,0,0,0,96,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,97,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,98,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,99,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,100,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,101,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,102,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,103,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,104,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,105,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,106,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,107,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,108,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,109,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,83,0,0,0,0,0,85,0,84,0,117,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,10,8,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,120},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,124,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,129,0,0,0,0,36,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,130,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,131,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,132,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,134,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,136,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,140,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,83,0,0,0,0,0,85,0,84,0,142,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,83,0,0,0,0,0,85,0,84,0,144,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                  { 0,0,83,0,0,0,0,0,85,0,84,0,146,0,0,0,0},
                                  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

extern int yylex();
extern void yyset_in(FILE *_in_str);



Program parse() {


    std::stack<uint> states;
    std::stack<std::pair<StackItem, uint>> stk;
    // push the initial state
    tokens.push_back({TokenType::Over, "$"});

    stk.push({Program{}, 0});

    uint loc = 0;


    while (loc < tokens.size()) {
        auto token = tokens[loc];


        TokenType token_type = token.type;
        uint top = stk.top().second;
        Act act = ACTION[top][static_cast<uint>(token_type)];
//        std::cout<<top<<std::endl;
        switch (act.kind) {
            case Act::Shift: {
                stk.push({token, act.val});
                loc++;
                break;
            }
            case Act::Reduce: {
                StackItem __;
                switch (act.val) {
                    case 1: {//  Program  Program  Decl
                        std::vector<Decl> _2(std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();
                        Program _1(std::move(*std::get_if<Program>(&stk.top().first)));
                        stk.pop();
                        for (auto &decl: _2) {
                            decl.is_glob = true;
                            _1.func_or_decl.emplace_back(decl);
                        }
                        __ = std::move(_1);
                        break;
                    }
                    case 2: {//  Program  Program  Func
                        Func _2(std::move(*std::get_if<Func>(&stk.top().first)));
                        stk.pop();
                        Program _1(std::move(*std::get_if<Program>(&stk.top().first)));
                        stk.pop();
                        _1.func_or_decl.emplace_back(std::move(_2));
                        __ = std::move(_1);
                        break;
                    }
                    case 3:{//  Program  Decl
                       std::vector<Decl>_1 (
                                std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();
                        Program _2;
                        for(auto item:_1)
                        {
                            _2.func_or_decl.emplace_back(item);
                        }
                        dbg("program decl");

                        __ = _2;
                        break;
                    }case 4:{//  Program  Func
                        Func _1(std::move(*std::get_if<Func>(&stk.top().first)));
                        stk.pop();

                        Program _2;
                        _2.func_or_decl.emplace_back(_1);
                        __ = _2;
                        break;
                    }
                    case 5: {//  Decl  Const  Int  DeclList  Semi
                        stk.pop();
                        [[maybe_unused]] std::vector<Decl> _3(
                                std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();
//                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
//                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        for (Decl &d: _3) {
                            d.is_const = true;
                        }
                        __ = std::move(_3);

                        break;
                    }
                    case 6: {//  Decl  Int  DeclList  Semi
                        stk.pop();
                        [[maybe_unused]] std::vector<Decl> _2(
                                std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();
                        stk.pop();
                        __ = std::move(_2);
                        break;
                    }
                    case 7: {//  DeclList  DeclList  Comma  Decl1
                        Decl _3(std::move(*std::get_if<Decl>(&stk.top().first)));
                        stk.pop();
                        stk.pop();
                        std::vector<Decl> _1(std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();

                        _1.push_back(std::move(_3));
                        __ = std::move(_1);
                        break;
                    }
                    case 8: {//  DeclList  Decl1
                        Decl _1(std::move(*std::get_if<Decl>(&stk.top().first)));
                        stk.pop();
                        __ = std::vector{std::move(_1)};
                        break;
                    }
                    case 9: {//  Decl1  ID  ArrayDims  Assign  InitList
                        InitList _4(std::move(*std::get_if<InitList>(&stk.top().first)));
                        stk.pop();
                        stk.pop();
                        std::vector<Expr *> _2(*std::get_if<std::vector<Expr *>>(&stk.top().first));
                        stk.pop();
                        Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Decl{false, false, true, _1.val, std::move(_2), std::move(_4)};

                        break;
                    }
                    case 10: {//  Decl1  ID  ArrayDims
                          std::vector<Expr *> _2(
                                std::move(*std::get_if<std::vector<Expr *>>(&stk.top().first)));
                        stk.pop();
                        Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Decl{false, false, false, _1.val, std::move(_2), {}};

                        break;
                    }
                    case 11: {//  Decl1  ID  Assign  InitList
                        InitList _3(std::move(*std::get_if<InitList>(&stk.top().first)));
                        stk.pop();
                        stk.pop();


                        Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Decl{false, false, true, _1.val, {}, std::move(_3)};

                        break;
                    }
                    case 12: {//  Decl1  ID
                        Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Decl(false, false, false, _1.val, {}, {});
                        break;
                    }
                    case 13: {//  InitList  LBrc  InitList1  RBrc
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();

                        [[maybe_unused]] std::vector<InitList> _2(
                                std::move(*std::get_if<std::vector<InitList>>(&stk.top().first)));
                        stk.pop();
//                        [[maybe_unused]] InitList _2(std::move(*std::get_if<InitList>(&stk.top().first)));
//                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = InitList{nullptr, std::move(_2)};
                        break;
                    }
                    case 14: {//  InitList  LBrc  RBrc
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = InitList{nullptr, {}};
                        break;
                    }
                    case 15: {//  InitList  Expr
                        Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = InitList{_1, {}};
                        break;
                    }
                    case 16: {//  InitList1  InitList1  Comma  InitList
                        [[maybe_unused]] InitList _3(std::move(*std::get_if<InitList>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<InitList> _1(
                                std::move(*std::get_if<std::vector<InitList>>(&stk.top().first)));
                        stk.pop();
                        _1.push_back(std::move(_3));
                        __ = std::move(_1);
                        break;
                    }
                    case 17: {//  InitList1  InitList
                        [[maybe_unused]] InitList _1(std::move(*std::get_if<InitList>(&stk.top().first)));
                        stk.pop();
                        __ = std::vector{std::move(_1)};
                        break;
                    }
                    case 18: {//  Func  Int  ID  LPar  ParamList  RPar  Block
                        [[maybe_unused]] Block _6(std::move(*std::get_if<Block>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _5(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Decl> _4(
                                std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Func(true, _2.val, std::move(_4), std::move(_6));

                        break;
                    }
                    case 19: {//  Func  Void  ID  LPar  ParamList  RPar  Block
                        [[maybe_unused]] Block _6(std::move(*std::get_if<Block>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _5(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Decl> _4(
                                std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Func(false, _2.val, std::move(_4), std::move(_6));

                        break;
                    }
                    case 20: {//  Func  Int  ID  LPar  RPar  Block
                        [[maybe_unused]] Block _5(std::move(*std::get_if<Block>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();

                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Func(true, _2.val, {}, std::move(_5));
                        dbg("func");

                        break;
                    }
                    case 21: {//  Func  Void  ID  LPar  RPar  Block
                        [[maybe_unused]] Block _5(std::move(*std::get_if<Block>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        dbg("func");
                        __ = Func(false, _2.val, {}, std::move(_5));
                        break;
                    }
                    case 22: {//  Block  LBrc  StmtList  RBrc
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Stmt *> _2(
                                std::move(*std::get_if<std::vector<Stmt *>>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();

                        __ = Block{std::move(_2)};
                        break;
                    }
                    case 23: {//  Block  LBrc  RBrc
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();

                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();

                        __ = Block();
                        break;
                    }
                    case 24: {//  ParamList  ParamList  Comma  Param
                        [[maybe_unused]] Decl _3(std::move(*std::get_if<Decl>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Decl> _1(
                                std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();
                        _1.push_back(std::move(_3));
                        __ = std::move(_1);
                        break;
                    }
                    case 25: {//  ParamList  Param
                        [[maybe_unused]] Decl _1(std::move(*std::get_if<Decl>(&stk.top().first)));
                        stk.pop();
                        __ = std::vector{std::move(_1)};
                        break;
                    }
                    case 26: {//  Expr  Expr  Add  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Add, _1, _3};
                        break;
                    }
                    case 27: {//  Expr  Expr  Sub  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Sub, _1, _3};
                        break;
                    }
                    case 28: {//  Expr  Expr  Mul  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Mul, _1, _3};
                        break;
                    }
                    case 29: {//  Expr  Expr  Div  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Div, _1, _3};
                        break;
                    }
                    case 30: {//  Expr  Expr  Mod  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Mod, _1, _3};
                        break;
                    }
                    case 31: {//  Expr  Expr  Lt  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Lt, _1, _3};
                        break;
                    }
                    case 32: {//  Expr  Expr  Le  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Le, _1, _3};
                        break;
                    }
                    case 33: {//  Expr  Expr  Gt  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Gt, _1, _3};
                        break;
                    }
                    case 34: {//  Expr  Expr  Ge  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Ge, _1, _3};
                        break;
                    }
                    case 35: {//  Expr  Expr  Eq  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Eq, _1, _3};
                        break;
                    }
                    case 36: {//  Expr  Expr  Ne  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Ne, _1, _3};
                        break;
                    }
                    case 37: {//  Expr  Expr  And  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::And, _1, _3};
                        break;
                    }
                    case 38: {//  Expr  Expr  Or  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary{OpType::Or, _1, _3};
                        break;
                    }
                    case 39: {//  Expr  Add  Expr
                        [[maybe_unused]] Expr *_2(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = _2;
                        break;
                    }
                    case 40: {//  Expr  Sub  Expr
                        [[maybe_unused]] Expr *_2(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary(OpType::Sub, IntConstant::getZero(), _2);
                        break;
                    }
                    case 41: {//  Expr  Not  Expr
                        [[maybe_unused]] Expr *_2(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Binary(OpType::Eq, IntConstant::getZero(), _2);
                        break;
                    }
                    case 42: {//  Expr  LPar  Expr  RPar
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_2(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = _2;
                        break;
                    }
                    case 43: {//  Expr  ID  LPar  ExprList  RPar
                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Expr *> _3(
                                std::move(*std::get_if<std::vector<Expr *>>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Call{_1.val, std::move(_3)};
                        break;
                    }
                    case 44:{//  Expr  ID  LPar  RPar

                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();

                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Call{_1.val, {}};
                        break;

                    }

                    case 45: {//  Expr  ID  ArrayDims
                        [[maybe_unused]] std::vector<Expr *> _2(
                                std::move(*std::get_if<std::vector<Expr *>>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Index(_1.val, std::move(_2));
                        break;
                    }
                    case 46: {//  Expr  ID

                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Index(_1.val, {});
                        break;
                    }
                    case 47: {//  Expr  IntConst
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        int base = _1.val[1] == 'x' ? 16 : _1.val[0] == '0' ? 8 : 10;
                        __ = new IntConstant{(int) strtol(_1.val.data(), nullptr, base)};
                        break;
                    }
                    case 48: {//  Param  Int  ID  FunArrayDims
                        [[maybe_unused]] std::vector<Expr *> _3(
                                std::move(*std::get_if<std::vector<Expr *>>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Decl{false, false, false, _2.val, std::move(_3), {}};

                        break;
                    }
                    case 49: {//  Param  Int  ID
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Decl{false, false, false, _2.val, {}, {}};

                        break;
                    }
                    case 50: {//  Stmt  ID  ArrayDims  Assign  Expr  Semi
                        [[maybe_unused]] Token _5(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_4(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Expr *> _2(
                                std::move(*std::get_if<std::vector<Expr *>>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Assign(_1.val, std::move(_2), _4);
                        break;
                    }
                    case 51:{//  Stmt  ID  Assign  Expr  Semi

                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();

                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Assign(_1.val, {}, _3);

                        break;

                    }


                    case 52: {//  Stmt  Expr  Semi
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = new ExprStmt(_1);
                        break;
                    }
                    case 53: {//  Stmt  Semi
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new ExprStmt(nullptr);
                        break;
                    }
                    case 54: {//  Stmt  Decl
                        [[maybe_unused]] std::vector<Decl> _1(
                                std::move(*std::get_if<std::vector<Decl>>(&stk.top().first)));
                        stk.pop();
                        __ = new DeclStmt(std::move(_1));
                        break;
                    }
                    case 55: {//  Stmt Block
                        [[maybe_unused]] Block _1(std::move(*std::get_if<Block>(&stk.top().first)));
                        stk.pop();
                        __ = new Block(std::move(_1.stmts));
                        break;
                    }
                    case 56: {//  Stmt  If  LPar  Expr  RPar  Stmt

                        [[maybe_unused]] Stmt *_5(std::move(*std::get_if<Stmt *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new If(_3, _5, nullptr);
                        break;
                    }
                    case 57: {//  Stmt  If  LPar  Expr  RPar  Stmt  Else  Stmt
                        [[maybe_unused]] Stmt *_7(std::move(*std::get_if<Stmt *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _6(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Stmt *_5(std::move(*std::get_if<Stmt *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new If(_3, _5, _7);
                        break;
                    }
                    case 58: {//  Stmt  While  LPar  Expr  RPar  Stmt
                        [[maybe_unused]] Stmt *_5(std::move(*std::get_if<Stmt *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new While(_3, _5);
                        break;
                    }
                    case 59: {//  Stmt  Break  Semi
                        [[maybe_unused]] Token _2(*std::get_if<Token>(&stk.top().first));
                        stk.pop();
                        [[maybe_unused]] Token _1(*std::get_if<Token>(&stk.top().first));
                        stk.pop();
                        __ = Break::INSTANCE;
                        break;
                    }
                    case 60: {//  Stmt  Continue  Semi
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = Continue::INSTANCE;
                        break;
                    }
                    case 61: {//  Stmt  Return  Expr  Semi
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_2(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = new Return(_2);
                        break;
                    }
                    case 62: {//  Stmt  Return  Semi
                        [[maybe_unused]] Token _2(*std::get_if<Token>(&stk.top().first));
                        stk.pop();
                        [[maybe_unused]] Token _1(*std::get_if<Token>(&stk.top().first));
                        stk.pop();
                        __ = new Return(nullptr);
                        break;
                    }
                    case 63: {//  StmtList  StmtList  Stmt
                        [[maybe_unused]] Stmt *_2(std::move(*std::get_if<Stmt *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Stmt *> _1(
                                std::move(*std::get_if<std::vector<Stmt *>>(&stk.top().first)));
                        stk.pop();
                        _1.push_back(_2);
                        __ = std::move(_1);
                        break;
                    }
                    case 64: {//  StmtList  Stmt
                        [[maybe_unused]] Stmt *_1(std::move(*std::get_if<Stmt *>(&stk.top().first)));
                        stk.pop();

                        __ = std::move(std::vector<Stmt *>{_1});
                        break;
                    }
                    case 65: {//  ExprList  ExprList  Comma  Expr
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Expr *> _1(
                                std::move(*std::get_if<std::vector<Expr *>>(&stk.top().first)));
                        stk.pop();
                        _1.push_back(_3);
                        __ = std::move(_1);
                        break;
                    }
                    case 66: {//  ExprList  Expr
                        [[maybe_unused]] Expr *_1(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        __ = std::vector{_1};
                        break;
                    }
                    case 67: {//  FunArrayDims  FunArrayDims  LBrk  Expr  RBrk
                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Expr *> _1(
                                std::move(*std::get_if<std::vector<Expr *>>(&stk.top().first)));
                        stk.pop();
                        _1.push_back(_3);
                        __ = std::move(_1);
                        break;
                    }
                    case 68: {//  FunArrayDims  LBrk  RBrk
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        __ = std::vector<Expr *>{nullptr};
                        break;
                    }
                    case 69: {//  ArrayDims  ArrayDims  LBrk  Expr  RBrk
                        [[maybe_unused]] Token _4(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_3(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _2(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] std::vector<Expr *> _1(
                                std::move(*std::get_if<std::vector<Expr *>>(&stk.top().first)));
                        stk.pop();
                        _1.push_back(_3);
                        __ = std::move(_1);
                        break;
                    }
                    case 70: {//  ArrayDims  LBrk  Expr  RBrk
                        [[maybe_unused]] Token _3(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Expr *_2(std::move(*std::get_if<Expr *>(&stk.top().first)));
                        stk.pop();
                        [[maybe_unused]] Token _1(std::move(*std::get_if<Token>(&stk.top().first)));
                        stk.pop();

                        __ = std::vector<Expr *>{_2};
                        break;
                    }
                    default:
                        break;
                }
                assert(stk.size());
                auto nxstate = Goto[stk.top().second][expres2nonter[act.val]];
                stk.push({__, nxstate});
                break;
            }
            case Act::Accept:
//                std::cout << "fuck" << std::endl;
               return std::move(*std::get_if<Program>(&stk.top().first));
//                return std::get_if<Program>(&stk.top().first);
            case Act::Err:
                std::cout << token.val<<std::endl;
                return {};
        }
    }
    return {};
}

//int main() {
//    FILE *pf = fopen(
//            "/home/supercb/mycode/CppProjects/CBcompiler/sysyruntimelibrary/section1/functional_test/00_arr_defn2.sy", "r");
//    yyset_in(pf);
//    yylex();
////    std::cout<<ACTION[110][35].expr;
//    auto res = parse();
//    if (res == nullptr)
//        std::cout << "dsfa" << std::endl;
//    fclose(pf);
//}