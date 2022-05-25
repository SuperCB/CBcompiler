//
// Created by supercb on 22-5-23.
//

#include "CompilerFrontGenerater.h"


CompilerFrontGenerater::CompilerFrontGenerater(std::string addr) : token_cnt(0) {
    json bnfs;
    assert(!addr.empty());
    std::ifstream jfile(addr);
    jfile >> bnfs;
    std::cout << bnfs;
    auto cflex = bnfs["cblex"];
    for (auto iter = cflex.begin(); iter != cflex.end(); ++iter) {
//        std::cout << iter.value()["val"] << std::endl;
//        std::cout << iter.value()["name"] << std::endl;
        val2id[iter.value()["val"]] = token_cnt;
        name2id[iter.value()["name"]] = token_cnt;
        token_cnt++;
    }
    lalr = new CBCompiler::LALR(bnfs["cbsion"]);
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

    out << "{";
    for (auto [k, v]: val2id) {
        out << "{";
        out << string_format("CFlex(\"%s\")", k.c_str());
        out << ",";
        out << v;
        out << "},\n";
    }
    out << "}";

    lalr->GenerateParseChart(out, name2id);
    out.close();
}

CompilerFrontGenerater::~CompilerFrontGenerater() {
    delete lalr;
}


