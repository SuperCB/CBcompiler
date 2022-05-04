//
// Created by supercb on 22-4-23.
//

#pragma once
#include "dbg.h"

#include <cassert>
#include <string>
#include "DfaUtil.h"
#include <cstring>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>


namespace CBCompiler {


    class Graph {
    public:
        using uint = unsigned int;

        Graph();

        void GenerateRelation(int from, int to, const CBCompiler::Token &token);

        void AddEdge(int a, int b, char ch); // 添加一条边a->b
        ~Graph();

        inline void AddAcceptState(uint id) {
            acc_states.insert(id);
        };

        inline unsigned int GetNewNodeId() {
            return ++node_id;
        }
        void DrawDot(const std::string &outf);
    private:
        std::set<::uint> acc_states;
        uint node_id;
        std::vector<std::tuple<uint, uint, char>> charts;


    };
}

