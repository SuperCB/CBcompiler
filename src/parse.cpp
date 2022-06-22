
#include "../src/Regex2Dfa/CFlex.h"
#include <vector>
#include <utility>using uint=unsigned int;

struct Act {
    enum : uint {
        Shift, Reduce, Accept, Err
    } kind;
    uint val;
};
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
std::vector<std::pair<CBCompiler::CFlex, int> > tokens{{CBCompiler::CFlex(""),                     16},
                                                       {CBCompiler::CFlex("!"),                    25},
                                                       {CBCompiler::CFlex("!="),                   19},
                                                       {CBCompiler::CFlex("%"),                    13},
                                                       {CBCompiler::CFlex("&&"),                   20},
                                                       {CBCompiler::CFlex(","),                    23},
                                                       {CBCompiler::CFlex("-"),                    10},
                                                       {CBCompiler::CFlex("/"),                    12},
                                                       {CBCompiler::CFlex(";"),                    24},
                                                       {CBCompiler::CFlex("<"),                    14},
                                                       {CBCompiler::CFlex("<="),                   15},
                                                       {CBCompiler::CFlex("="),                    22},
                                                       {CBCompiler::CFlex("=="),                   18},
                                                       {CBCompiler::CFlex(">="),                   17},
                                                       {CBCompiler::CFlex("[_A-Za-z]\w*"),         32},
                                                       {CBCompiler::CFlex("\\("),                  26},
                                                       {CBCompiler::CFlex("\\)"),                  27},
                                                       {CBCompiler::CFlex("\\*"),                  11},
                                                       {CBCompiler::CFlex("\\+"),                  9},
                                                       {CBCompiler::CFlex("\\["),                  28},
                                                       {CBCompiler::CFlex("\\]"),                  29},
                                                       {CBCompiler::CFlex("\d+|(0x[0-9a-fA-F]+)"), 33},
                                                       {CBCompiler::CFlex("break"),                7},
                                                       {CBCompiler::CFlex("const"),                2},
                                                       {CBCompiler::CFlex("continue"),             8},
                                                       {CBCompiler::CFlex("else"),                 5},
                                                       {CBCompiler::CFlex("if"),                   4},
                                                       {CBCompiler::CFlex("int"),                  1},
                                                       {CBCompiler::CFlex("return"),               6},
                                                       {CBCompiler::CFlex("void"),                 0},
                                                       {CBCompiler::CFlex("while"),                3},
                                                       {CBCompiler::CFlex("{"),                    30},
                                                       {CBCompiler::CFlex("||"),                   21},
                                                       {CBCompiler::CFlex("}"),                    31},
};

