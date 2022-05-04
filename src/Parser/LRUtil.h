//
// Created by supercb on 22-4-26.
//

#pragma once


#include "LRItem.h"
#include <algorithm>
#include <utility>

namespace CBCompiler {

    class LR0group {
    public:
        std::vector<LRItem> core_items;
        int id{0};

        LR0group(std::vector<LRItem> core_items_) : core_items(std::move(core_items_)) { sort(); }

        void sort() {
            auto checkstates = [](LRItem &l, LRItem &r) -> bool {
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


        bool AddNewLookForwardToken(const LRItem &lrItem) {
            for (auto &item: core_items) {
                if (L_Transto_R(lrItem, item)) {
                    bool flag = false;
                    for (auto forward_token: lrItem.look_forward) {
                        if (item.look_forward.count(forward_token) == 0) {
                            item.temp.insert(forward_token);
                            flag = true;
                        }
                    }
                    return flag;
                }
            }
            assert(true);
            return true;
        }

        bool L_Transto_R(const LRItem &l, const LRItem &r) const {
            if (l.GetLva() == r.GetLva()) {
                if (l.rexprs.size() == r.rexprs.size()) {
                    bool flag = true;
                    for (uint i = 0; i < l.rexprs.size(); ++i) {
                        if (l.rexprs[i] != r.rexprs[i]) { flag = false; }
                    }
                    if (flag && l.ploc + 1 == r.ploc) {
                        return true;
                    } else return false;
                } else return false;
            }
            return false;
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
