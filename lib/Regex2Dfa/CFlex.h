//
// Created by supercb on 2022-04-02.
//

#pragma once
#define DBG_MACRO_NO_WARNING

#define EMPTY_TOKEN ' '

#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include "dbg.h"
#include "DfaUtil.h"

namespace CBCompiler {
    class CFlex {
        using uint8 = uint8_t;
        using uint32 = unsigned int;

    public:
        CFlex(std::string regexstr);

//        CFlex(const CFlex &regex2Dfa) = delete;

        CFlex operator=(const CFlex &regex2Dfa) = delete;


        void InitTheChart();

        //Trans token to id
        inline int TokenId(TOKENTYPE regexToken) {
            return static_cast<int>(regexToken);
        }

        void DrawDot(const std::string &outf);

        bool matched(std::string str);

    private:


        //accept项
        std::set<::uint> acc_states;
        uint node_id;


        std::vector<std::tuple<uint, uint, char>> charts;

        inline unsigned int GetNewNodeId() {
            return ++node_id;
        }

        inline void AddAcceptState(uint id) {
            acc_states.insert(id);
        };


        void GenerateRelation(uint from, uint to,const Token &token);

        void AddLar0Item(int loc, TOKENTYPE token, ChartItem item);

        std::vector<Token> Preprocessing(std::string_view str);

        void AddGotoItem(int loc, TOKENTYPE token, unsigned int state);

        void OperBNF1(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void OperBNF2(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void OperBNF4(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void OperBNF5(std::stack<uint32> &states, std::stack<Token> &token_stack);

        void OperBNF6(std::stack<uint32> &states, std::stack<Token> &token_stack);

        //生成自动机的函数
        void Follows2Dfa(TranState root);

        void AddNewID(std::vector<Token> &tokens, char ch);


        //  std::shared_ptr<CBCompiler::Graph> graph;
        unsigned int token_loc{0};//used when processing
        int graph_id{0};
        std::vector<std::vector<ChartItem>> ACTIONS;
        std::vector<std::vector<unsigned int >> GOTOS;
        std::unordered_map<unsigned int, std::set<uint32>> follows;
        std::map<uint32, Token> token_map;
        std::map<uint32, Token> id2token;

        std::map<uint, std::unordered_map<char, uint>> regexchart;
    };
}
