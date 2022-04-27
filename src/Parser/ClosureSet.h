//
// Created by supercb on 22-4-27.
//

#pragma
#include <vector>
#include <set>
#include "LRUtil.h"
#include "LR0Item.h"
namespace CBCompiler {
    class ClosureSet {
    public:
        std::vector<LR0Item>items;
        void push_back(const LR0Item&item);

        bool find(const LR0Item &item);
    };
} // CBCompiler


