//
// Created by supercb on 22-4-26.
//
#pragma once

#include <string_view>
class JsonReader {
public:
    JsonReader()=delete;

    //explicit is interesting
    explicit JsonReader(std::string_view json);


};


