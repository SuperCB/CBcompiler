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

class Graph {
    using uint = unsigned int;
private:
    std::vector<Node> nodes;
    std::map<uint, Node> id2map;
public:

    void Add_Node(Node node);

    void AddEdge(uint from, uint to);

    void ToSSA();

    void GetDomTree();

    void DrawTree();

    void DrawDomTree();
};


