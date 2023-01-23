cmake_minimum_required(VERSION 3.23)

project(ACKMatrix)

add_library(ackmatrix matrix.hpp)
set_target_properties(ackmatrix PROPERTIES
    LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)


add_executable(ackmatrix_tests matrix_tests.cpp)
set_target_properties(ackmatrix_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
