//
// Created by supercb on 2022-04-02.
//

#ifndef CBCOMPILER_REGEX2DFA_H
#define CBCOMPILER_REGEX2DFA_H

#include <string_view>
#include <string>
#include <vector>

#include "DfaSubGraph.h"
#include "RegexConjunction.h"
class Regex2Dfa {
    Regex2Dfa(std::string_view regexstr);

    Regex2Dfa(const Regex2Dfa &regex2Dfa) = delete;

    static inline bool isSpecialOperator(char op);

    static inline bool isidentityChar(char ch);
private:
    int idx;
    int n;//the id of node
};


#endif //CBCOMPILER_REGEX2DFA_H
