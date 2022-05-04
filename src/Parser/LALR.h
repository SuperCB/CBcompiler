//
// Created by supercb on 22-4-26.
//

#pragma once

#include <fstream>
#include <iostream>
#include <set>
#include "../../include/json.hpp"
#include "LRUtil.h"
#include "../../include/dbg.h"
#include <typeinfo>
#include <queue>
#include "LRItem.h"
#include "SetVector.h"

using json = nlohmann::json;

namespace CBCompiler {


    class LALR {
        using uint = unsigned int;
    public:
        LALR() = delete;

        LALR(std::string_view addr);

        void DrawLR(std::string outf, bool closure);

        void DrawLALR(std::string outf);

    private:


        std::vector<LRItem> GetLR0Closure(const std::vector<LRItem> &coreitems);


        void GenerateNewLr0Group(LR0group *group, std::queue<LR0group *> &que);

        void GetLR0groups();

        void AddEdge(uint from, uint to, const std::string &token);


        void GenerateLR1Groups();

        std::set<std::string> GetFirst(const LRToken &token);

        std::set<std::string> GetFirst(const std::vector<LRToken> &tokens);

        std::vector<LRItem> GetLR1Closure(const LRItem &core_item);

        uint StateTransfer(uint id, const std::string &token);


        std::unordered_map<std::string, std::vector<LRToken>> first;
        std::unordered_map<std::string, std::vector<std::vector<LRToken>>> expressions;
        std::vector<std::tuple<uint, uint, LRToken>> trans_chart;
        std::string rootstr;
        std::vector<LR0group *> groups;
        unsigned int lr0_group_id{0};
        bool closure;


    };
}
