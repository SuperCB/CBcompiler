//
// Created by supercb on 22-6-3.
//
#include "gtest/gtest.h"
#include "../lib/Regex2Dfa/CFlex.h"
#include "../lib/Parser/LALR.h"
#include <iostream>
#include <yaml-cpp/yaml.h>
TEST(LR1Testwithclosure, test1) {

    const std::string yamlFilePath = "/home/supercb/mycode/CppProjects/CBcompiler/yamls/withempty.yaml";
    YAML::Node root = YAML::LoadFile(yamlFilePath);
    CBCompiler::LALR lalr(root["cbsion"]);
   auto firsts= lalr.GetFirst({CBCompiler::LRType::UNEND, "T"});
    for (auto str: firsts) {
        std::cout << str << std::endl;
    }
//    lalr.DrawLR("lr1testwithclosure.dot", true);

}

TEST(LR1Testwithoutclosure, test1) {
    const std::string yamlFilePath = "/home/supercb/mycode/CppProjects/CBcompiler/test/withempty.yaml";
    YAML::Node root = YAML::LoadFile(yamlFilePath);
    CBCompiler::LALR lalr(root["cbsion"]);
    lalr.DrawLR("lr1testwithoutclosure.dot", false);
}

TEST(LALRTestwithclosure, test1) {
    const std::string yamlFilePath = "/home/supercb/mycode/CppProjects/CBcompiler/test/withempty.yaml";
    YAML::Node root = YAML::LoadFile(yamlFilePath);
    CBCompiler::LALR lalr(root["cbsion"]);
    lalr.DrawLALR("lalr1test.dot");
}