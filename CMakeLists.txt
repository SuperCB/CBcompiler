cmake_minimum_required(VERSION 3.21)
project(CBcompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

include_directories(yaml-cpp/yaml-cpp/include)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # don't override our compiler/linker options when building gtest


add_subdirectory(test)


add_subdirectory(src)
file(GLOB_RECURSE CBlibrary_source ${PROJECT_SOURCE_DIR}/lib/*/*.cpp ${PROJECT_SOURCE_DIR}/lib/*/*.h)


add_subdirectory(yaml-cpp/yaml-cpp)

add_library(CBlibrary
        STATIC
        ${CBlibrary_source}
        )

add_executable(CBcompiler main.cpp )

target_link_libraries(CBcompiler CBlibrary yaml-cpp)


include(ExternalProject)
ExternalProject_Add(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
        SOURCE_DIR "${CMAKE_BINARY_DIR}/googletest-src"
        BINARY_DIR "${CMAKE_BINARY_DIR}/googletest-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )

add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src" "${CMAKE_BINARY_DIR}/googletest-build")