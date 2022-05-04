//
// Created by supercb on 22-4-23.
//

#include "Graph.h"

namespace CBCompiler {
    template<typename ... Args>
    std::string string_format(const std::string &format, Args ... args) {
        size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
        // unique_ptr<char[]> buf(new char[size]);
        char bytes[size];
        snprintf(bytes, size, format.c_str(), args ...);
        return bytes;
    }
}

void CBCompiler::Graph::AddEdge(int a, int b, char ch) {
    std::tuple<::uint, ::uint, char> tu{a, b, ch};
    charts.emplace_back(tu);
//    dbg(tu);

}

CBCompiler::Graph::Graph() : node_id(0) {
}

CBCompiler::Graph::~Graph() {
}

void CBCompiler::Graph::GenerateRelation(int from, int to, const CBCompiler::Token &token) {
    for (auto &ch: token.parseToken()) {
        AddEdge(from, to, ch);
    }
}

void CBCompiler::Graph::DrawDot(const std::string &outf) {

    assert(node_id >= 1);
    std::ofstream out(outf);
    out << "digraph G {" << std::endl;

    if (acc_states.count(1)) {
        out << "node_1 [label=StartOrAccept shape=doublecircle color=green];" << std::endl;
    } else { out << "node_1 [label=Start shape=doublecircle color=blue];" << std::endl; }
    for (uint i = 2; i <= node_id; ++i) {
        if (acc_states.count(i)) {
            out << string_format("node_%d [label=Accept shape=%s color=red];", i, "doublecircle") << std::endl;
        } else {
            out << string_format("node_%d [label=%d shape=%s];", i, i, "circle") << std::endl;
        }
    }
    for (auto &tu: charts) {
        out << string_format("node_%d ->node_%d [label=%c];", std::get<0>(tu), std::get<1>(tu), std::get<2>(tu))
            << std::endl;
    }

    out << "}" << std::endl;
    out.close();
}


