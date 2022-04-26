//
// Created by supercb on 22-4-26.
//

#pragma once
#include <fstream>
#include <iostream>
#include <set>
#include "../../include/json.hpp"
using json = nlohmann::json;

namespace CBCompiler {
    class CBison {

    public:
        CBison() = delete;
        explicit CBison(std::string_view addr);
    private:
        json bnfs;

    };
}
