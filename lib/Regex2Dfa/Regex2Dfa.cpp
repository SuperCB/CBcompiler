//
// Created by supercb on 2022-04-02.
//

#include "CFlex.h"
#include <cassert>
#include <fstream>
namespace CBCompiler {
    void CFlex::OperBNF1(std::stack<uint32> &states, std::stack<Token> &token_stack) {
        states.pop();
        auto token_T = token_stack.top();
        token_stack.pop();

        states.pop();
        token_stack.pop();

        states.pop();
        auto token_E = token_stack.top();
        token_stack.pop();
        uint32 new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::E)];
        states.push(new_state);

        auto firstpos = token_E.firstpos;
        auto lastpos = token_E.lastpos;
        for (auto &it: token_T.firstpos) {
            firstpos.insert(it);
        }

        for (auto &it: token_T.lastpos) {
            lastpos.insert(it);
        }
        Token token{TOKENTYPE::E, {}, 0, token_E.nullable || token_T.nullable, firstpos, lastpos};
        token_stack.push(token);
    }

    void CFlex::OperBNF2(std::stack<uint32> &states, std::stack<Token> &token_stack) {
//    dbg("E-> ET");

        states.pop();
        auto token_T = token_stack.top();
        token_stack.pop();
        states.pop();
        auto token_E = token_stack.top();
        token_stack.pop();


        auto new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::E)];
        states.push(new_state);


        auto firstpos = token_E.firstpos;
        auto lastpos = token_T.lastpos;

        if (token_E.nullable) {
            for (auto it: token_T.firstpos) {
                firstpos.insert(it);
            }
        }

        if (token_T.nullable) {
            for (auto it: token_E.lastpos) {
                lastpos.insert(it);
            }
        }
        //caculate the follow
        {
            for (auto last_l_i: token_E.lastpos) {
                for (auto first_r_i: token_T.firstpos) {
                    follows[last_l_i].insert(first_r_i);
                }
            }
        }

        Token token{TOKENTYPE::E, {}, 0, token_E.nullable && token_T.nullable, firstpos, lastpos};
        token_stack.push(token);
    }

    void CFlex::OperBNF4(std::stack<uint32> &states, std::stack<Token> &token_stack) {
        //"T-> F+"
        states.pop();
        token_stack.pop();

        states.pop();
        auto token_F = token_stack.top();
        token_stack.pop();


        auto new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::T)];
        states.push(new_state);
        {
            for (auto last_i: token_F.lastpos) {
                for (auto first_i: token_F.firstpos) {
                    follows[last_i].insert(first_i);
                }
            }
        }
        token_F.nullable = false;
        token_F.type = TOKENTYPE::T;
        token_stack.push(token_F);
    }

    void CFlex::OperBNF5(std::stack<uint32> &states, std::stack<Token> &token_stack) {
        //"T-> F*"
        states.pop();
        token_stack.pop();

        states.pop();
        auto token_F = token_stack.top();
        token_stack.pop();


        auto new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::T)];
        states.push(new_state);

        //caculate the followpos

        for (auto last_i: token_F.lastpos) {
            for (auto first_i: token_F.firstpos) {
                follows[last_i].insert(first_i);
            }
        }

        token_F.nullable = true;
        token_F.type = TOKENTYPE::T;
        token_stack.push(token_F);
    }

    void CFlex::OperBNF6(std::stack<uint32> &states, std::stack<Token> &token_stack) {
        //T->F?
        states.pop();
        token_stack.pop();

        states.pop();
        auto token_F = token_stack.top();
        token_stack.pop();


        auto new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::T)];
        states.push(new_state);

        token_F.nullable = true;
        token_F.type = TOKENTYPE::T;
        token_stack.push(token_F);
    }

    CFlex::CFlex(std::string regexstr): node_id(0) {

        InitTheChart();
        std::stack<uint32> states;
        std::stack<Token> token_stack;
        std::vector<Token> tokens = Preprocessing(regexstr);
        //the end of the sentence
        tokens.push_back({TOKENTYPE::OVER, '$', token_loc});



        // push the initial state
        states.push(0);

        bool flag = false;
        uint32 tokeni = 0;
        while (tokeni < tokens.size()) {
            auto token = tokens[tokeni];
//        std::cout << token.str << std::endl;
            TOKENTYPE token_type = token.type;
            uint32 top = states.top();
            ChartItem item = ACTIONS[top][static_cast<uint32>(token_type)];
            switch (item.act) {
                case ACTION::SHIFT:
                    states.push(item.val);
                    token_stack.push(token);
                    tokeni++;
                    break;
                case ACTION::REDUCE: {
                    uint32 new_state{};
                    switch (item.val) {
                        case 1:
                            OperBNF1(states, token_stack);
                            dbg("E-> E or T");
                            break;
                        case 2:
                            OperBNF2(states, token_stack);
                            dbg("E-> ET");
                            break;
                        case 3: {
                            states.pop();
                            auto token = token_stack.top();
                            token_stack.pop();
                            new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::E)];
                            states.push(new_state);
                            dbg("E-> T");
                            token.type = TOKENTYPE::E;
                            token_stack.push(token);
                            break;
                        }
                        case 4:
                            OperBNF4(states, token_stack);
                            dbg("T-> F+");
                            break;
                        case 5:
                            OperBNF5(states, token_stack);
                            dbg("T-> F*");
                            break;
                        case 6:
                            OperBNF6(states, token_stack);
                            dbg("T-> F?");
                            break;
                        case 7: {
                            states.pop();
                            auto token_F = token_stack.top();
                            token_stack.pop();
                            new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::T)];
                            states.push(new_state);
                            token_F.type = TOKENTYPE::T;
                            token_stack.push(token_F);
                            dbg("T-> F");
                            break;
                        }
                        case 8: {
                            states.pop();
                            token_stack.pop();
                            states.pop();
                            auto token_E = token_stack.top();
                            token_stack.pop();
                            states.pop();
                            token_stack.pop();
                            new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::F)];
                            states.push(new_state);
                            token_E.type = TOKENTYPE::F;
                            token_stack.push(token_E);
                            dbg("F-> (E)");
                            break;
                        }
                        case 9: {
                            states.pop();
                            Token id = token_stack.top();
                            token_stack.pop();
                            new_state = GOTOS[states.top()][static_cast<int>(TOKENTYPE::F)];
                            states.push(new_state);
                            id.type = TOKENTYPE::F;
//                        std::cout << id.idx << std::endl;
                            token_stack.push(id);
                            dbg("F-> id");
                            break;
                        }
                    }
                    break;
                }
                case ACTION::ACCPET: {
                    dbg("success");
                    auto fin = token_stack.top();
                    ++token_loc;
                    id2token[token_loc] = Token{TOKENTYPE::OVER, ' '};

                    for (auto i: fin.lastpos) {
                        // i should not use the set,i should use vector
                        follows[i].insert(token_loc);
                    }
                    for (auto [k, v]: follows) {

                        std::cout << k << "  ";
                        for (auto i: v) {
                            std::cout << i << " ";
                        }
                        std::cout << std::endl;
                    }
                    std::cout << token_stack.size() << std::endl;
                    std::vector<int> root_state;
                    for (auto i: fin.firstpos) {
                        root_state.push_back(i);
                    }
                    if (fin.nullable) {
                        root_state.push_back(token_loc);
                    }
                    TranState root{GetNewNodeId(), false, root_state};
                    Follows2Dfa(root);
                    flag = true;
                    break;
                }
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

    void CFlex::AddNewID(std::vector<Token> &tokens, char ch) {
        Token token{TOKENTYPE::ID, ch, token_loc};
        follows.insert({token_loc, {}});
        id2token.insert({token_loc, token});
        token.firstpos.insert(token_loc);
        token.lastpos.insert(token_loc);
        tokens.emplace_back(token);
        ++token_loc;
    }

    std::vector<Token> CFlex::Preprocessing(std::string_view str) {
        std::vector<Token> tokens;
        int i = 0;
        while (i < str.size()) {
            char ch = str.at(i);
            switch (ch) {
                case '(':
                    tokens.push_back({TOKENTYPE::LBRA, '('});
                    i++;
                    break;
                case ')':
                    tokens.push_back({TOKENTYPE::RBRA, ')'});
                    i++;
                    break;
                case '+':
                    tokens.push_back({TOKENTYPE::PLUS, '+'});
                    i++;
                    break;
                case '*':
                    tokens.push_back({TOKENTYPE::MUL, '*'});
                    i++;
                    break;
                case '?':
                    tokens.push_back({TOKENTYPE::QUE, '?'});
                    i++;
                    break;
                case '|':
                    tokens.push_back({TOKENTYPE::OR, '|'});
                    i++;
                    break;
                case '\\':
                    assert(i + 1 < str.size());
                    tokens.push_back({TOKENTYPE::LBRA, '('});
                    switch (str[i + 1]) {
                        case 'd': {
                            for (char chi = '0'; chi <= '9'; ++chi) {
                                AddNewID(tokens, chi);
                                tokens.push_back({TOKENTYPE::OR, '|'});
                            }
                            break;
                        }
                        case 'w': {
                            for (char chi = '0'; chi <= '9'; ++chi) {
                                AddNewID(tokens, chi);
                                tokens.push_back({TOKENTYPE::OR, '|'});
                            }
                            for (char chi = 'a'; chi <= 'z'; ++chi) {
                                AddNewID(tokens, chi);
                                tokens.push_back({TOKENTYPE::OR, '|'});
                            }
                            for (char chi = 'A'; chi <= 'Z'; ++chi) {
                                AddNewID(tokens, chi);
                                tokens.push_back({TOKENTYPE::OR, '|'});
                            }
                            break;
                        }
                        default: {
                            AddNewID(tokens, str[i + 1]);
                            tokens.push_back({TOKENTYPE::OR, '|'});
                            break;
                        }
                    }
                    tokens.pop_back();
                    tokens.push_back({TOKENTYPE::RBRA, ')'});
                    i += 2;
                    break;
                case '[': {
                    int j = i + 1;
                    tokens.push_back({TOKENTYPE::LBRA, '('});
                    while (j < str.size() && str[j] != ']') {
                        if (j + 1 < str.size() && str[j + 1] == '-') {
                            assert(j + 2 < str.size());
                            char begin = str[j];
                            char end = str[j + 2];
                            for (; begin <= end; ++begin) {
                                AddNewID(tokens, begin);
                                tokens.push_back({TOKENTYPE::OR, '|'});
                            }
                            j += 3;
                            continue;
                        }
                        if (str[j] == '\\') {
                            assert(j + 1 < str.size());
                            switch (str[j + 1]) {
                                case 'd': {
                                    for (char chi = '0'; chi <= '9'; ++chi) {
                                        AddNewID(tokens, chi);
                                        tokens.push_back({TOKENTYPE::OR, '|'});
                                    }
                                    break;
                                }
                                case 'w': {
                                    for (char chi = '0'; chi <= '9'; ++chi) {
                                        AddNewID(tokens, chi);
                                        tokens.push_back({TOKENTYPE::OR, '|'});
                                    }
                                    for (char chi = 'a'; chi <= 'z'; ++chi) {
                                        AddNewID(tokens, chi);
                                        tokens.push_back({TOKENTYPE::OR, '|'});
                                    }
                                    for (char chi = 'A'; chi <= 'Z'; ++chi) {
                                        AddNewID(tokens, chi);
                                        tokens.push_back({TOKENTYPE::OR, '|'});
                                    }
                                    break;
                                }
                            }
                            j += 2;
                            continue;
                        }
                        AddNewID(tokens, str[j]);
                        tokens.push_back({TOKENTYPE::OR, '|'});
                        j++;
                    }
                    tokens.pop_back();
                    tokens.push_back({TOKENTYPE::RBRA, ')'});
                    i = j + 1;
                    break;
                }
                default:
                    AddNewID(tokens, str[i]);
                    i++;
                    break;
            }
        }
        return tokens;
    }


