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
#include "src/Parser/LALR.h"
#include "include/json.hpp"

using namespace std;


using json = nlohmann::json;

int main() {



    CBCompiler::LALR a("/home/supercb/mycode/CppProjects/CBcompiler/new.json");
    a.DrawLR("fuck.dot", true);
    a.DrawLALR("fuckyou.dot");
}
//    shared_ptr<CBCompiler::Graph>trans_chart(new CBCompiler::Graph);
//    CBCompiler::Regex2Dfa regex2Dfa("(ab+)", trans_chart);
//    trans_chart->DrawDot("cb.dot");
//    return 0;
// read a JSON file
//    string v="../model_server.py";
//    char *s[] = {const_cast<char *>(v.c_str()), "model-server-ipc", nullptr};
//    cout << execvp(v.c_str(), s);
//    cout<<strerror(errno);
//    char *envp[] = { NULL};
//    char *argv[]={"../model_server.py", NULL};
//    cout<<execlp("/root/anaconda3/bin/python","python","../model_server.py", (char*)0);
//    cout<<strerror(errno);