//
// Created by supercb on 2022-04-02.
//

#pragma once
#define DBG_MACRO_NO_WARNING

#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include "dbg.h"
#include "Graph.h"
#include "DfaUtil.h"
namespace DFA {
    class Regex2Dfa {
        using uint8 = uint8_t;
        using uint32 = unsigned int;
    public:
        Regex2Dfa(std::string_view regexstr);

        Regex2Dfa(const Regex2Dfa &regex2Dfa) = delete;

        Regex2Dfa operator=(const Regex2Dfa &regex2Dfa) = delete;


        void InitTheChart();

        //Trans token to id
        inline int TokenId(TOKENTYPE regexToken) {
            return static_cast<int>(regexToken);
        }


    private:
        void AddLar0Item(int loc, TOKENTYPE token, ChartItem item);

        std::vector<Token> Preprocessing(std::string_view str);

        void AddGotoItem(int loc, TOKENTYPE token, unsigned int state);


        void OperBNF1(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void OperBNF2(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void OperBNF4(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void OperBNF5(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void OperBNF6(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void Follows2Dfa(TranState root);


        CBCompiler::Graph graph;
        unsigned int token_loc{0};//used when processing
        int graph_id{0};
        std::vector<std::vector<ChartItem>> ACTIONS;
        std::vector<std::vector<unsigned int >> GOTOS;
        std::unordered_map<unsigned int, std::set<uint32>> follows;
        std::map<uint32 , Token> token_map;
        std::map<uint32 , Token> id2token;


        void GenerateRelation(int from, int to, const Token &token);
    };
}
