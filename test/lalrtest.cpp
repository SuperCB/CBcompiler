//
// Created by supercb on 22-6-3.
//
#include "gtest/gtest.h"
#include "../src/Regex2Dfa/CFlex.h"
#include "../src/Parser/LALR.h"
#include "../include/json.hpp"
#include <iostream>

TEST(LR1Testwithclosure, test1) {

    json bnfs;

    std::ifstream jfile("/home/supercb/mycode/CppProjects/CBcompiler/test/lr1test.json");
    jfile >> bnfs;
    std::cout << bnfs;
    CBCompiler::LALR lalr(bnfs["cbsion"]);
    lalr.DrawLR("lr1testwithclosure.dot", true);

}

TEST(LR1Testwithoutclosure, test1) {
    json bnfs;
    std::ifstream jfile("/home/supercb/mycode/CppProjects/CBcompiler/test/lr1test.json");
    jfile >> bnfs;
    std::cout << bnfs;
    CBCompiler::LALR lalr(bnfs["cbsion"]);
    lalr.DrawLR("lr1testwithoutclosure.dot", false);
}

TEST(LALRTestwithclosure, test1) {
    json bnfs;
    std::ifstream jfile("/home/supercb/mycode/CppProjects/CBcompiler/test/lr1test.json");
    jfile >> bnfs;
    std::cout << bnfs;
    CBCompiler::LALR lalr(bnfs["cbsion"]);
    lalr.DrawLALR("lalr1test.dot");
}