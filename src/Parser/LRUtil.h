//
// Created by supercb on 22-4-26.
//

#pragma once


#include "LR0Item.h"
#include <algorithm>

namespace CBCompiler {

    class LR0group {
    public:
        std::vector<LR0Item> core_items;
        std::vector<LR0Item> closure_items;
        int id{0};

        LR0group(std::vector<LR0Item> core_items_) : core_items(core_items_) { sort(); }

        void sort() {
            auto checkstates = [](LR0Item &l, LR0Item &r) -> bool {
                std::string lstr = l.GetLva();
                std::string rstr = r.GetLva();
                for (auto &token: l.GetRexprs())
                    lstr.append(token.str);
                for (auto &token: r.GetRexprs())
                    rstr.append(token.str);

                if (lstr != rstr)
                    return lstr < rstr;
                else {
                    return l.GetPointLoc() < r.GetPointLoc();
                }
            };
            std::sort(core_items.begin(), core_items.end(), checkstates);

        }

        bool operator==(const LR0group &r) const {
            if (core_items.size() != r.core_items.size()) {
                return false;
            }
            bool flag = true;
            for (int i = 0; i < core_items.size(); ++i) {
                if (core_items[i] != r.core_items[i]) {
                    flag = false;
                    break;
                }
            }
            return flag;
        }
    };


}
