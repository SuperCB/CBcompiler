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

    enum class State {
        DISCOVERD,
        UNDISCOVERD,
        VISITED
    };
    Node() : state(State::UNDISCOVERD), id(0), before(0), after(0), doms({}), pres({}), succs({}) {};

    Node(uint id_) : state(State::UNDISCOVERD), id(id_), before(0), after(0), doms({}), pres({}), succs({}) {};

    State state;

    unsigned int id;
    uint before, after;

    std::vector<uint> doms;
    std::vector<uint> pres;
    std::vector<uint> succs;

    void AddSucc(uint succ_);

    void AddPre(uint pre);

    void AddDom(uint dom);

};


