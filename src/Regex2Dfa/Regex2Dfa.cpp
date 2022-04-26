//
// Created by supercb on 2022-04-02.
//

#include "Regex2Dfa.h"

namespace CBCompiler {
    void Regex2Dfa::OperBNF1(std::stack<uint32> &states, std::stack<Token> &token_stack) {
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

    void Regex2Dfa::OperBNF2(std::stack<uint32> &states, std::stack<Token> &token_stack) {
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

    void Regex2Dfa::OperBNF4(std::stack<uint32> &states, std::stack<Token> &token_stack) {
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

    void Regex2Dfa::OperBNF5(std::stack<uint32> &states, std::stack<Token> &token_stack) {
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

    void Regex2Dfa::OperBNF6(std::stack<uint32> &states, std::stack<Token> &token_stack) {
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

    Regex2Dfa::Regex2Dfa(std::string_view regexstr, std::shared_ptr<CBCompiler::Graph> graph_) : graph(graph_) {

        InitTheChart();
        std::stack<uint32> states;
        std::stack<Token> token_stack;
        std::vector<Token> tokens = Preprocessing(regexstr);
        //the end of the sentence
        tokens.push_back({TOKENTYPE::OVER, "$", token_loc});
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
                    id2token[token_loc] = Token{TOKENTYPE::OVER, ""};

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
                    TranState root{graph->GetNewNodeId(), false, root_state};
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

    std::vector<Token> Regex2Dfa::Preprocessing(std::string_view str) {
        std::vector<Token> tokens;
        int i = 0;
        while (i < str.size()) {
            char ch = str.at(i);
            switch (ch) {
                case '(':
                    tokens.push_back({TOKENTYPE::LBRA, "("});
                    i++;
                    break;
                case ')':
                    tokens.push_back({TOKENTYPE::RBRA, ")"});
                    i++;
                    break;
                case '+':
                    tokens.push_back({TOKENTYPE::PLUS, "+"});
                    i++;
                    break;
                case '*':
                    tokens.push_back({TOKENTYPE::MUL, "*"});
                    i++;
                    break;
                case '?':
                    tokens.push_back({TOKENTYPE::QUE, "?"});
                    i++;
                    break;
                case '|':
                    tokens.push_back({TOKENTYPE::OR, "|"});
                    i++;
                    break;
                case '\\':
                    tokens.push_back({TOKENTYPE::ID, &"\\"[str[i + 1]]});
                    i += 2;
                    break;
                case '[': {
                    i++;
                    int j = i;
                    j++;
                    while (j < str.size() && str[j] != ']') {
                        j++;
                    }

                    //initial the followpos
                    follows[token_loc].insert({});
                    ++token_loc;

                    Token token{TOKENTYPE::ID, std::string(str.substr(i, j - i + 1)), token_loc};
                    id2token.insert({token_loc, token});

                    token.firstpos.insert(token_loc);
                    token.lastpos.insert(token_loc);
                    tokens.push_back(token);

                    i = j + 1;
                    break;
                }
                default:
                    std::string strit(1, str[i]);
                    //initial the followpos

                    ++token_loc;
                    Token token{TOKENTYPE::ID, strit, token_loc};
                    id2token.insert({token_loc, token});

                    token.firstpos.insert(token_loc);
                    token.lastpos.insert(token_loc);
                    tokens.push_back(token);
                    i++;
                    break;
            }
        }
        return tokens;
    }


/**
 * Generate the la0 chart to read the regex
 */

    inline void Regex2Dfa::AddLar0Item(int loc, TOKENTYPE token, ChartItem item) {
        ACTIONS[loc][TokenId(token)].act = item.act;
        ACTIONS[loc][TokenId(token)].val = item.val;
    }

    inline void Regex2Dfa::AddGotoItem(int loc, TOKENTYPE token, unsigned int state) {
        GOTOS[loc][TokenId(token)] = state;
    }

    void Regex2Dfa::InitTheChart() {
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
            AddLar0Item(11, TOKENTYPE::ID, {ACTION::SHIFT, 8});
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

}

void CBCompiler::Regex2Dfa::Follows2Dfa(TranState root) {

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
                graph->AddAcceptState(S.id);
                continue;
            }
            if (U_map.count(token) == 0) {
                U_map.insert({token, {loc}});
            } else {
                U_map[token].insert(loc);
            }

        }
        for (auto [token, token_locs]: U_map) {
//            dbg(token.str);
            std::set<int> unions;

            for (auto p: token_locs) {//get the union of the follows
                unions.insert(follows[p].begin(), follows[p].end());
            }

            std::vector<int> states;
            states.assign(unions.begin(), unions.end());
            TranState new_trans{0, false, states};
            if (tran_sta_set.count(new_trans) == 0) {
                new_trans.id = graph->GetNewNodeId();
                tran_sta_set.insert(new_trans);
            } else {
                new_trans.id = tran_sta_set.find(new_trans)->id;
            }
            dbg(S.states, "->", new_trans.states, token.str, "\n\n\n");
            graph->GenerateRelation(S.id, new_trans.id, token);
        }
    }
}
