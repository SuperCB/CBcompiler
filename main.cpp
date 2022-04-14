#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <string_view>
#include <utility>
#include <memory>

using namespace std;

class Learn {
public:
    Learn() : c(nullptr) {
        cout << "fdas" << endl;
    }
    Learn(int *c_) : c(c_) {
        cout << "fdas" << endl;
    }

    Learn(Learn &&learn) : c(learn.c) {
        learn.c = nullptr;
        cout << "move" << endl;
    }
    int *c;
};

int main() {
    vector<Learn> learns = vector<Learn>(10);
    int c = 211;
    Learn c1(&c);
    learns[2] = move(c1);
    return 0;
}
