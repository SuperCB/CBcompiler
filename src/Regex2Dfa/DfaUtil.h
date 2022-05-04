//
// Created by supercb on 22-4-24.
//
#pragma once
#include <utility>
#include <vector>
#include <set>
#include <functional>

namespace CBCompiler {
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

}
namespace CBCompiler{

    class TranState {
    public:
        uint id;//for generating the trans_chart
        bool flag;
        std::vector<int> states;
        TranState():id(0),flag(false),states({}){};
        TranState(uint id_,bool flag_,std::vector<int>states_):id(id_),flag(flag_),states(std::move(states_)) {};

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