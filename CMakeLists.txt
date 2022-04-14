cmake_minimum_required(VERSION 3.21)
project(CBcompiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(CBcompiler main.cpp Regex2Dfa/Regex2Dfa.cpp Regex2Dfa/Regex2Dfa.h)
