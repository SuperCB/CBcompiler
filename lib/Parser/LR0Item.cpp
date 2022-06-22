//
// Created by supercb on 22-4-27.
//

#include "LRItem.h"

bool CBCompiler::LRItem::operator==(const CBCompiler::LRItem &r) const {

    bool f0 = (r.lv == lv);
    bool f1 = (r.ploc == ploc);
    bool f2 = (r.core == core);
    bool f3 = true;
    bool f4 = true;
    if (rexprs.size() != r.rexprs.size()) {
        return false;
    }
    for (int i = 0; i < r.rexprs.size(); i++) {
        if (r.rexprs[i] == rexprs[i])continue;
        else {
            f3 = false;
            break;
        }
    }
    if (!look_forward.empty()) {
        if (r.look_forward.empty() || r.look_forward.size() != look_forward.size()) { f4 = false; }
        else {
            for (auto iter1 = look_forward.begin(),
                         iter2 = r.look_forward.begin();
                 iter1 != look_forward.end(),
                 iter2 != r.look_forward.end();++iter1, ++iter2) {
                if (*iter1 != *iter2) {
                    f4 = false;
                    break;
                }

            }
        }
    }
    return f0 && f1 && f2 && f3 && f4;
}

bool CBCompiler::LRItem::operator!=(const CBCompiler::LRItem &r) const {
    return !(*this == r);
}


bool CBCompiler::LRItem::operator<(const LRItem &r) const {
    std::string lstr = lv;
    std::string rstr = r.lv;
    for (auto &token: rexprs)
        lstr.append(token.str);
    for (auto &token: r.rexprs)
        rstr.append(token.str);
    return lstr < rstr;
}



