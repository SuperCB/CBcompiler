//
// Created by supercb on 22-5-23.
//
#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include "../include/dbg.h"
#include "../include/json.hpp"
#include "../Regex2Dfa/CFlex.h"
#include "../Parser/LALR.h"
#include <fstream>

using json = nlohmann::json;

class CompilerFrontGenerater {
    using uint = unsigned int;
    using RegexToken = std::pair<CBCompiler::CFlex, std::string>;
public:
    CompilerFrontGenerater() = delete;

//    CompilerFrontGenerater(const CompilerFrontGenerater &compilerFrontGenerater) = delete;


    explicit CompilerFrontGenerater(std::string addr);

    virtual ~CompilerFrontGenerater();

    void Generate();
private:


    uint token_cnt;
    std::map<std::string, ::uint> val2id;
    std::map<std::string, ::uint> name2id;
    std::vector<RegexToken> tokens_pass;
    CBCompiler::LALR *lalr;
};


