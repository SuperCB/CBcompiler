//
// Created by supercb on 22-5-28.
//
#pragma once

#include <vector>
#include <map>
#include <set>
#include "Node.h"
#include "../include/dbg.h"
#include <fstream>
#include<cassert>


#define NUM first
#define NODE second


template<typename ... Args>
std::string string_format(const std::string &format, Args ... args) {
    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
    // unique_ptr<char[]> buf(new char[size]);
    char bytes[size];
    snprintf(bytes, size, format.c_str(), args ...);
    return bytes;
}

class Graph {
    using uint = unsigned int;
private:
    std::vector<Node> nodes;
    std::map<uint, Node> id2map;
    std::map<uint, uint> sdom;
    std::map<uint, uint> forest_fa;
    std::map<uint, uint> label;
    std::map<uint, uint> idom;
    std::map<uint, std::vector<uint>> bucket;


    uint time_stamp = 1;


    uint Find(uint u) {
        if (forest_fa[u] == u)return u;
        uint fa = Find(forest_fa[u]);
        if (sdom[label[forest_fa[u]]] < sdom[label[u]])
            label[u] = label[forest_fa[u]];

        forest_fa[u] = fa;
        return fa;
    }

    void Merge(uint fa, uint son) {
        forest_fa[son] = fa;
    }

public:

    void Add_Node(Node node);

    void AddEdge(uint from, uint to);

    void ToSSA();

    void GetDomTree();

    void DrawTree();

    void DrawDomTree();

    void DFS(std::vector<std::string> &edges);

    void DFS(uint root, std::vector<std::string> &edges);

    void DrawDfsTree();


    void Lengauer_Tarjan(bool draw= false,bool orignal= false);


    static inline std::string Tree_Edge(uint from, uint to, std::string name) {

        return string_format(
                R"(%s_%d ->%s_%d[label="Tree Edge" fontcolor=forestgreen fontsize="25" color=forestgreen penwidth="5"];)",
                name.c_str(), from, name.c_str(), to);
    }

    static inline std::string Forward_Edge(uint from, uint to, std::string name) {

        return string_format(
                R"(%s_%d ->%s_%d[label="Forward Edge" fontcolor=purple fontsize="25" color=purple style=dotted penwidth="4"];)",
                name.c_str(), from, name.c_str(), to);
    }

    static inline std::string Cross_Edge(uint from, uint to, std::string name) {
        return string_format(
                R"(%s_%d ->%s_%d[label="Cross Edge" fontcolor=blue fontsize="25" color=blue style=dotted penwidth="5"];)",
                name.c_str(), from, name.c_str(), to);
    }

    static inline std::string Backward_Edge(uint from, uint to, std::string name) {
        return string_format(
                R"(%s_%d ->%s_%d[label="Backward Edge" fontcolor=red fontsize="25" color=red style=dashed penwidth="5"];)",
                name.c_str(), from, name.c_str(), to);
    }

    static inline std::string Sdom_Edge(uint from, uint to, std::string name) {
        return string_format(
                R"(%s_%d ->%s_%d[label="Sdom" fontcolor=red fontsize="25" color=red  penwidth="5"];)",
                name.c_str(), from, name.c_str(), to);
    }

    static inline std::string Idom_Edge(uint from, uint to, std::string name) {
        return string_format(
                R"(%s_%d ->%s_%d[label="Idom" fontcolor=deeppink2 fontsize="25" style=dashed  color=deeppink2  penwidth="2"];)",
                name.c_str(), from, name.c_str(), to);
    }
};



