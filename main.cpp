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
#include "lib/Regex2Dfa/CFlex.h"
#include "lib/Parser/LALR.h"
#include <list>
#include "lib/Compiler/CompilerFrontGenerater.h"
#include <yaml-cpp/yaml.h>

using namespace std;




int main() {
//
    CompilerFrontGenerater compilerFrontGenerater("/home/supercb/mycode/CppProjects/CBcompiler/yamls/front.yaml");
    compilerFrontGenerater.Generate();


//    const std::string yamlFilePath = "/home/supercb/mycode/CppProjects/CBcompiler/yamls/withempty.yaml";
//    YAML::Node root = YAML::LoadFile(yamlFilePath);
//    CBCompiler::LALR lalr(root["cbsion"]);
//    auto firsts= lalr.GetFirst({CBCompiler::LRType::UNEND, "Tp"});
//    for (auto str: firsts) {
//        std::cout << str << std::endl;
//    }
}
