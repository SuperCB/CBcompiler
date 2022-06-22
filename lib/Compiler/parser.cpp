//
// Created by supercb on 22-5-23.
//
using uint = unsigned int;
struct Act {
    enum : uint {
        Shift, Reduce, Acc, Err
    } kind;
    uint val;
};