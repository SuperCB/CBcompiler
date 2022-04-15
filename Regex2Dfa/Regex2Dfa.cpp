//
// Created by supercb on 2022-04-02.
//

#include "Regex2Dfa.h"

Regex2Dfa::Regex2Dfa(std::string_view regexstr) : idx(0) {
    InitTheChart();

    e = new int[2 * size];
    ne = new int[2 * size];
    h = new int[size];

    std::stack<uint> states;
    std::stack<Token> token_stack;
    std::vector<Token> tokens = Preprocessing(regexstr);
    tokens.push_back({RegexTOKEN::OVER, "$"});
    for (auto token: tokens) {
        std::cout << token.str << std::endl;
    }
    states.push(0);
    bool flag = false;
    uint tokeni = 0;
    while (tokeni < tokens.size()) {
        auto token = tokens[tokeni];
        std::cout << token.str << std::endl;
        RegexTOKEN token_type = token.type;
        uint top = states.top();
        ChartItem item = ACTIONS[top][static_cast<uint>(token_type)];
        switch (item.act) {
            case ACTION::SHIFT:
                states.push(item.val);
                token_stack.push(token);
                tokeni++;
                break;
            case ACTION::REDUCE: {
                uint new_state{};
                switch (item.val) {
                    case 1:
                        states.pop();
                        token_stack.pop();
                        states.pop();
                        token_stack.pop();
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::E)];
                        states.push(new_state);
                        token_stack.push({RegexTOKEN::E, {}});

                        dbg("E-> E or T");
                        break;
                    case 2:
                        states.pop();
                        token_stack.pop();
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::E)];
                        states.push(new_state);
                        token_stack.push({RegexTOKEN::E, {}});

                        dbg("E-> ET");

                        break;
                    case 3:
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::E)];
                        states.push(new_state);
                        dbg("E-> T");
                        token_stack.push({RegexTOKEN::E, {}});

                        break;
                    case 4:
                        states.pop();
                        token_stack.pop();
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::T)];
                        states.push(new_state);
                        token_stack.push({RegexTOKEN::T, {}});

                        dbg("T-> F+");

                        break;
                    case 5:
                        states.pop();
                        token_stack.pop();
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::T)];
                        states.push(new_state);
                        token_stack.push({RegexTOKEN::T, {}});

                        dbg("T-> F*");
                        break;
                    case 6:
                        states.pop();
                        token_stack.pop();
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::T)];
                        states.push(new_state);
                        token_stack.push({RegexTOKEN::T, {}});

                        dbg("T-> F?");

                        break;
                    case 7:
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::T)];
                        states.push(new_state);
                        token_stack.push({RegexTOKEN::T, {}});

                        dbg("T-> F");

                        break;
                    case 8:
                        states.pop();
                        token_stack.pop();
                        states.pop();
                        token_stack.pop();
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::F)];

                        states.push(new_state);
                        token_stack.push({RegexTOKEN::F, {}});

                        dbg("F-> (E)");

                        break;
                    case 9:
                        states.pop();
                        token_stack.pop();
                        new_state = GOTOS[states.top()][static_cast<int>(RegexTOKEN::F)];
                        states.push(new_state);
                        token_stack.push({RegexTOKEN::F, {}});

                        dbg("F-> id");
                        break;
                }
                break;
            }
            case ACTION::ACCPET:
                dbg("success");
                flag = true;
                break;
            case ACTION::ERR:
                dbg("wrong regex input");
                flag = true;
                break;
        }
        if (flag) {
            break;
        }
    }

}

std::vector<Token> Regex2Dfa::Preprocessing(std::string_view str) {
    std::vector<Token> tokens;
    int i = 0;
    while (i < str.size()) {
        char ch = str.at(i);
        switch (ch) {
            case '(':
                tokens.push_back({RegexTOKEN::LBRA, "("});
                i++;
                break;
            case ')':
                tokens.push_back({RegexTOKEN::RBRA, ")"});
                i++;
                break;
            case '+':
                tokens.push_back({RegexTOKEN::PLUS, "+"});
                i++;
                break;
            case '*':
                tokens.push_back({RegexTOKEN::MUL, "*"});
                i++;
                break;
            case '?':
                tokens.push_back({RegexTOKEN::QUE, "?"});
                i++;
                break;
            case '|':
                tokens.push_back({RegexTOKEN::OR, "|"});
                i++;
                break;
            case '\\':
                tokens.push_back({RegexTOKEN::ID, &"\\"[str[i + 1]]});
                i += 2;
                break;
            case '[': {
                i++;
                int j = i;
                j++;
                while (j < str.size() && str[j] != ']') {
                    j++;
                }
                tokens.push_back({RegexTOKEN::ID, std::string(str.substr(i, j - i + 1))});
                i = j + 1;
                break;
            }
            default:
                std::string strit(1, str[i]);
                tokens.push_back({RegexTOKEN::ID, strit});
                i++;
                break;
        }
    }
    return tokens;
}

