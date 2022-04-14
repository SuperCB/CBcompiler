//
// Created by supercb on 2022-04-02.
//

#ifndef CBCOMPILER_REGEX2DFA_H
#define CBCOMPILER_REGEX2DFA_H

#include <string_view>
#include <string>
#include <vector>
#include <stack>

enum class ACTION {
    SHIFT,
    REDUCE,
    ACCPET,
    ERR
};

enum class RegexTOKEN {
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

    ChartItem &operator=(const ChartItem &chartItem) {
        act = chartItem.act;
        val = chartItem.val;
    };
};

struct Token {
    RegexTOKEN type;
    std::string_view str;
};

class Regex2Dfa {
    using uint8 = uint8_t;
public:
    Regex2Dfa(std::string_view regexstr);

    Regex2Dfa(const Regex2Dfa &regex2Dfa) = delete;

    Regex2Dfa operator=(const Regex2Dfa &regex2Dfa) = delete;

    ~Regex2Dfa();

    static inline bool IsSpecialOperator(char op);

    static inline bool isidentityChar(char ch);

    int NewNode();

    void AddEdge(int a, int b, char ch);

    void InitTheChart();

    //Trans token to id
    inline int TokenId(RegexTOKEN regexToken) {
        return static_cast<int>(regexToken);
    }

    int node_id;//the id of node
    unsigned int start_id, end_id;
private:
    int idx;
    int *e, *ne, *h;
    const int size = 10000;
    std::vector<std::vector<ChartItem>> lr0echart;

    void AddLar0Item(int loc, RegexTOKEN token, ChartItem item);

    std::vector<Token> Preprocessing(std::string_view str);
};


#endif //CBCOMPILER_REGEX2DFA_H
