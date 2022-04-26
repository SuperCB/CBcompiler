//
// Created by supercb on 22-4-26.
//

#pragma once

#include <string>
#include <vector>
#include <set>

namespace CBCompiler {

    class BNFItem {
        std::string_view lexr;
        std::vector<std::string> rexprs;
    };
    class LR0Item : public BNFItem {
        int pointloc;
    };
}
