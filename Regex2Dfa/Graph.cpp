//
// Created by supercb on 22-4-23.
//

#include "Graph.h"

void CBCompiler::Graph::addedge(int a, int b, char ch) {
    edges[idx] = {ch};
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

CBCompiler::Graph::Graph() {
    h = new int[N];
    e = new int[M];
    ne = new int[M];
    edges = new LexEdge[M];
}

CBCompiler::Graph::~Graph() {
    delete []h;
    delete []e;
    delete []ne;
    delete[]edges;
}



