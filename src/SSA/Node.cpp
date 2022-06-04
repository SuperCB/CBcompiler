//
// Created by supercb on 22-5-28.
//

#include "Node.h"


void Node::AddSucc(uint succ_) {
    succs.push_back(succ_);
}

void Node::AddPre(uint pre) {
    pres.push_back(pre);
}

void Node::AddDom(uint dom) {
    doms.push_back(dom);
}


