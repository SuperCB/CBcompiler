//
// Created by supercb on 22-6-22.
//
#include "gtest/gtest.h"

extern int yylex();

extern void yyset_in(FILE *_in_str);

//测试lex的运行效果，看起来相当的好
TEST(LexTest, test1) {

    FILE *pf = fopen("/home/supercb/mycode/CppProjects/CBcompiler/sysyruntimelibrary/section2/performance_test/conv0.sy", "r");
    yyset_in(pf);
    yylex();

    fclose(pf);
}
