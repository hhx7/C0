cmake_minimum_required(VERSION 3.10)
project(C0)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp constants/symbol.h symbol_table/symbol_table.h lexer/token.h lexer/lexer.h lexer/lexer.cpp syntax_analysis/syntax_analysis.h syntax_analysis/syntax_analysis.cpp interface/token_stream.h simulator/code_generator/code_generator.h simulator/instruction.h simulator/code_generator/code_generator.cpp symbol_table/symbol_attribute.h symbol_table/symbol_table.cpp symbol_table/symbol_attribute.cpp simulator/simulator.h simulator/simulator.cpp constants/operation_code.h simulator/stack.h AST/node_factory.h AST/abstract_node.h)

add_executable(C0 ${SOURCE_FILES})
set(BOOST_ROOT "/home/pi/C++/include/boost_1_65_0")

find_package(Boost)
if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(C0 "${BOOST_ROOT}/stage/lib/libboost_system.a" "${BOOST_ROOT}/stage/lib/libboost_thread.a" "${BOOST_ROOT}/stage/lib/libboost_filesystem.a")
endif()
