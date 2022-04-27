//
// Created by supercb on 22-4-26.
//

#include "CBison.h"


CBCompiler::CBison::CBison(std::string_view addr) {
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

//                assert(typeid(exi.value()) == typeid(std::string));
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
    generateLR0groups();
}

void CBCompiler::CBison::generateLR0groups() {

    CBCompiler::LR0Item root("root", {{LRType::UNEND, rootstr}}, 0);

    LR0group sta({root});
    std::queue<CBCompiler::LR0group> que;

    sta.id = ++lr0_group_id;

    que.push(sta);//jia ru zengguangwenfa
    cores.emplace_back(sta);

    while (!que.empty()) {
        auto top_lro_group = que.front();
        que.pop();
        auto closure_items = GetClosure(top_lro_group.core_items);
        std::unordered_map<std::string, std::vector<unsigned int>> token2lr0item;
        for (unsigned int i = 0; i < closure_items.size(); ++i) {
            LR0Item lr0item = closure_items[i];
            LRToken lr0token;
            bool flag = lr0item.tokenafterpos(lr0token);
            if (!flag) {
//                dbg("Accept");
            } else {
                token2lr0item[lr0token.str].push_back(i);
            }
        }
        for (auto &[k, ids]: token2lr0item) {
            std::vector<LR0Item> n_group_cores;
            for (auto &i: ids) {
                closure_items[i].PointLocAdd();
                n_group_cores.push_back(closure_items[i]);
            }
            LR0group ne_lr0_group(n_group_cores);
            GenerateNewLr0Group(ne_lr0_group, que);
//            dbg(top_lro_group.id, "->", k, ne_lr0_group.id);
        }
    }
    std::cout<<cores.size()<<std::endl;
}

std::vector<CBCompiler::LR0Item> CBCompiler::CBison::GetClosure(const std::vector<LR0Item> &coreitems) {
    ClosureSet lr0items;
    std::queue<LR0Item> itemsque;

    for (auto &core_item: coreitems) {
        itemsque.push(core_item);
        lr0items.push_back(core_item);
    }
    while (!itemsque.empty()) {
        auto top = itemsque.front();
        itemsque.pop();
        LRToken token;
        bool flag = top.tokenafterpos(token);
        if (!flag) {
//            dbg("Accept ");
        } else {
            if (token.IsUnend()) {
//                dbg("unend token", token.str);
                for (auto &i: expressions[token.str]) {
                    LR0Item tlr0item{token.str, i, 0};

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
void CBCompiler::CBison::GenerateNewLr0Group(CBCompiler::LR0group &group, std::queue<LR0group> &que) {
    assert(!cores.empty());
    bool flag = true;
    for (auto &core: cores) {
        if (group == core) {
            group.id = core.id;
            flag = false;
            return;
        }
    }
    if (flag) {
        printf("fdas\n");
        group.id = ++lr0_group_id;
        que.push(group);
        cores.push_back(group);
        for(auto c:group.core_items)
        {
            std::cout<<c.GetLva()<< std::endl;
            for(auto c1:c.GetRexprs())
                std::cout<<c1.str<<std::endl;
            std::cout << c.GetPointLoc();
            std::cout << "\n";
        }
        std::cout << "\n\n\n";


    }
}
