//
// Created by supercb on 22-4-27.
//

#pragma
#include <vector>
#include <set>
#include "LRUtil.h"
#include "LRItem.h"
namespace CBCompiler {
//    template <typename Type>
    class SetVector {
    public:
        std::vector<LRItem>items;
        void push_back(const LRItem&item);

        bool find(const LRItem &item);

        void append(const std::vector<LRItem> &datas);
    };
} // CBCompiler