/**
 * Generate the la0 chart to read the regex
 */

    inline void CFlex::AddLar0Item(int loc, TOKENTYPE token, ChartItem item) {
        ACTIONS[loc][TokenId(token)].act = item.act;
        ACTIONS[loc][TokenId(token)].expr = item.val;
    }

    inline void CFlex::AddGotoItem(int loc, TOKENTYPE token, unsigned int state) {
        GOTOS[loc][TokenId(token)] = state;
    }

    void CFlex::InitTheChart() {
        ACTIONS = {20, std::vector<ChartItem>(20)};

        {
            AddLar0Item(0, TOKENTYPE::ID, {ACTION::SHIFT, 2});
            AddLar0Item(0, TOKENTYPE::LBRA, {ACTION::SHIFT, 7});
            AddLar0Item(0, TOKENTYPE::E, {ACTION::REDUCE, 3});

        }
        {
            AddLar0Item(1, TOKENTYPE::ID, {ACTION::SHIFT, 2});
            AddLar0Item(1, TOKENTYPE::OR, {ACTION::SHIFT, 9});
            AddLar0Item(1, TOKENTYPE::LBRA, {ACTION::SHIFT, 7});
            AddLar0Item(1, TOKENTYPE::RBRA, {ACTION::SHIFT, 11});

        }
        {
            AddLar0Item(2, TOKENTYPE::ID, {ACTION::REDUCE, 9});
            AddLar0Item(2, TOKENTYPE::PLUS, {ACTION::REDUCE, 9});
            AddLar0Item(2, TOKENTYPE::QUE, {ACTION::REDUCE, 9});
            AddLar0Item(2, TOKENTYPE::MUL, {ACTION::REDUCE, 9});
            AddLar0Item(2, TOKENTYPE::OR, {ACTION::REDUCE, 9});
            AddLar0Item(2, TOKENTYPE::LBRA, {ACTION::REDUCE, 9});
            AddLar0Item(2, TOKENTYPE::RBRA, {ACTION::REDUCE, 9});
            AddLar0Item(2, TOKENTYPE::OVER, {ACTION::REDUCE, 9});
        }
        {
            AddLar0Item(3, TOKENTYPE::ID, {ACTION::SHIFT, 2});
            AddLar0Item(3, TOKENTYPE::OR, {ACTION::SHIFT, 9});
            AddLar0Item(3, TOKENTYPE::LBRA, {ACTION::SHIFT, 7});
            AddLar0Item(3, TOKENTYPE::OVER, {ACTION::ACCPET, 0});
        }
        {
            AddLar0Item(4, TOKENTYPE::ID, {ACTION::REDUCE, 7});
            AddLar0Item(4, TOKENTYPE::PLUS, {ACTION::SHIFT, 5});
            AddLar0Item(4, TOKENTYPE::QUE, {ACTION::SHIFT, 12});
            AddLar0Item(4, TOKENTYPE::MUL, {ACTION::SHIFT, 6});
            AddLar0Item(4, TOKENTYPE::OR, {ACTION::REDUCE, 7});
            AddLar0Item(4, TOKENTYPE::LBRA, {ACTION::REDUCE, 7});
            AddLar0Item(4, TOKENTYPE::RBRA, {ACTION::REDUCE, 7});
            AddLar0Item(4, TOKENTYPE::OVER, {ACTION::REDUCE, 7});
        }
        {
            AddLar0Item(5, TOKENTYPE::ID, {ACTION::REDUCE, 4});
            AddLar0Item(5, TOKENTYPE::OR, {ACTION::REDUCE, 4});
            AddLar0Item(5, TOKENTYPE::LBRA, {ACTION::REDUCE, 4});
            AddLar0Item(5, TOKENTYPE::RBRA, {ACTION::REDUCE, 4});

            AddLar0Item(5, TOKENTYPE::OVER, {ACTION::REDUCE, 4});
        }
        {
            AddLar0Item(6, TOKENTYPE::ID, {ACTION::REDUCE, 5});
            AddLar0Item(6, TOKENTYPE::OR, {ACTION::REDUCE, 5});
            AddLar0Item(6, TOKENTYPE::LBRA, {ACTION::REDUCE, 5});
            AddLar0Item(6, TOKENTYPE::RBRA, {ACTION::REDUCE, 5});

            AddLar0Item(6, TOKENTYPE::OVER, {ACTION::REDUCE, 5});
        }
        {
            AddLar0Item(7, TOKENTYPE::ID, {ACTION::SHIFT, 2});
            AddLar0Item(7, TOKENTYPE::LBRA, {ACTION::SHIFT, 7});
        }
        {
            AddLar0Item(8, TOKENTYPE::ID, {ACTION::REDUCE, 2});
            AddLar0Item(8, TOKENTYPE::OR, {ACTION::REDUCE, 2});
            AddLar0Item(8, TOKENTYPE::LBRA, {ACTION::REDUCE, 2});
            AddLar0Item(8, TOKENTYPE::RBRA, {ACTION::REDUCE, 2});
            AddLar0Item(8, TOKENTYPE::OVER, {ACTION::REDUCE, 2});
        }
        {
            AddLar0Item(9, TOKENTYPE::ID, {ACTION::SHIFT, 2});

            AddLar0Item(9, TOKENTYPE::LBRA, {ACTION::SHIFT, 7});
            AddLar0Item(9, TOKENTYPE::OVER, {ACTION::REDUCE, 7});
        }
        {
            AddLar0Item(10, TOKENTYPE::ID, {ACTION::REDUCE, 3});
            AddLar0Item(10, TOKENTYPE::OR, {ACTION::REDUCE, 3});
            AddLar0Item(10, TOKENTYPE::LBRA, {ACTION::REDUCE, 3});
            AddLar0Item(10, TOKENTYPE::RBRA, {ACTION::REDUCE, 3});
            AddLar0Item(10, TOKENTYPE::OVER, {ACTION::REDUCE, 3});

        }
        {
            AddLar0Item(11, TOKENTYPE::ID, {ACTION::REDUCE, 8});
            AddLar0Item(11, TOKENTYPE::PLUS, {ACTION::REDUCE, 8});
            AddLar0Item(11, TOKENTYPE::QUE, {ACTION::REDUCE, 8});
            AddLar0Item(11, TOKENTYPE::MUL, {ACTION::REDUCE, 8});
            AddLar0Item(11, TOKENTYPE::OR, {ACTION::REDUCE, 8});
            AddLar0Item(11, TOKENTYPE::LBRA, {ACTION::REDUCE, 8});
            AddLar0Item(11, TOKENTYPE::RBRA, {ACTION::REDUCE, 8});
            AddLar0Item(11, TOKENTYPE::OVER, {ACTION::REDUCE, 8});
        }
        {
            AddLar0Item(12, TOKENTYPE::ID, {ACTION::REDUCE, 6});
            AddLar0Item(12, TOKENTYPE::OR, {ACTION::REDUCE, 6});
            AddLar0Item(12, TOKENTYPE::LBRA, {ACTION::REDUCE, 6});
            AddLar0Item(12, TOKENTYPE::RBRA, {ACTION::REDUCE, 6});
            AddLar0Item(12, TOKENTYPE::OVER, {ACTION::REDUCE, 6});
        }
        {
            AddLar0Item(13, TOKENTYPE::ID, {ACTION::REDUCE, 1});
            AddLar0Item(13, TOKENTYPE::OR, {ACTION::REDUCE, 1});
            AddLar0Item(13, TOKENTYPE::LBRA, {ACTION::REDUCE, 1});
            AddLar0Item(13, TOKENTYPE::RBRA, {ACTION::REDUCE, 1});
            AddLar0Item(13, TOKENTYPE::OVER, {ACTION::REDUCE, 1});
        }


        GOTOS = {20, std::vector<unsigned int>(20)};
        {
            AddGotoItem(0, TOKENTYPE::E, 3);
            AddGotoItem(0, TOKENTYPE::F, 4);
            AddGotoItem(0, TOKENTYPE::T, 10);
        }
        {
            AddGotoItem(1, TOKENTYPE::F, 4);
            AddGotoItem(1, TOKENTYPE::T, 8);
        }
        {
            AddGotoItem(3, TOKENTYPE::F, 4);
            AddGotoItem(3, TOKENTYPE::T, 8);
        }
        {
            AddGotoItem(7, TOKENTYPE::E, 1);
            AddGotoItem(7, TOKENTYPE::F, 4);
            AddGotoItem(7, TOKENTYPE::T, 10);
        }
        AddGotoItem(9, TOKENTYPE::T, 13);
        AddGotoItem(9, TOKENTYPE::F, 4);

    }


    void CFlex::Follows2Dfa(TranState root) {

        std::function<bool(std::set<TranState>)> checkstates = [](std::set<TranState> state_set) -> bool {
            bool flag = true;
            for (auto &transtate: state_set) {
                if (!transtate.flag) {
                    flag = false;
                    break;
                }
            }
            return flag;
        };


        std::set<TranState> tran_sta_set;
        tran_sta_set.insert(root);

        while (!tran_sta_set.empty()) {

            auto iterator = tran_sta_set.begin();
            // get the unmarked state

            while (iterator != tran_sta_set.end() && iterator->flag)++iterator;
            if (iterator == tran_sta_set.end())break;
            auto S = *iterator;

            S.flag = true;
            tran_sta_set.erase(iterator);
            tran_sta_set.insert(S);

            std::map<Token, std::set<int>> U_map{};
            // get all union of input token
            for (auto &loc: S.states) {
                auto token = id2token[loc];
                if (token.type == TOKENTYPE::OVER) {
                    //if the state can tranfer to end state,so we can get mark this state as accept state
                    dbg(S.states, "is the accpet state");

                    AddAcceptState(S.id);
                    continue;
                }
                if (U_map.count(token) == 0) {
                    U_map.insert({token, {loc}});
                } else {
                    U_map[token].insert(loc);
                }

            }
            for (auto [token, token_locs]: U_map) {
                std::set<int> unions;
                for (auto p: token_locs) {
                    unions.insert(follows[p].begin(), follows[p].end());
                }
                std::vector<int> states;
                states.assign(unions.begin(), unions.end());
                TranState new_trans{0, false, states};
                if (tran_sta_set.count(new_trans) == 0) {
                    new_trans.id = GetNewNodeId();
                    tran_sta_set.insert(new_trans);
                } else {
                    new_trans.id = tran_sta_set.find(new_trans)->id;
                }
                dbg(S.states, "->", new_trans.states, token.ch, "\n\n\n");
                GenerateRelation(S.id, new_trans.id, token);
            }
        }
    }
}

