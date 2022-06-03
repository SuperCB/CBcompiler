//
// Created by supercb on 22-5-24.
//
#include "gtest/gtest.h"
#include "../src/Regex2Dfa/CFlex.h"
#include "../src/Parser/LALR.h"
#include "../include/json.hpp"

TEST(Regex2DFATest, test1) {
    CBCompiler::CFlex regex2Dfa("\\d+");
    EXPECT_EQ(regex2Dfa.matched("2132"), true);
}

TEST(Regex2DFATest1, test2) {
    CBCompiler::CFlex regex2Dfa("\\w+");
    EXPECT_EQ(regex2Dfa.matched("2132qweqw"), true);
}

TEST(Regex2DFATest, test3) {
    CBCompiler::CFlex regex2Dfa("void");
    EXPECT_EQ(regex2Dfa.matched("void"), true);
}

TEST(Regex2DFATest, test4) {
    CBCompiler::CFlex regex2Dfa("a*bb");
    EXPECT_EQ(regex2Dfa.matched("aaaaaabb"), true);
}