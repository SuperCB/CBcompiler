file(GLOB BUSTUB_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")

add_executable(regex2dfa regex2dfa.cpp)
add_executable(ssa ssatest.cpp)
add_executable(lalr lalrtest.cpp)
add_executable(empty  emptytest.cpp)
add_executable(yaml yamlcpptest.cpp)
add_executable(compilertest compilertest.cpp)
add_executable(lextest lextest.cpp ../src/front/lex.h)




target_link_libraries(lextest  gtest gmock_main)
target_link_libraries(compilertest CBlibrary gtest gmock_main yaml-cpp)
target_link_libraries(empty CBlibrary gtest gmock_main yaml-cpp)
target_link_libraries(yaml yaml-cpp gtest gmock_main)
target_link_libraries(lalr CBlibrary gtest gmock_main yaml-cpp)
target_link_libraries(ssa CBlibrary gtest gmock_main)
target_link_libraries(regex2dfa CBlibrary gtest gmock_main)