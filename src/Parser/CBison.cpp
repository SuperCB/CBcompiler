//
// Created by supercb on 22-4-26.
//

#include "CBison.h"


CBCompiler::CBison::CBison(std::string_view addr) {
    std::ifstream jfile(addr.data());
    jfile >> bnfs;


    auto rootExpr=bnfs["root"];

}
