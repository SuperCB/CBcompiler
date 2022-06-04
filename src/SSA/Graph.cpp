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

void Graph::DFS(std::vector<std::string> &edges) {
    assert(!id2map.empty());
    uint root_id = 1;

    for (auto [k, v]: id2map) {
        if (v.pres.empty()) {
            root_id = k;
            break;
        }
    }
    DFS(root_id, edges);
}

void Graph::DFS(uint root, std::vector<std::string> &edges) {

    auto &root_node = id2map[root];

    sdom[root] = root;
    forest_fa[root] = root;
    label[root] = root;
    root_node.before = time_stamp++;
    root_node.state = Node::State::DISCOVERD;

    //  std::cout << id2map[root].before << std::endl;

    for (auto succ: root_node.succs) {

        switch (id2map[succ].state) {
            case Node::State::DISCOVERD:
                edges.emplace_back(Backward_Edge(root, succ, "nodedfs"));
                break;
            case Node::State::UNDISCOVERD:
                id2map[succ].treefas = root;
                edges.emplace_back(Tree_Edge(root, succ, "nodedfs"));
                DFS(succ, edges);
                break;
            case Node::State::VISITED:
                if (id2map[succ].before > id2map[root].before)
                    edges.emplace_back(Forward_Edge(root, succ, "nodedfs"));
                else {
                    edges.emplace_back(Cross_Edge(root, succ, "nodedfs"));
                }
                break;
            default:
                break;
        }

    }
    root_node.after = time_stamp++;
    root_node.state = Node::State::VISITED;
}

void Graph::DrawDfsTree() {
    std::vector<std::string> edges;
    DFS(edges);
    std::ofstream tree("dfstree.dot");
    tree << "digraph tree {" << std::endl;
    tree << "rankdir=TD;" << std::endl;
    {
        tree << "subgraph cluster_1 {" << std::endl;
        tree << "fontsize=40;" << std::endl;
        tree << "style=filled;" << std::endl;
        tree << "color=lightcyan;" << std::endl;

        tree << R"(label="Original Graph")" << std::endl;
        for (auto &[k, v]: id2map) {
            tree << string_format("nodeor_%u [label=%u shape=doublecircle fillcolor = pink style = filled];", k, k)
                 << std::endl;
        }
        for (auto [k, node]: id2map) {
            for (auto succ_id: node.succs) {
                tree << string_format("nodeor_%d ->nodeor_%d ;", k, succ_id) << std::endl;
            }
        }
        tree << "};" << std::endl;
    }
    {
        tree << "subgraph cluster_2 {" << std::endl;
        tree << "fontsize=40;" << std::endl;
        tree << R"(label="DFS Graph")" << std::endl;
        tree << "color = blue;" << std::endl;

        for (auto &[k, v]: id2map) {
            tree << string_format(
                    R"(nodedfs_%u [label=<<FONT POINT-SIZE="25">%u</FONT>|<FONT POINT-SIZE="35">id:%u</FONT>|<FONT POINT-SIZE="25">%u</FONT>> shape=Mrecord fillcolor = pink style = filled];)",
                    k, v.before, k, v.after) << std::endl;
        }

        for (auto &edge: edges) {
            tree << edge << std::endl;
        }
        tree << "};" << std::endl;
    }
    tree << "}" << std::endl;
    tree.close();
}

void Graph::Lengauer_Tarjan(bool draw, bool orignal) {
    std::vector<std::string> edges;
    DFS(edges);
    std::vector<std::pair<uint, Node>> vec(id2map.begin(), id2map.end());
    sort(vec.begin(), vec.end(), [&](std::pair<uint, Node> a, std::pair<uint, Node> b) {
        return a.NODE.before < b.NODE.before;
    }); //排序

    for (int i = vec.size() - 1; i >= 0; i--) {
        auto node_pair = vec[i];

        for (auto &pre: node_pair.NODE.pres) {
            Find(pre);
            sdom[node_pair.NUM] = std::min(sdom[node_pair.NUM], sdom[label[pre]]);
        }
        if (i > 0)bucket[sdom[node_pair.NUM]].push_back(node_pair.NUM);

        for (int j = 0; j < bucket[node_pair.NUM].size(); j++) {
            uint w = bucket[node_pair.NUM][j];
            Find(w);
            uint u = label[w];
            if (sdom[u] == sdom[w])idom[w] = sdom[u];
            else {
                idom[w] = u;
            }
        }
        if (i > 0)Merge(id2map[node_pair.NUM].treefas, node_pair.NUM);
    }

    for (int i = 1; i < vec.size(); i++) {
        auto loc = vec[i].NUM;
        if (idom[loc] != sdom[loc])
            idom[loc] = idom[idom[loc]];
    }

    if (draw) {
        std::ofstream tree("domtree.dot");
        tree << "digraph tree {" << std::endl;
        {

            tree << R"(fontsize="40")" << std::endl;
            tree << R"(label="Dominator Tree")" << std::endl;
            for (auto &[k, v]: id2map) {
                tree << string_format("nodeor_%u [label=%u shape=doublecircle fillcolor = pink style = filled];", k, k)
                     << std::endl;
            }
            if (orignal) {
                for (auto [k, node]: id2map) {
                    for (auto succ_id: node.succs) {
                        tree << string_format("nodeor_%d ->nodeor_%d ;", k, succ_id) << std::endl;
                    }
                }
            }
            for (auto &[k, v]: idom) {
                tree << Idom_Edge(v, k, "nodeor") << std::endl;
            }

        }

        tree << "}" << std::endl;
        tree.close();
    }
}