const static Act ACTION[131][35] = {{{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Shift,  2},  {Act::Shift,  3},  {Act::Shift,  5},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Accept, 0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  7},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  10}, {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 2},  {Act::Reduce, 2},  {Act::Reduce, 2},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 2}},
                                    {{Act::Err,    0},  {Act::Shift,  12}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 1},  {Act::Reduce, 1},  {Act::Reduce, 1},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 1}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  13},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 7},   {Act::Reduce, 7},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  14},  {Act::Reduce, 5},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  15},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  17},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  18}, {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Shift,  20}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  18}, {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Shift,  20}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  26},  {Act::Reduce, 9},   {Act::Reduce, 9},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  27}, {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Err, 0}, {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 4},   {Act::Reduce, 4},  {Act::Reduce, 4},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4},  {Act::Reduce, 4}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  28},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  29}, {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 38},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 38},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  30},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 36},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  31},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 6},   {Act::Reduce, 6},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  32},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift, 40}, {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Err, 0}, {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 3},   {Act::Reduce, 3},  {Act::Reduce, 3},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3},  {Act::Reduce, 3}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 40},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 40},  {Act::Shift,  43}, {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Shift,  20}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift, 46}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift, 46}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Reduce, 34}, {Act::Err,    0},   {Act::Reduce, 34},  {Act::Reduce, 34},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 34},  {Act::Err,    0},  {Act::Reduce, 34},  {Act::Err,   0},  {Act::Reduce, 34}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  50},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Reduce, 12},  {Act::Reduce, 12},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 12}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift, 40}, {Act::Shift,  69}, {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 8},   {Act::Reduce, 8},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  71},  {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  72},  {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 39},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 39},  {Act::Shift,  73}, {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 37},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 37},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 35}, {Act::Reduce, 35}, {Act::Reduce, 35}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 35}},
                                    {{Act::Reduce, 58}, {Act::Reduce, 58}, {Act::Reduce, 58}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 58}},
                                    {{Act::Reduce, 57}, {Act::Reduce, 57}, {Act::Reduce, 57}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 57}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  75},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Err,    0},   {Act::Reduce, 33},  {Act::Reduce, 33},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 33},  {Act::Shift,  27}, {Act::Reduce, 33},  {Act::Err,   0},  {Act::Reduce, 33}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Reduce, 30}, {Act::Err,    0},   {Act::Reduce, 30},  {Act::Reduce, 30},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 30},  {Act::Err,    0},  {Act::Reduce, 30},  {Act::Err,   0},  {Act::Reduce, 30}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 29}, {Act::Reduce, 29}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Reduce, 29}, {Act::Reduce, 29}, {Act::Reduce, 29}, {Act::Reduce, 29}, {Act::Reduce, 29}, {Act::Reduce, 29}, {Act::Reduce, 29}, {Act::Reduce, 29}, {Act::Err,    0},   {Act::Reduce, 29},  {Act::Reduce, 29},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 29},  {Act::Err,    0},  {Act::Reduce, 29},  {Act::Err,   0},  {Act::Reduce, 29}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 28}, {Act::Reduce, 28}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Reduce, 28}, {Act::Reduce, 28}, {Act::Reduce, 28}, {Act::Reduce, 28}, {Act::Reduce, 28}, {Act::Reduce, 28}, {Act::Reduce, 28}, {Act::Reduce, 28}, {Act::Err,    0},   {Act::Reduce, 28},  {Act::Reduce, 28},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 28},  {Act::Err,    0},  {Act::Reduce, 28},  {Act::Err,   0},  {Act::Reduce, 28}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 14},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 14}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 11},  {Act::Reduce, 11},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 11}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  93},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Shift,  92}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61}, {Act::Reduce, 61},  {Act::Reduce, 61},  {Act::Reduce, 61},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 61},  {Act::Reduce, 61}, {Act::Reduce, 61},  {Act::Err,   0},  {Act::Reduce, 61}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 60},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 60},  {Act::Reduce, 60}, {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Err, 0}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 52},  {Act::Reduce, 52}, {Act::Reduce, 52},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Reduce, 31}, {Act::Err,    0},   {Act::Reduce, 31},  {Act::Reduce, 31},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Reduce, 31},  {Act::Err,   0},  {Act::Reduce, 31}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Reduce, 56},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 56},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  107}, {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 54},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  108}, {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 16}, {Act::Reduce, 16}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Reduce, 16}, {Act::Reduce, 16}, {Act::Reduce, 16}, {Act::Reduce, 16}, {Act::Reduce, 16}, {Act::Reduce, 16}, {Act::Reduce, 16}, {Act::Reduce, 16}, {Act::Err,    0},   {Act::Reduce, 16},  {Act::Reduce, 16},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 16},  {Act::Err,    0},  {Act::Reduce, 16},  {Act::Err,   0},  {Act::Reduce, 16}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Reduce, 27}, {Act::Err,    0},   {Act::Reduce, 27},  {Act::Reduce, 27},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 27},  {Act::Err,    0},  {Act::Reduce, 27},  {Act::Err,   0},  {Act::Reduce, 27}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Reduce, 22}, {Act::Reduce, 22}, {Act::Reduce, 22}, {Act::Reduce, 22}, {Act::Reduce, 22}, {Act::Reduce, 22}, {Act::Reduce, 22}, {Act::Reduce, 22}, {Act::Err,    0},   {Act::Reduce, 22},  {Act::Reduce, 22},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 22},  {Act::Err,    0},  {Act::Reduce, 22},  {Act::Err,   0},  {Act::Reduce, 22}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Reduce, 19}, {Act::Err,    0},   {Act::Reduce, 19},  {Act::Reduce, 19},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 19},  {Act::Err,    0},  {Act::Reduce, 19},  {Act::Err,   0},  {Act::Reduce, 19}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Reduce, 23}, {Act::Reduce, 23}, {Act::Reduce, 23}, {Act::Reduce, 23}, {Act::Reduce, 23}, {Act::Reduce, 23}, {Act::Reduce, 23}, {Act::Reduce, 23}, {Act::Err,    0},   {Act::Reduce, 23},  {Act::Reduce, 23},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 23},  {Act::Err,    0},  {Act::Reduce, 23},  {Act::Err,   0},  {Act::Reduce, 23}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Reduce, 20}, {Act::Reduce, 20}, {Act::Reduce, 20}, {Act::Reduce, 20}, {Act::Reduce, 20}, {Act::Reduce, 20}, {Act::Reduce, 20}, {Act::Reduce, 20}, {Act::Err,    0},   {Act::Reduce, 20},  {Act::Reduce, 20},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 20},  {Act::Err,    0},  {Act::Reduce, 20},  {Act::Err,   0},  {Act::Reduce, 20}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Reduce, 24}, {Act::Reduce, 24}, {Act::Reduce, 24}, {Act::Reduce, 24}, {Act::Err,    0},   {Act::Reduce, 24},  {Act::Reduce, 24},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 24},  {Act::Err,    0},  {Act::Reduce, 24},  {Act::Err,   0},  {Act::Reduce, 24}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Reduce, 17}, {Act::Err,    0},   {Act::Reduce, 17},  {Act::Reduce, 17},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 17},  {Act::Err,    0},  {Act::Reduce, 17},  {Act::Err,   0},  {Act::Reduce, 17}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Reduce, 18}, {Act::Err,    0},   {Act::Reduce, 18},  {Act::Reduce, 18},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 18},  {Act::Err,    0},  {Act::Reduce, 18},  {Act::Err,   0},  {Act::Reduce, 18}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Reduce, 26}, {Act::Reduce, 26}, {Act::Err,    0},   {Act::Reduce, 26},  {Act::Reduce, 26},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 26},  {Act::Err,    0},  {Act::Reduce, 26},  {Act::Err,   0},  {Act::Reduce, 26}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Reduce, 25}, {Act::Reduce, 25}, {Act::Reduce, 25}, {Act::Reduce, 25}, {Act::Err,    0},   {Act::Reduce, 25},  {Act::Reduce, 25},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 25},  {Act::Err,    0},  {Act::Reduce, 25},  {Act::Err,   0},  {Act::Reduce, 25}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Reduce, 21}, {Act::Reduce, 21}, {Act::Reduce, 21}, {Act::Reduce, 21}, {Act::Reduce, 21}, {Act::Reduce, 21}, {Act::Reduce, 21}, {Act::Reduce, 21}, {Act::Err,    0},   {Act::Reduce, 21},  {Act::Reduce, 21},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 21},  {Act::Err,    0},  {Act::Reduce, 21},  {Act::Err,   0},  {Act::Reduce, 21}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 15}, {Act::Reduce, 15}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Reduce, 15}, {Act::Reduce, 15}, {Act::Reduce, 15}, {Act::Reduce, 15}, {Act::Reduce, 15}, {Act::Reduce, 15}, {Act::Reduce, 15}, {Act::Reduce, 15}, {Act::Err,    0},   {Act::Reduce, 15},  {Act::Reduce, 15},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 15},  {Act::Err,    0},  {Act::Reduce, 15},  {Act::Err,   0},  {Act::Reduce, 15}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 10},  {Act::Reduce, 10},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift, 40}, {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  110}, {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 35}, {Act::Reduce, 35}, {Act::Reduce, 35}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 35}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  18}, {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Err, 0}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 52},  {Act::Reduce, 52}, {Act::Reduce, 52},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Reduce, 52}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  50},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  112}, {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Err, 0}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 44},  {Act::Reduce, 44}, {Act::Reduce, 44},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Reduce, 44}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  113}, {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Shift,  114}, {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  115}, {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  117}, {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Err, 0}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 43},  {Act::Reduce, 43}, {Act::Reduce, 43},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Reduce, 43}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  118}, {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Reduce, 32}, {Act::Err,    0},   {Act::Reduce, 32},  {Act::Reduce, 32},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 32},  {Act::Err,    0},  {Act::Reduce, 32},  {Act::Err,   0},  {Act::Reduce, 32}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 13},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 13}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 59},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 59},  {Act::Reduce, 59}, {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Reduce, 33}, {Act::Shift,  120}, {Act::Err,    0},   {Act::Reduce, 33},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  27}, {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Err, 0}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 42},  {Act::Reduce, 42}, {Act::Reduce, 42},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Reduce, 42}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Err, 0}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 51},  {Act::Reduce, 51}, {Act::Reduce, 51},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Reduce, 51}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  123}, {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Err, 0}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 48},  {Act::Reduce, 48}, {Act::Reduce, 48},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Reduce, 48}, {Act::Err,    0}},
                                    {{Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Err, 0}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 49},  {Act::Reduce, 49}, {Act::Reduce, 49},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Reduce, 49}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Reduce, 55},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Reduce, 55},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  39}, {Act::Shift,  37}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  36}, {Act::Shift,  33},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Shift,  35}, {Act::Shift,  34}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  125}, {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Shift,  126}, {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Err, 0}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 50},  {Act::Reduce, 50}, {Act::Reduce, 50},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Reduce, 50}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Shift,  66}, {Act::Shift,  54}, {Act::Shift,  61}, {Act::Shift,  62}, {Act::Shift,  57}, {Act::Shift,  59}, {Act::Shift,  65}, {Act::Shift,  56}, {Act::Shift,  58}, {Act::Shift,  60}, {Act::Shift,  64}, {Act::Shift,  63}, {Act::Shift,  55}, {Act::Err,    0},   {Act::Err,    0},   {Act::Shift,  127}, {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Err, 0}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 46},  {Act::Reduce, 46}, {Act::Reduce, 46},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Err,    0}},
                                    {{Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Err, 0}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 47},  {Act::Reduce, 47}, {Act::Reduce, 47},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Err,    0}},
                                    {{Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Err, 0}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 41},  {Act::Reduce, 41}, {Act::Reduce, 41},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Reduce, 41}, {Act::Err,    0}},
                                    {{Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err, 0}, {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0},  {Act::Err,    0}},
                                    {{Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Err, 0}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 47},  {Act::Reduce, 47}, {Act::Reduce, 47},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Reduce, 47}, {Act::Err,    0}},
                                    {{Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Err, 0}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Err,    0},   {Act::Err,    0},   {Act::Reduce, 46},  {Act::Reduce, 46}, {Act::Reduce, 46},  {Act::Err,    0},   {Act::Err,    0},  {Act::Err,    0},   {Act::Err,   0},  {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Reduce, 46}, {Act::Err,    0}},
};
const static uint Goto[131][20] = {{1,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   6,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  4, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   11, 9, 8,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  16},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   19, 9, 8,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  23, 22, 21, 0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 24, 0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  25, 22, 21, 0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  16},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  41,  0,  38,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  42,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 44, 0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  45, 0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   47, 0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   48, 0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  49,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  51},
                                   {0,   0,   0,  0, 0,  0,   0,  52,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  53,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  67,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  68,  70, 38,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   74, 0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  76,  0,  0,  0,  0,  0,   0,  0, 78, 77, 0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  79,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  80,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  81,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  82,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  83,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  84,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  85,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  86,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  87,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  88,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  89,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  90,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  91,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  94,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   100, 0,  0, 0,  0,   0,  99,  0,  0,  0,  0,  97,  0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  109, 0,  38,  0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   11, 9, 8,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  111},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  116, 0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  119, 0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  121, 0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  122, 0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  124, 0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   100, 0,  0, 0,  0,   0,  99,  0,  0,  0,  0,  128, 0,  0, 0,  0,  0, 0,  0},
                                   {0,   100, 0,  0, 0,  0,   0,  99,  0,  0,  0,  0,  129, 0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {130, 0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
                                   {0,   0,   0,  0, 0,  0,   0,  0,   0,  0,  0,  0,  0,   0,  0, 0,  0,  0, 0,  0},
};

void parse() {
    while (true) {
        Act act = ACTION[state][token.kind];
        switch (act.kind) {
            case Act::Shift: {
                stk.emplace_back(token, act.val);
                state = act.val;
                token = lexer.next();
                break;
            }
            case Act::Reduce: {
                StackItem __;
                switch (act.val) {
                    case 61: {
                        fsadfasdf
                        break;
                    }
                    case 60: {
                        fsdaf
                        break;
                    }
                    case 29: {
                        dfas
                        break;
                    }
                    case 28: {
                        dfas
                        break;
                    }
                    case 27: {
                        dfas
                        break;
                    }
                    case 26: {
                        dfas
                        break;
                    }
                    case 25: {
                        dfas
                        break;
                    }
                    case 24: {
                        dfas
                        break;
                    }
                    case 23: {
                        dfas
                        break;
                    }
                    case 22: {
                        dfas
                        break;
                    }
                    case 21: {
                        dfas
                        break;
                    }
                    case 20: {
                        dfas
                        break;
                    }
                    case 19: {
                        fdsa
                        break;
                    }
                    case 18: {
                        [id]break;
                    }
                    case 17: {
                        ["L", "E", "R"]break;
                    }
                    case 16: {
                        ["E", "mul", "E"]break;
                    }
                    case 15: {
                        gfsd
                        sfdgs sdfg
                        dfa sd
                        break;
                    }
                    case 14: {
                        fasdf
                        break;
                    }
                    case 1: {
                        fasdf
                        break;
                    }
                    case 2: {
                        fasd adf
                        break;
                    }
                    case 3: {
                        dfas
                        break;
                    }
                    case 4: {
                        dfas
                        break;
                    }
                    case 5: {
                        fasd
                        break;
                    }
                    case 6: {
                        fas
                        break;
                    }
                    case 7: {
                        fasdf
                        break;
                    }
                    case 8: {
                        dfas
                        break;
                    }
                    case 9: {
                        fads
                        break;
                    }
                    case 10: {
                        dfas
                        break;
                    }
                    case 11: {
                        dasfa
                        break;
                    }
                    case 12: {
                        fadsf
                        break;
                    }
                    case 13: {
                        fads
                        break;
                    }
                    case 30: {
                        dfas
                        break;
                    }
                    case 31: {
                        dfa
                        break;
                    }
                    case 32: {
                        dsaf
                        break;
                    }
                    case 33: {
                        dsfa
                        break;
                    }
                    case 34: {
                        adfasdf
                        break;
                    }
                    case 35: {
                        adsf
                        break;
                    }
                    case 36: {
                        fdsa
                        break;
                    }
                    case 37: {
                        afsdf
                        break;
                    }
                    case 38: {
                        asdf
                        break;
                    }
                    case 39: {
                        afds
                        break;
                    }
                    case 40: {
                        adsf
                        break;
                    }
                    case 41: {
                        sdaf
                        break;
                    }
                    case 42: {
                        dasf
                        break;
                    }
                    case 43: {
                        fasd
                        break;
                    }
                    case 44: {
                        das
                        break;
                    }
                    case 45: {
                        fdsa
                        break;
                    }
                    case 46: {
                        dfsa
                        break;
                    }
                    case 47: {
                        fdsa
                        break;
                    }
                    case 48: {
                        dsfa
                        break;
                    }
                    case 49: {
                        fdas
                        break;
                    }
                    case 50: {
                        afds
                        break;
                    }
                    case 51: {
                        dsafs
                        break;
                    }
                    case 52: {
                        adfs
                        break;
                    }
                    case 53: {
                        fads
                        break;
                    }
                    case 54: {
                        adsf
                        break;
                    }
                    case 55: {
                        dasf
                        break;
                    }
                    case 56: {
                        fdas
                        break;
                    }
                    case 57: {
                        fdas
                        break;
                    }
                    case 58: {
                        fdas
                        break;
                    }
                    case 59: {
                        fas
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
}