#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <string_view>
#include <utility>
#include <memory>
#include <string>
#include "src/Regex2Dfa/Regex2Dfa.h"
#include "include/json.hpp"

using namespace std;


using json = nlohmann::json;

int main() {
//    shared_ptr<CBCompiler::Graph>graph(new CBCompiler::Graph);
//    CBCompiler::Regex2Dfa regex2Dfa("(ab+)", graph);
//    graph->DrawDot("cb.dot");
//    return 0;
// read a JSON file
    std::ifstream i("/home/supercb/mycode/CppProjects/CBcompiler/cb.json");
    json j;
    i >> j;
    auto c = j.find("afds");
    if (c == j.end())
        cout << "das";

}
