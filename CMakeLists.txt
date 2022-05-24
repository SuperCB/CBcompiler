cmake_minimum_required(VERSION 3.21)
project(CBcompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})
# gmock gtest https://crascit.com/2015/07/25/cmake-gtest/
configure_file("${PROJECT_SOURCE_DIR}/gtest_CMakeLists.txt.in" googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # don't override our compiler/linker options when building gtest
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src" "${CMAKE_BINARY_DIR}/googletest-build")

add_subdirectory(test)
file(GLOB_RECURSE CBlibrary_source ${PROJECT_SOURCE_DIR}/src/*/*.cpp ${PROJECT_SOURCE_DIR}/src/*/*.h)

add_library(CBlibrary
        STATIC
        ${CBlibrary_source}
        )

add_executable(CBcompiler main.cpp src/JsonReader/JsonReader.cpp src/JsonReader/JsonReader.h)

target_link_libraries(CBcompiler CBlibrary)





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