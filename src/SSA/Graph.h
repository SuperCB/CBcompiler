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
    uint time_stamp = 1;
public:

    void Add_Node(Node node);

    void AddEdge(uint from, uint to);

    void ToSSA();

    void GetDomTree();

    void DrawTree();

    void DrawDomTree();

    void DFS(std::vector<std::string>&edges);

    void DFS(uint root,std::vector<std::string>&edges);

    void Draw();

    inline std::string Tree_Edge(uint from, uint to) {

        return string_format(R"(nodedfs_%d ->nodedfs_%d[label="Tree Edge" fontcolor=green fontsize="25" color=forestgreen ];)", from, to);
    }

    inline std::string Forward_Edge(uint from, uint to) {

        return string_format(R"(nodedfs_%d ->nodedfs_%d[label="Forward Edge" fontcolor=purple fontsize="25" color=purple style=dotted];)", from, to);
    }

    inline std::string Cross_Edge(uint from, uint to) {
        return string_format(R"(nodedfs_%d ->nodedfs_%d[label="Cross Edge" fontcolor=blue fontsize="25" color=blue style=dotted];)", from, to);
    }

    inline std::string Backward_Edge(uint from, uint to) {
        return string_format(R"(nodedfs_%d ->nodedfs_%d[label="Backward Edge" fontcolor=red fontsize="25" color=red style=dashed];)", from, to);
    }

};



