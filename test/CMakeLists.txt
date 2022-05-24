file(GLOB BUSTUB_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")

add_executable(regex2dfa regex2dfa.cpp)

target_link_libraries(regex2dfa  CBlibrary gtest gmock_main)