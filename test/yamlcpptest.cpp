//
// Created by supercb on 22-6-17.
//
#include "gtest/gtest.h"
#include "../src/Regex2Dfa/CFlex.h"

#include <yaml-cpp/yaml.h>


TEST(Regex2DFATest, test1) {
    const std::string yamlFilePath = "/home/supercb/mycode/CppProjects/CBcompiler/test/cbsion.yaml";
    YAML::Node root = YAML::LoadFile(yamlFilePath);
    auto expres = root["cbsion"]["exprs"];
    for (auto begin = expres.begin(); begin != expres.end(); begin++) {
        auto c = *begin;
        std::cout << c.Type();
        std::cout << c["lval"];
    }
}
