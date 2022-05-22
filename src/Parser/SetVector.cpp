//
// Created by supercb on 22-4-27.
//

#include "SetVector.h"

namespace CBCompiler {
    void SetVector::push_back(const LRItem &lr0item) {

        items.push_back(lr0item);
    }
    bool SetVector::find(const LRItem &lr0item) {
        bool flag = true;
        for (auto &item: items) {
            if (item == lr0item) {
                return true;
            }
        }
        if (flag)
            return false;
    }
    void SetVector::append(const std::vector<LRItem>&datas) {
       for(auto &item:datas)
       {
           if(find(item))
               continue;
           else
               items.emplace_back(item);
       }
    }
} // CBCompiler