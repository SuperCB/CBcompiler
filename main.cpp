#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <string_view>
#include <utility>

using namespace std;


const int N = 10000, M = 13000;
int h[N], e[M], ne[M], idx;


struct Node {
    unsigned int id;

};

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

enum regex_type {
    OP,
    SET,
    SUBREGEX,
    CHAR
};
struct RegexToken {
    regex_type type;
    char op;
    string str;
};

inline bool specialOperator(char op) {
    if (op == '*' || op == '|' || op == '+')
        return true;
    else
        return false;
}

vector<RegexToken> dropparentthese(string_view str) {

    vector<RegexToken> result;
    for (int i = 0; i < str.size();) {
        char ch = str[i];
        if (ch == '(') {
            // we only consider the situation with a layer of parenthese
            string substr{};
            while (i < str.size() && str[i] != ')') {
                substr += str[i];
                i++;
            }
            result.push_back({SUBREGEX, {}, substr});
            i++;
        } else if (ch == '[') {
            string substr{};
            while (i < str.size() && str[i] != ']') {
                substr += str[i];
                i++;
            }
            result.push_back({SET, {}, substr});
            i++;
        } else if (specialOperator(ch)) {
            result.push_back({OP, ch, {}});
        } else {
            result.push_back({CHAR, ch, {}});
        }
    }
    return std::move(result);
}

void dealsubregex(RegexToken regexToken) {
    for (int i = 0; i < regexToken.str.size(); i++)
    {
    }
}

void regex2dfa(vector<RegexToken> input) {
    for (auto &regextoken: input) {
        switch (regextoken.type) {
            case SUBREGEX:


                break;
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;


    return 0;
}
