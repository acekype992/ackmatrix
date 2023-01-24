cmake_minimum_required(VERSION 3.23)

project(ACKMatrix VERSION 1.0)

add_executable(ackmatrix_tests matrix.hpp matrix_tests.cpp)
set_target_properties(ackmatrix_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
