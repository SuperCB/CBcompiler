
#file(GLOB_RECURSE source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(front  ${CMAKE_CURRENT_SOURCE_DIR}/front/parse.cpp ${CMAKE_CURRENT_SOURCE_DIR}/front/ast.h)

