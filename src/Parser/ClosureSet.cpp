//
// Created by supercb on 22-4-27.
//

#include "ClosureSet.h"

namespace CBCompiler {
    void ClosureSet::push_back(const LR0Item &lr0item) {

        items.push_back(lr0item);
    }

    bool ClosureSet::find(const LR0Item &lr0item) {
        bool flag = true;
        for (auto &item: items) {
            if (item == lr0item) {
                return true;
            }
        }
        if (flag)
            return false;
    }

} // CBCompiler