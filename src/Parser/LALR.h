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
#include <vector>

#define ACCEPT_EXPR_ID 0
using json = nlohmann::json;

namespace CBCompiler {


    struct ExpressionInfor {
        std::vector<LRToken> expression;
        uint id;
    };


    enum class ActionItemType {
        Shift,
        Reduce,
        Err,
        Accept
    };

    //用于生成语法分析表的biaoxiang
    struct ActionItem {
        ActionItemType type;
        uint val;

        std::string &parse() {
        }
    };

    struct GotoItem {

    };

    class LALR {
        using uint = unsigned int;


    public:
        LALR() = delete;

        explicit LALR(json exprs);


        void DrawLR(std::string outf, bool closure);

        void DrawLALR(std::string outf);

        void GenerateParseChart(std::ofstream &out, std::map<std::string, uint> terminator2id);

    private:
        std::vector<LRItem> GetLR0Closure(const std::vector<LRItem> &coreitems);

        void GenerateNewLr0Group(LR0group *group, std::queue<LR0group *> &que);

        void GetLR0groups();

        void RemoveDuplicateTrans(uint group_id,std::string str);

        bool ComPriority(LRItem &lrItem, const std::string &look);

        void AddEdge(uint from, uint to, const std::string &token);


        void GenerateLR1Groups();

        std::set<std::string> GetFirst(const LRToken &token);

        std::set<std::string> GetFirst(const std::vector<LRToken> &tokens);

        std::vector<LRItem> GetLR1Closure(const LRItem &core_item);

        uint StateTransfer(uint id, const std::string &token);

        std::unordered_map<std::string, std::vector<LRToken>> first;

        // 记录一个左值相对应的所有表达式，ExpressionInfor还需要记录每一个表达式的编号，这个编号是为了记录一个表达式所对应的语法生成动作
        std::unordered_map<std::string, std::vector<ExpressionInfor>> expressions;

        //记录每一个表达式对应的动作
        std::unordered_map<::uint, std::string> expression_action;

        std::vector<std::tuple<uint, uint, LRToken>> trans_graph;

        std::string rootstr;
        std::vector<LR0group *> groups;
        unsigned int lr0_group_id{0};
        bool closure;
        std::unordered_map<std::string, int> priority;
        //终结符的数量
        uint terminator_cnt;
        uint nonterminator_cnt;
        std::map<std::string, uint> nonterminator2id;


    };
}