inline bool Regex2Dfa::IsSpecialOperator(char op) {

    if (op == '*' || op == '|' || op == '+')
        return true;
    else
        return false;
}

bool Regex2Dfa::isidentityChar(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
        return true;
    else
        return false;
}

void Regex2Dfa::AddEdge(int a, int b, char ch) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx;
    ++idx;
}

Regex2Dfa::~Regex2Dfa() {
    delete[]e;
    delete[]ne;
    delete[]h;
}

int Regex2Dfa::NewNode() {
    return ++node_id;
}

/**
 * Generate the la0 chart to read the regex
 */

inline void Regex2Dfa::AddLar0Item(int loc, RegexTOKEN token, ChartItem item) {
    ACTIONS[loc][TokenId(token)].act = item.act;
    ACTIONS[loc][TokenId(token)].val = item.val;
}

inline void Regex2Dfa::AddGotoItem(int loc, RegexTOKEN token, unsigned int state) {
    GOTOS[loc][TokenId(token)] = state;
}

void Regex2Dfa::InitTheChart() {
    ACTIONS = {20, std::vector<ChartItem>(20)};

    {
        AddLar0Item(0, RegexTOKEN::ID, {ACTION::SHIFT, 2});
        AddLar0Item(0, RegexTOKEN::LBRA, {ACTION::SHIFT, 7});
        AddLar0Item(0, RegexTOKEN::E, {ACTION::REDUCE, 3});

    }
    {
        AddLar0Item(1, RegexTOKEN::ID, {ACTION::SHIFT, 2});
        AddLar0Item(1, RegexTOKEN::OR, {ACTION::SHIFT, 9});
        AddLar0Item(1, RegexTOKEN::LBRA, {ACTION::SHIFT, 7});
        AddLar0Item(1, RegexTOKEN::RBRA, {ACTION::SHIFT, 11});

    }
    {
        AddLar0Item(2, RegexTOKEN::ID, {ACTION::REDUCE, 9});
        AddLar0Item(2, RegexTOKEN::PLUS, {ACTION::REDUCE, 9});
        AddLar0Item(2, RegexTOKEN::QUE, {ACTION::REDUCE, 9});
        AddLar0Item(2, RegexTOKEN::MUL, {ACTION::REDUCE, 9});
        AddLar0Item(2, RegexTOKEN::OR, {ACTION::REDUCE, 9});
        AddLar0Item(2, RegexTOKEN::LBRA, {ACTION::REDUCE, 9});
        AddLar0Item(2, RegexTOKEN::RBRA, {ACTION::REDUCE, 9});
        AddLar0Item(2, RegexTOKEN::OVER, {ACTION::REDUCE, 9});
    }
    {
        AddLar0Item(3, RegexTOKEN::ID, {ACTION::SHIFT, 2});
        AddLar0Item(3, RegexTOKEN::OR, {ACTION::SHIFT, 9});
        AddLar0Item(3, RegexTOKEN::LBRA, {ACTION::SHIFT, 7});
        AddLar0Item(3, RegexTOKEN::OVER, {ACTION::ACCPET, 0});
    }
    {
        AddLar0Item(4, RegexTOKEN::ID, {ACTION::REDUCE, 7});
        AddLar0Item(4, RegexTOKEN::PLUS, {ACTION::SHIFT, 5});
        AddLar0Item(4, RegexTOKEN::QUE, {ACTION::SHIFT, 12});
        AddLar0Item(4, RegexTOKEN::MUL, {ACTION::SHIFT, 6});
        AddLar0Item(4, RegexTOKEN::OR, {ACTION::REDUCE, 7});
        AddLar0Item(4, RegexTOKEN::LBRA, {ACTION::REDUCE, 7});
        AddLar0Item(4, RegexTOKEN::RBRA, {ACTION::REDUCE, 7});
        AddLar0Item(4, RegexTOKEN::OVER, {ACTION::REDUCE, 7});
    }
    {
        AddLar0Item(5, RegexTOKEN::ID, {ACTION::REDUCE, 4});
        AddLar0Item(5, RegexTOKEN::OR, {ACTION::REDUCE, 4});
        AddLar0Item(5, RegexTOKEN::LBRA, {ACTION::REDUCE, 4});
        AddLar0Item(5, RegexTOKEN::OVER, {ACTION::REDUCE, 4});
    }
    {
        AddLar0Item(6, RegexTOKEN::ID, {ACTION::REDUCE, 5});
        AddLar0Item(6, RegexTOKEN::OR, {ACTION::REDUCE, 5});
        AddLar0Item(6, RegexTOKEN::LBRA, {ACTION::REDUCE, 5});
        AddLar0Item(6, RegexTOKEN::OVER, {ACTION::REDUCE, 5});
    }
    {
        AddLar0Item(7, RegexTOKEN::ID, {ACTION::SHIFT, 2});
        AddLar0Item(7, RegexTOKEN::LBRA, {ACTION::SHIFT, 7});
    }
    {
        AddLar0Item(8, RegexTOKEN::ID, {ACTION::REDUCE, 2});
        AddLar0Item(8, RegexTOKEN::OR, {ACTION::REDUCE, 2});
        AddLar0Item(8, RegexTOKEN::LBRA, {ACTION::REDUCE, 2});
        AddLar0Item(8, RegexTOKEN::RBRA, {ACTION::REDUCE, 2});
        AddLar0Item(8, RegexTOKEN::OVER, {ACTION::REDUCE, 2});
    }
    {
        AddLar0Item(9, RegexTOKEN::ID, {ACTION::SHIFT, 7});
        AddLar0Item(9, RegexTOKEN::PLUS, {ACTION::REDUCE, 5});
        AddLar0Item(9, RegexTOKEN::QUE, {ACTION::REDUCE, 12});
        AddLar0Item(9, RegexTOKEN::MUL, {ACTION::REDUCE, 6});
        AddLar0Item(9, RegexTOKEN::OR, {ACTION::REDUCE, 7});
        AddLar0Item(9, RegexTOKEN::LBRA, {ACTION::REDUCE, 7});
        AddLar0Item(9, RegexTOKEN::RBRA, {ACTION::REDUCE, 7});
        AddLar0Item(9, RegexTOKEN::OVER, {ACTION::REDUCE, 7});
    }
    {
        AddLar0Item(10, RegexTOKEN::ID, {ACTION::REDUCE, 3});
        AddLar0Item(10, RegexTOKEN::OR, {ACTION::REDUCE, 3});
        AddLar0Item(10, RegexTOKEN::LBRA, {ACTION::REDUCE, 3});
        AddLar0Item(10, RegexTOKEN::RBRA, {ACTION::REDUCE, 3});
        AddLar0Item(10, RegexTOKEN::OVER, {ACTION::REDUCE, 3});

    }
    {
        AddLar0Item(11, RegexTOKEN::ID, {ACTION::SHIFT, 8});
        AddLar0Item(11, RegexTOKEN::PLUS, {ACTION::REDUCE, 8});
        AddLar0Item(11, RegexTOKEN::QUE, {ACTION::REDUCE, 8});
        AddLar0Item(11, RegexTOKEN::MUL, {ACTION::REDUCE, 8});
        AddLar0Item(11, RegexTOKEN::OR, {ACTION::REDUCE, 8});
        AddLar0Item(11, RegexTOKEN::LBRA, {ACTION::REDUCE, 8});
        AddLar0Item(11, RegexTOKEN::RBRA, {ACTION::REDUCE, 8});
        AddLar0Item(11, RegexTOKEN::OVER, {ACTION::REDUCE, 8});
    }
    {
        AddLar0Item(12, RegexTOKEN::ID, {ACTION::REDUCE, 6});
        AddLar0Item(12, RegexTOKEN::OR, {ACTION::REDUCE, 6});
        AddLar0Item(12, RegexTOKEN::LBRA, {ACTION::REDUCE, 6});
        AddLar0Item(12, RegexTOKEN::OVER, {ACTION::REDUCE, 6});
    }
    {
        AddLar0Item(13, RegexTOKEN::ID, {ACTION::REDUCE, 1});
        AddLar0Item(13, RegexTOKEN::OR, {ACTION::REDUCE, 1});
        AddLar0Item(13, RegexTOKEN::LBRA, {ACTION::REDUCE, 1});
        AddLar0Item(13, RegexTOKEN::RBRA, {ACTION::REDUCE, 1});
        AddLar0Item(13, RegexTOKEN::OVER, {ACTION::REDUCE, 1});
    }


    GOTOS = {20, std::vector<unsigned int>(20)};
    {
        AddGotoItem(0, RegexTOKEN::E, 3);
        AddGotoItem(0, RegexTOKEN::F, 4);
        AddGotoItem(0, RegexTOKEN::T, 10);
    }
    {
        AddGotoItem(1, RegexTOKEN::F, 4);
        AddGotoItem(1, RegexTOKEN::T, 8);
    }
    {
        AddGotoItem(3, RegexTOKEN::F, 4);
        AddGotoItem(3, RegexTOKEN::T, 8);
    }
    {
        AddGotoItem(7, RegexTOKEN::E, 1);
        AddGotoItem(7, RegexTOKEN::F, 4);
        AddGotoItem(7, RegexTOKEN::T, 10);
    }
    AddGotoItem(9, RegexTOKEN::T, 13);
}




