//
// Created by supercb on 2022-04-02.
//

#ifndef CBCOMPILER_REGEX_H
#define CBCOMPILER_REGEX_H

#include <string_view>
enum Type {
    CONJUNCTION,
    CHAR,
    SQUAREBRA,//[]
    PARENTHESIS,
    SPECIAL// /d/(
};

class Regex {

public:
    Regex(Type type_, char op_,Regex);
    Regex(Type type_, std::string_view str_);

private:
    Type type;
    std::string_view str;
    char op;
};


#endif //CBCOMPILER_REGEX_H
