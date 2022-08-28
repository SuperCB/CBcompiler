
#file(GLOB_RECURSE source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)



add_executable(front  ${CMAKE_CURRENT_SOURCE_DIR}/front/parse.cpp ast.h)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ssa.h ${CMAKE_CURRENT_SOURCE_DIR}/ssa.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/ir.h ${CMAKE_CURRENT_SOURCE_DIR}/ir.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/typecheck.h ${CMAKE_CURRENT_SOURCE_DIR}/typecheck.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/ast.cpp
        )