template<typename ... Args>
std::string string_format(const std::string &format, Args ... args) {
    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
    // unique_ptr<char[]> buf(new char[size]);
    char bytes[size];
    snprintf(bytes, size, format.c_str(), args ...);
    return bytes;
}

void CBCompiler::CFlex::DrawDot(const std::string &outf) {

    assert(node_id >= 1);
    std::ofstream out(outf);
    out << "digraph G {" << std::endl;
    if (acc_states.count(1)) {
        out << "node_1 [label=StartOrAccept shape=doublecircle color=green];" << std::endl;
    } else { out << "node_1 [label=Start shape=doublecircle color=blue];" << std::endl; }
    for (uint i = 2; i <= node_id; ++i) {
        if (acc_states.count(i)) {
            out << string_format("node_%d [label=Accept shape=%s color=red fillcolor = pink style = filled];", i, "doublecircle") << std::endl;
        } else {
            out << string_format("node_%d [label=%d shape=%s];", i, i, "circle") << std::endl;
        }
    }
    for (auto &tu: charts) {
        out << string_format("node_%d ->node_%d [label=%c];", std::get<0>(tu), std::get<1>(tu), std::get<2>(tu))
            << std::endl;
    }

    out << "}" << std::endl;
    out.close();
}

void CBCompiler::CFlex::GenerateRelation(uint from, uint to, const Token &token) {
    std::tuple<::uint, ::uint, char> tu{from, to, token.ch};
    charts.emplace_back(tu);
    regexchart[from].insert({token.ch, to});
}

/**
 * 验证str是否符合正则表达式标准
 * @param str
 * @return
 */
bool CBCompiler::CFlex::matched(std::string str) {
    uint state = 1;
    uint loc = 0;
    while (loc < str.size()) {
        char ch = str.at(loc);
        if (regexchart[state].count(ch) == 0) {
            return false;
        }
        state = regexchart[state][ch];
        ++loc;
    }
    if (acc_states.count(state) > 0) { return true; }
    else { return false; }
}

