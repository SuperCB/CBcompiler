//
// Created by supercb on 22-4-23.
//

#pragma once


#include <string>

namespace CBCompiler {

    struct LexEdge {
        char ch;
    };
    struct YaccEdge {

    };

}

namespace CBCompiler {
    class Graph {
    public:
        Graph();
        void addedge(int a, int b, char ch); // 添加一条边a->b
        virtual ~Graph();

    private:
        const int N = 1000, M = 20000;
        int *h;
        int *e;
        int *ne;
        LexEdge  *edges;
        unsigned int idx{1};
    };
}

