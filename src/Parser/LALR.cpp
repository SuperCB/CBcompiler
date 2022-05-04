//
// Created by supercb on 22-4-26.
//

#include "LALR.h"


CBCompiler::LALR::LALR(std::string_view addr) {
    json bnfs;

    std::ifstream jfile(addr.data());
    jfile >> bnfs;
    auto rootExpr = bnfs.find("root");
    assert(rootExpr != bnfs.end());
    rootstr = rootExpr.value();


    //first get all unendtoken
    for (auto iter = bnfs.begin(); iter != bnfs.end(); ++iter) {
        if (iter == rootExpr)continue;
        assert(typeid(iter.key()) == typeid(std::string));
        std::string lv = iter.key();
        expressions.insert({lv, {}});
    }
    // second get all endtoken
    for (auto iter = bnfs.begin(); iter != bnfs.end(); ++iter) {
        if (iter == rootExpr)continue;
        auto rv = iter.value();
        auto exprlist = rv["values"];
        for (auto exiter = exprlist.begin(); exiter != exprlist.end(); ++exiter) {
            std::vector<LRToken> lrtokens;
            for (auto exi = exiter.value().begin(); exi != exiter.value().end(); ++exi) {

                std::string little_expr = exi.value();
                LRType type_;
                if (expressions.count(little_expr) == 0) {
                    type_ = LRType::END;
                } else {
                    type_ = LRType::UNEND;
                }
                dbg(little_expr);
                lrtokens.emplace_back(type_, little_expr);
            }
            expressions[iter.key()].push_back(std::move(lrtokens));
        }
    }
    GetLR0groups();
    GenerateLR1Groups();
}

void CBCompiler::LALR::GetLR0groups() {

    CBCompiler::LRItem root("root", {{LRType::UNEND, rootstr}}, 0);

    LR0group *sta = new LR0group({root});
    std::queue<CBCompiler::LR0group *> que;

    sta->id = lr0_group_id++;

    que.push(sta);//jia ru zengguangwenfa
    groups.emplace_back(sta);

    while (!que.empty()) {
        auto top_lro_group = que.front();
        que.pop();
        auto closure_items = GetLR0Closure(top_lro_group->core_items);
        std::unordered_map<std::string, std::vector<unsigned int>> token2lr0item;
        for (unsigned int i = 0; i < closure_items.size(); ++i) {
            LRItem lr0item = closure_items[i];
            LRToken lr0token;
            bool flag = lr0item.TokenAfterPos(lr0token);
            if (!flag) {
//                dbg("Accept");
            } else {
                token2lr0item[lr0token.str].push_back(i);
            }
        }
        for (auto &[k, ids]: token2lr0item) {
            std::vector<LRItem> n_group_cores;
            for (auto &i: ids) {
                closure_items[i].PointLocAdd();
                n_group_cores.push_back(closure_items[i]);
            }
            LR0group *ne_lr0_group = new LR0group(n_group_cores);
            GenerateNewLr0Group(ne_lr0_group, que);


            AddEdge(top_lro_group->id, ne_lr0_group->id, k);
        }
    }

    {
        auto cmp = [](LR0group *l, LR0group *r) -> bool {
            return l->id < r->id;
        };
        std::sort(groups.begin(), groups.end(), cmp);
    }
}


std::vector<CBCompiler::LRItem> CBCompiler::LALR::GetLR0Closure(const std::vector<LRItem> &coreitems) {
    SetVector lr0items;
    std::queue<LRItem> itemsque;

    for (auto &core_item: coreitems) {
        itemsque.push(core_item);
        lr0items.push_back(core_item);
    }
    while (!itemsque.empty()) {
        auto top = itemsque.front();
        itemsque.pop();
        LRToken token;
        bool flag = top.TokenAfterPos(token);
        if (!flag) {
//            dbg("Accept ");
        } else {
            if (token.IsUnend()) {
//                dbg("unend token", token.str);
                for (auto &expres: expressions[token.str]) {
                    LRItem tlr0item{token.str, expres, 0};

                    if (!lr0items.find(tlr0item)) {
                        itemsque.push(tlr0item);
                        lr0items.push_back(tlr0item);
                    }
                }
            } else {
                continue;
            }
        }
    }
    return lr0items.items;
}

