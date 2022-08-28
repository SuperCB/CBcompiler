//
// Created by supercb on 22-6-19.
//
#include "gtest/gtest.h"
#include "../lib/Regex2Dfa/CFlex.h"
#include "../lib/Parser/LALR.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

TEST(FindFirstTest, test1) {

    const std::string yamlFilePath = "/home/supercb/mycode/CppProjects/CBcompiler/yamls/withempty.yaml";
    YAML::Node root = YAML::LoadFile(yamlFilePath);
    CBCompiler::LALR lalr(root["cbsion"]);

    lalr.DrawLR("fuck.dot", true);
    lalr.DrawLALR("fucklalr.dot");
    auto firsts = lalr.GetFirst({CBCompiler::LRType::UNEND, "T"});
    for (auto str: firsts) {
        std::cout << str << std::endl;
    }
//    lalr.DrawLR("lr1testwithclosure.dot", true);

}