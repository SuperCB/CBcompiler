//
// Created by supercb on 22-5-23.
//

#include "CompilerFrontGenerater.h"


CompilerFrontGenerater::CompilerFrontGenerater(std::string addr) : token_cnt(0) {
    YAML::Node root = YAML::LoadFile(addr);


    auto cflex = root["cblex"];
    for (auto iter = cflex.begin(); iter != cflex.end(); ++iter) {
        auto con = *iter;

        val2id[con["val"].as<std::string>()] = token_cnt;
        name2id[con["name"].as<std::string>()] = token_cnt;
        token_cnt++;
    }
    lalr = new CBCompiler::LALR(root["cbsion"]);
    lalr->DrawLALR("two1.dot");
}

template<typename ... Args>
std::string string_format(const std::string &format, Args ... args) {
    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
    // unique_ptr<char[]> buf(new char[size]);
    char bytes[size];
    snprintf(bytes, size, format.c_str(), args ...);
    return bytes;
}

/**
 * 生成前端文件，要不要弄成命令行版本的呢？着实有趣的紧
 */
void CompilerFrontGenerater::Generate() {
    std::ofstream out("parse.cpp");


    out << R"(
#include "../src/Regex2Dfa/CFlex.h"
#include <vector>
#include <utility>)";

    out << R"(using uint=unsigned int;)";

    out << std::endl;

    out << R"(struct Act {
          enum : uint {
          Shift, Reduce, Accept, Err
        } kind;
    uint val;
    };)";

    out << std::endl;

    out << "enum class TokenType {";
    for (auto [k, v]: name2id) {
        out << string_format("%s=%u,\n", k.c_str(), v);
    }

    out << "};\n";

    out << "std::vector<std::pair<CBCompiler::CFlex, int> > tokens{";
    for (auto [k, v]: val2id) {
        out << "{";
        out << string_format("CBCompiler::CFlex(\"%s\")", k.c_str());
        out << ",";
        out << v;
        out << "},\n";
    }
    out << "};";

    lalr->GenerateParseChart(out, name2id);
    out.close();
}

CompilerFrontGenerater::~CompilerFrontGenerater() {

    delete lalr;
}


