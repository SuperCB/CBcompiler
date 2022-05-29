//
// Created by supercb on 22-5-28.
//

#include "Graph.h"


void Graph::Add_Node(Node node) {
    if (id2map.count(node.id) == 0)
        id2map[node.id] = node;
}

void Graph::AddEdge(uint from, uint to) {

    if (id2map.count(from) == 0 || id2map.count(to) == 0) {
        dbg("wrong");
        return;
    }
    id2map[from].AddSucc(to);
    id2map[to].AddPre(from);
}

template<typename ... Args>
std::string string_format(const std::string &format, Args ... args) {
    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
    // unique_ptr<char[]> buf(new char[size]);
    char bytes[size];
    snprintf(bytes, size, format.c_str(), args ...);
    return bytes;
}

//最简单的一种求支配树的方法
void Graph::GetDomTree() {

    //这个算法最好是使用bitset来做，如果不使用bitset的话，会失去code的优雅，但是bitset需要预先知道图中有多少点，这个想法又是不现实的
    assert(id2map.size() >= 1);
    id2map[1].doms.push_back(1);

    for (uint i = 2; i <= id2map.size(); ++i) {
        for (uint j = 1; j <= id2map.size(); ++j)
            id2map[i].AddDom(j);
    }
    //检查两个vector是否相同
    auto checksame = [](std::vector<uint> l, std::vector<uint> r) -> bool {

        std::sort(l.begin(), l.end());
        std::sort(r.begin(), r.end());
        if (l.size() != r.size())return false;
        for (auto i = 0; i < l.size(); ++i) {
            if (l[i] != r[i])return false;
        }

        return true;
    };

    //将v并到集合中去
    auto union_v = [](uint v, std::vector<uint> &doms) {

        std::sort(doms.begin(), doms.end());
        auto loc = std::find(doms.begin(), doms.end(), v);
        if (loc == doms.end())
            doms.push_back(v);

    };
    bool changed = true;
    while (changed) {
        changed = false;
        for (uint i = 2; i <= id2map.size(); ++i) {
            std::vector<uint> new_doms = id2map[id2map[i].pres[0]].doms;
//这种求并集的方法丧失了优雅与美
            for (uint j = 1; j < id2map[i].pres.size(); ++j) {
                auto preid = id2map[i].pres[j];
                auto doms = id2map[preid].doms;
                std::vector<uint> temp;
                std::set_intersection(new_doms.begin(), new_doms.end(), doms.begin(), doms.end(),
                                      std::inserter(temp, temp.begin()));
                new_doms = temp;
            }
            union_v(i, new_doms);
            bool f = checksame(id2map[i].doms, new_doms);
            if (!f) {
                id2map[i].doms = new_doms;
                changed = true;
            }
        }
    }
}

void Graph::DrawTree() {
    std::ofstream tree("tree.dot");
    tree << "digraph LALR {" << std::endl;
    for (auto &[k, v]: id2map) {
        tree << string_format("node_%u [label=%u shape=doublecircle fillcolor = pink style = filled];", k, k)
             << std::endl;
    }
    for (auto [k, node]: id2map) {

        for (auto succ_id: node.succs) {
            tree << string_format("node_%d ->node_%d ;", k, succ_id) << std::endl;
        }
    }
    tree << "}" << std::endl;
    tree.close();
}

void Graph::DrawDomTree() {
    std::ofstream tree("domtree.dot");
    tree << "digraph LALR {" << std::endl;
    for (auto &[k, v]: id2map) {
        tree << string_format("node_%u [label=%u shape=doublecircle fillcolor = pink style = filled];", k, k)
             << std::endl;
    }
    for (auto [k, node]: id2map) {

        for (auto dom: node.doms) {
            if (dom != k)
                //k必须是直接前缀
                tree << string_format("node_%d ->node_%d ;", dom, k) << std::endl;
        }
    }
    tree << "}" << std::endl;
    tree.close();

}