/**
 *
 * @param group
 * @return
 */
void CBCompiler::LALR::GenerateNewLr0Group(CBCompiler::LR0group *group, std::queue<LR0group *> &que) {
    assert(!groups.empty());
    bool flag = true;
    for (auto &core: groups) {
        if (*group == *core) {
            group->id = core->id;
            flag = false;
            return;
        }
    }
    if (flag) {
        group->id = lr0_group_id++;
        que.push(group);
        groups.push_back(group);

    }
}

void CBCompiler::LALR::AddEdge(uint from, uint to, const std::string &token) {

    if (expressions.count(token)) trans_chart.push_back({from, to, {LRType::UNEND, token}});
    else {
        trans_chart.push_back({from, to, {LRType::END, token}});
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

void CBCompiler::LALR::DrawLR(std::string outf, bool closure) {
    assert(groups.size() >= 1);
    std::ofstream out(outf);
    out << "digraph LALR {" << std::endl;
    out << "node[shape=plaintext]" << std::endl;

    for (auto &lr_group: groups) {
        out << string_format("group_%d", lr_group->id);
        out << "[label=<<TABLE>" << std::endl;

        out << R"(<TR><TD BGCOLOR="darkslategray2"><FONT POINT-SIZE="30" COLOR="red">)";
        out << string_format("Group  %d", lr_group->id);
        out << "</FONT></TD></TR>)" << std::endl;


        for (auto &core_item: lr_group->core_items) {
            out << R"(<TR><TD BGCOLOR="green">)" << std::endl;
            out << core_item.to_string();
            out << "</TD></TR>" << std::endl;
        }
        if (closure) {
            out << R"(<TR><TD BGCOLOR="pink">)";
            out << "Closure Items";
            out << "</TD></TR>" << std::endl;

            for (auto &closure_item: GetLR0Closure(lr_group->core_items)) {
                out << R"(<TR><TD BGCOLOR="yellow">)" << std::endl;
                out << closure_item.to_string();
                out << "</TD></TR>" << std::endl;
            }
        }
        out << "</TABLE>>]\n" << std::endl;
    }

    for (auto &edge: trans_chart) {
        out << string_format("group_%d ->group_%d [label=%s];", std::get<0>(edge), std::get<1>(edge),
                             std::get<2>(edge).str.c_str())
            << std::endl;
    }
    out << "}" << std::endl;
    out.close();
}

/**
 *
 * @param tokens
 * @return
 */
std::set<std::string> CBCompiler::LALR::GetFirst(const std::vector<LRToken> &tokens) {
    assert(!tokens.empty());

    return GetFirst(tokens[0]);
}

/**
 *
 * @param token
 * @return
 */
std::set<std::string> CBCompiler::LALR::GetFirst(const CBCompiler::LRToken &token) {
    if (token.type == LRType::END) {
        return {token.str};
    }
    std::set<std::string> res;
    auto rexpres = expressions[token.str];
    for (auto &tokens: rexpres) {
        auto token = tokens[0];
        if (token.type == LRType::UNEND) {
            auto first = GetFirst(token);
            res.insert(first.begin(), first.end());
        } else {
            res.insert(token.str);
        }
    }
    return res;
}

void CBCompiler::LALR::GenerateLR1Groups() {
//    void
    assert(groups.size() > 1);
    //the first item is must be the root item
    LRItem &root = groups[0]->core_items[0];

    std::queue<::uint> que;
    root.temp.insert("$");

    que.push(0);

    while (!que.empty()) {
        auto top_id = que.front();
        que.pop();
        auto top = groups[top_id];
        for (auto &core_item: top->core_items) {
            if (core_item.temp.empty())continue;
            auto lr_closure = GetLR1Closure(core_item);
            for (auto &closure_item: lr_closure) {
                LRToken token;
                bool flag = closure_item.TokenAfterPos(token);
                if (!flag)continue;
                uint group_id = top->id;
                uint trans_to_id = StateTransfer(group_id, token.str);
                auto trans_group = groups[trans_to_id];
                dbg(group_id, trans_to_id);

                bool f = trans_group->AddNewLookForwardToken(closure_item);
                if (f) {
                    que.push(trans_to_id);
                }
            }
            core_item.look_forward.insert(core_item.temp.begin(), core_item.temp.end());
            core_item.temp.clear();
        }

    }
}

std::vector<CBCompiler::LRItem> CBCompiler::LALR::GetLR1Closure(const LRItem &core_item) {
    std::queue<LRItem> itemsque;
    SetVector lr1_items;
    LRItem new_core(core_item);
    new_core.look_forward = new_core.temp;
    new_core.temp.clear();
    itemsque.push(new_core);
    lr1_items.push_back(new_core);
    while (!itemsque.empty()) {
        auto top = itemsque.front();
        itemsque.pop();
        LRToken token;
        bool flag = top.TokenAfterPos(token);
        if (!flag) {
        } else {
            if (token.IsUnend()) {
                for (auto &i: expressions[token.str]) {
                    LRToken token2;
                    bool flag = top.TokenTwoAfterPos(token2);
                    std::vector<LRToken> belta_a;
                    std::set<std::string> look_forward;
                    if (flag) {
                        //if twoafterpos exists
                        auto first_set = GetFirst(token2);
                        look_forward.insert(first_set.begin(), first_set.end());
                    } else {
                        // i
                        look_forward = top.look_forward;
                    }
                    LRItem belta_item{token.str, i, 0};
                    belta_item.look_forward = look_forward;
                    if (!lr1_items.find(belta_item)) {
                        itemsque.push(belta_item);
                        lr1_items.push_back(belta_item);
                    }
                }
            } else {
                continue;
            }
        }
    }
    return lr1_items.items;
}

uint CBCompiler::LALR::StateTransfer(uint id, const std::string &token) {
    for (auto &row: trans_chart) {
        if (std::get<0>(row) == id && std::get<2>(row).str == token)
            return std::get<1>(row);
    }
    assert(true);
    return 0;
}

void CBCompiler::LALR::DrawLALR(std::string outf) {

    assert(groups.size() >= 1);
    std::ofstream out(outf);
    out << "digraph LALR {" << std::endl;
    out << "node[shape=plaintext]" << std::endl;

    for (auto &lr_group: groups) {
        out << string_format("group_%d", lr_group->id);
        out << "[label=<<TABLE>" << std::endl;

        out << R"(<TR><TD COLSPAN="2" BGCOLOR="darkslategray2"><FONT POINT-SIZE="30" COLOR="red">)";
        out << string_format("Group  %d", lr_group->id);
        out << "</FONT></TD></TR>)" << std::endl;

        for (auto &core_item: lr_group->core_items) {
            out << R"(<TR><TD BGCOLOR="green">)" << std::endl;
            out << core_item.to_string();
            out << R"(</TD><TD BGCOLOR="yellow">)" << std::endl;
            for (auto &look: core_item.look_forward) {
                out << look << " ";
            }
            out << "</TD></TR>";
        }
        out << "</TABLE>>]\n" << std::endl;
    }

    for (auto &edge: trans_chart) {
        out << string_format("group_%d ->group_%d [label=%s];", std::get<0>(edge), std::get<1>(edge),
                             std::get<2>(edge).str.c_str())
            << std::endl;
    }
    out << "}" << std::endl;
    out.close();
}



