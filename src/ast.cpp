//
// Created by supercb on 22-6-20.
//

#include "ast.h"

IntConstant *IntConstant::ZERO = new IntConstant(0);

Continue *Continue::INSTANCE = new Continue;

Break *Break::INSTANCE = new Break;
Func Func::BUILTIN[9] = {
        Func{true, "getint"},
        Func{true, "getch"}
};