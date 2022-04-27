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
#include "LR0Item.h"
#include "ClosureSet.h"

using json = nlohmann::json;

namespace CBCompiler {


    class CBison {
        using uint = unsigned int;
    public:
        CBison() = delete;

        explicit CBison(std::string_view addr);

    private:
        std::unordered_map<std::string, std::vector<std::vector<LRToken>>> expressions;

        void generateLR0groups();


        std::string rootstr;


        std::vector<LR0group> cores;


        unsigned int lr0_group_id{1};

        std::vector<LR0Item> GetClosure(const std::vector<LR0Item> &coreitems);




        void GenerateNewLr0Group(LR0group &group, std::queue<LR0group> &que);
    };
}
