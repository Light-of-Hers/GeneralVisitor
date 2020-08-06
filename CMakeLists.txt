cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
        COMPILE_FLAGS "-d")
FLEX_TARGET(scanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(calculator main.cpp general_visitor.h node.h
        ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})
