//
// Created by supercb on 22-6-21.
//

#pragma once
//
#include <vector>
#include <string>
#include <string_view>
//
#define DEBUG 1
enum class TokenType {
    Add = 9,
    And = 20,
    Assign = 22,
    Break = 7,
    Comma = 23,
    Const = 2,
    Continue = 8,
    Div = 12,
    Else = 5,
    Eq = 18,
    Ge = 17,
    Gt = 16,
    ID = 32,
    If = 4,
    Int = 1,
    IntConst = 33,
    LBrc = 30,
    LBrk = 28,
    LPar = 26,
    Le = 15,
    Lt = 14,
    Mod = 13,
    Mul = 11,
    Ne = 19,
    Not = 25,
    Or = 21,
    RBrc = 31,
    RBrk = 29,
    RPar = 27,
    Return = 6,
    Semi = 24,
    Sub = 10,
    Void = 0,
    While = 3,
    Over = 35,
};
struct Token {
    TokenType type;
    std::string_view piece;
    uint line, col;
};
int chars = 0;
int words = 0;
int lines = 0;
//
std::vector<Token> tokens;


void lex_next(TokenType type, char *yytext) {

}