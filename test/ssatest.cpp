//
// Created by supercb on 22-5-29.
//
#include "../src/SSA/Graph.h"
#include "gtest/gtest.h"
#include <set>
#include <vector>
#include "../include/dbg.h"

TEST(SSATest, SetTest) {
    std::vector<int> a = {1, 2, 2, 3, 3, 3, 3, 3, 4};
    std::vector<int> b = {2, 3, 5};
    std::vector<int> c;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.begin()));

    dbg(c);
}


TEST(SSATest, GenerateGraph1) {

    Graph graph;
    for (unsigned int i = 1; i <= 10; ++i) {
        graph.Add_Node(Node(i));
    }

    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 4);
    graph.AddEdge(4, 3);
    graph.AddEdge(4, 5);
    graph.AddEdge(4, 6);
    graph.AddEdge(5, 7);
    graph.AddEdge(6, 7);
    graph.AddEdge(7, 4);

    graph.AddEdge(7, 8);
    graph.AddEdge(8, 9);
    graph.AddEdge(8, 10);
    graph.AddEdge(8, 3);
    graph.DrawDfsTree();
    //    graph.DrawTree();
//    graph.GetDomTree();
//    graph.DrawDomTree();
}

TEST(SSATest, GenerateGraph2) {

    Graph graph;
    for (unsigned int i = 1; i <= 7; ++i) {
        graph.Add_Node(Node(i));
    }

    graph.AddEdge(1, 2);
    graph.AddEdge(1, 5);
    graph.AddEdge(2, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(4, 6);
    graph.AddEdge(6, 7);
    graph.AddEdge(5, 7);
    graph.DrawDfsTree();
}

TEST(SSATest, TarjanTest) {

    Graph graph;
    for (unsigned int i = 1; i <= 13; ++i) {
        graph.Add_Node(Node(i));
    }

    graph.AddEdge(1, 2);
    graph.AddEdge(2, 3);
    graph.AddEdge(2, 6);
    graph.AddEdge(3, 4);
    graph.AddEdge(6, 4);
    graph.AddEdge(7, 4);
    graph.AddEdge(6, 7);
    graph.AddEdge(4, 5);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 1);
    graph.AddEdge(1, 8);
    graph.AddEdge(8, 9);
    graph.AddEdge(8, 11);
    graph.AddEdge(8, 12);
    graph.AddEdge(9, 10);
    graph.AddEdge(10, 9);
    graph.AddEdge(11, 12);
    graph.AddEdge(12, 13);
    graph.AddEdge(13, 10);
    graph.AddEdge(10, 5);
    graph.AddEdge(1, 11);

    graph.DrawDfsTree();
    graph.Lengauer_Tarjan(true, true);
}