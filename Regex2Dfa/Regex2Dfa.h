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

namespace DFA {
    enum class ACTION {
        SHIFT,
        REDUCE,
        ACCPET,
        ERR
    };

    enum class TOKENTYPE {
        ID = 1,
        PLUS,
        QUE,
        MUL,
        OR,
        LBRA,
        RBRA,
        E,
        F,
        T,
        OVER
    };

    struct ChartItem {
        ACTION act;
        uint8_t val;

        ChartItem() : act(ACTION::ERR), val(-1) {}

        ChartItem(ACTION act_, uint8_t val_) : act(act_), val(val_) {
        };
    };

    struct Token {
        TOKENTYPE type;
        std::string str;
        unsigned int loc;
        bool nullable;
        std::set<unsigned int> firstpos;
        std::set<unsigned int> lastpos;

        bool operator<(const Token &r) const {
            return str < r.str;
        }
        std::vector<char> parseToken()const {
            //easy type
            std::vector<char> res;
            for (auto &ch: str) {
                res.push_back(ch);
            }
            return res;
        }
    };

    struct TranState {
        int id;//for generating the graph
        bool flag;
        std::vector<int> states;

        bool operator<(const TranState &r) const {
            std::function<int(std::vector<int>)> vec2va = [](std::vector<int> vec) -> int {
                int val = 0;
                std::sort(vec.begin(), vec.end());
                for (auto v: vec) {
                    val = val * 10 + v;
                }
                return val;
            };
            return vec2va(this->states) < vec2va(r.states);
        }
    };
}


namespace DFA {
    class Regex2Dfa {
        using uint8 = uint8_t;
        using uint = unsigned int;
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


        void OperBNF1(std::stack<uint> &states, std::stack<Token> &token_stack);

        void OperBNF2(std::stack<uint> &states, std::stack<Token> &token_stack);

        void OperBNF4(std::stack<uint> &states, std::stack<Token> &token_stack);

        void OperBNF5(std::stack<uint> &states, std::stack<Token> &token_stack);

        void OperBNF6(std::stack<uint> &states, std::stack<Token> &token_stack);

        void Follows2Dfa(TranState root);


        CBCompiler::Graph graph;
        unsigned int token_loc{0};//used when processing
        int graph_id{0};
        std::vector<std::vector<ChartItem>> ACTIONS;
        std::vector<std::vector<unsigned int >> GOTOS;
        std::unordered_map<unsigned int, std::set<int >> follows;
        std::map<int, Token> token_map;
        std::map<int32_t, Token> id2token;


        void GenerateRelation(int from, int to, const Token &token);
    };
}
