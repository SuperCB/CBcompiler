//
// Created by supercb on 2022-04-02.
//

#include "Regex2Dfa.h"

Regex2Dfa::Regex2Dfa(std::string_view regexstr) {

    std::vector<Regex *> subitem;
    for (unsigned int i = 0; i < regexstr.size();) {
        char ch = regexstr[i];
        if (ch == '(') {
            std::string str{};
            i++;
            while (i < regexstr.size() && regexstr[i] != ')') {
                str += ch;
            }
            Regex *par = new Regex(Type::PARENTHESIS, ch);
            subitem.push_back(par);
            i++;

        } else if (ch == '[') {
            std::string str{};
            i++;
            while (i < regexstr.size() && regexstr[i] != ']') {
                str += ch;
            }
            Regex *squ = new Regex(Type::SQUAREBRA, ch);
            subitem.push_back(squ);
            i++;
        } else if (isidentityChar(ch)) {
            Regex *characater = new Regex(Type::CHAR, ch);
            subitem.push_back(characater);
            i++;
        } else if (isSpecialOperator(ch)) {
            Regex *conjunction = new Regex(Type::CONJUNCTION, ch);
            subitem.push_back(conjunction);
            i++;
        } else if (ch == '\\') {
            // speac
            Regex *spe = new Regex(Type::SPECIAL, regexstr[i + 1]);
            subitem.push_back(spe);
            i++;
        }
    }
    for (auto &item: subitem) {


    }
}


inline bool Regex2Dfa::isSpecialOperator(char op) {

    if (op == '*' || op == '|' || op == '+')
        return true;
    else
        return false;
}

bool Regex2Dfa::isidentityChar(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
        return true;
    else
        return false;
}


