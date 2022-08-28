#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <string_view>
#include <utility>
#include <memory>
#include <string>
#include "../lib/Regex2Dfa/CFlex.h"
#include "../lib/Parser/LALR.h"
#include <yaml-cpp/yaml.h>
#include "gtest/gtest.h"
#include "../lib/Compiler/CompilerFrontGenerater.h"



TEST(LR1Testwithcloe, test1) {

    CompilerFrontGenerater compilerFrontGenerater("/home/supercb/mycode/CppProjects/CBcompiler/yamls/test.yaml");
    compilerFrontGenerater.Generate();

}

TEST(LR1Testwithclosure, test1) {

    CompilerFrontGenerater compilerFrontGenerater("/home/supercb/mycode/CppProjects/CBcompiler/yamls/withempty.yaml");
    compilerFrontGenerater.Generate();

}
TEST(FinalTest, test1) {

    CompilerFrontGenerater compilerFrontGenerater("/home/supercb/mycode/CppProjects/CBcompiler/yamls/front.yaml");
    compilerFrontGenerater.Generate();

}