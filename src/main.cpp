//
// Created by supercb on 22-8-19.
//
#include <iostream>
#include "typecheck.h"

#include "front/parse.cpp"
#include "ssa.h"

int main() {
    FILE *pf = fopen(
            "/home/supercb/mycode/CppProjects/CBcompiler/sysyruntimelibrary/section1/functional_test/99_register_realloc.sy",
            "r");
    yyset_in(pf);
    yylex();
//    std::cout<<ACTION[110][35].expr;
    auto res = parse();
//    if (res == nullptr)
//        std::cout << "dsfa" << std::endl;
    fclose(pf);

    type_check(res);
//
//
    auto *ir = convert_ssa(res);
//    run_passes(ir, opt);
    std::ofstream output("output_ir.ll");
    output << *ir;


    return 0;
}