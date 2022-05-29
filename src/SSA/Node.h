//
// Created by supercb on 22-5-28.
//
#include<vector>
#include <iostream>
#include <algorithm>

#pragma once

class Node {
private:
    using uint = unsigned int;

public:
    Node() : id(0) {};

    Node(uint id_) : id(id_) {};
    unsigned int id;

    std::vector<uint> doms;
    std::vector<uint> pres;
    std::vector<uint> succs;

    void AddSucc(uint succ_);
    void AddPre(uint pre);
    void AddDom(uint dom);

};


