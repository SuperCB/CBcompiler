//
// Created by supercb on 22-4-27.
//

#include "LR0Item.h"

bool CBCompiler::LR0Item::operator==(const CBCompiler::LR0Item &r) const{
    bool f0 = (r.lv == lv);
    bool f1 = (r.ploc == ploc);
    bool f2 = (r.core == core);
    bool f3 = true;
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
    return f0 && f1 && f2 && f3;
}
bool CBCompiler::LR0Item::operator!=(const CBCompiler::LR0Item &r) const{
    return !(*this == r);
}

//bool CBCompiler::LR0Item::operator<(const CBCompiler::LR0Item &l, const CBCompiler::LR0Item &r) const {
//    std::string lstr = l.GetLva();
//    std::string rstr = r.GetLva();
//    for(auto &token:l.GetRexprs())
//        lstr.append(token.str);
//    for(auto &token:r.GetRexprs())
//        rstr.append(token.str);
//    return lstr < rstr;
//}

bool CBCompiler::LR0Item::operator<(const LR0Item &r) const{
    std::string lstr = lv;
    std::string rstr = r.lv;
    for(auto &token:rexprs)
        lstr.append(token.str);
    for(auto &token:r.rexprs)
        rstr.append(token.str);
    return lstr < rstr;
}


