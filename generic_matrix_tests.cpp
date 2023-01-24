///
/// @file generic_matrix_tests.cpp
/// @brief tests for GenericMatrix class
/// @author acekype992
///

#include <cassert>
#include <iostream>

#include "generic_matrix.hpp"

#define __ack__START_TEST {std::cout << "[" <<__TIME__ << \
                                "] ack_tests_func : " <<  \
                                    __PRETTY_FUNCTION__ << std::endl;

#define __ack__END_TEST std::cout  << "[" <<__TIME__ <<  \
                                "] " << "OK\n";}


void tst_fill() __ack__START_TEST

    ack::GenericMatrix<char, 10, 7> mat;
    char letter {'K'};
    mat.fill(letter);

    for(std::size_t y {0}; y < mat.rows; ++y)
        for(std::size_t x {0}; x < mat.columns; ++x)
            assert(mat(x, y) == letter && "tst_fill failed.");

__ack__END_TEST


///////////////////////////////
// only GenericMatrix type number //
///////////////////////////////
void tst_addition() __ack__START_TEST

    ack::GenericMatrix<int, 3, 4> mat_1;
    mat_1(0,0) = 1;  mat_1(1,3) = 3;  mat_1(2,3) = 5;
    mat_1(0,1) = 0;  mat_1(1,2) = 2;  mat_1(2,2) = 4;
    mat_1(0,2) = 7;  mat_1(1,1) = 9;  mat_1(2,1) = 0;
    mat_1(0,3) = 6;  mat_1(1,0) = 0;  mat_1(2,0) = 8;

    ack::GenericMatrix<int, 3, 4> mat_2;
    mat_2(0,0) = -5;  mat_2(1,3) = 10;  mat_2(2,3) =  2;
    mat_2(0,1) =  1;  mat_2(1,2) = -3;  mat_2(2,2) =  7;
    mat_2(0,2) = 21;  mat_2(1,1) = 4;   mat_2(2,1) = -1;
    mat_2(0,3) =  0;  mat_2(1,0) = -8;  mat_2(2,0) =  1;

    ack::GenericMatrix<int, 3, 4> mat_result;
    mat_result(0,0) = -4;  mat_result(1,3) = 13;  mat_result(2,3) =  7;
    mat_result(0,1) =  1;  mat_result(1,2) = -1;  mat_result(2,2) =  11;
    mat_result(0,2) = 28;  mat_result(1,1) = 13;   mat_result(2,1) = -1;
    mat_result(0,3) =  6;  mat_result(1,0) = -8;  mat_result(2,0) =  9;

    const ack::GenericMatrix<int, 3, 4> mat = mat_1 + mat_2;
    for(std::size_t y {0}; y < mat.rows; ++y)
        for(std::size_t x {0}; x < mat.columns; ++x)
            assert(mat(x,y) == mat_result(x,y) && "tst addition failed");

__ack__END_TEST




void tst_multiplication_factor() __ack__START_TEST

    ack::GenericMatrix<int, 2, 3> mat;
    mat(0,0) = 5;   mat(1,0) = 20;
    mat(0,1) = 10;  mat(1,1) = 25;
    mat(0,2) = 15;  mat(1,2) = 30;

    ack::GenericMatrix<int, 2, 3> mat_result;
    mat_result(0,0) = 15;  mat_result(1,0) = 60;
    mat_result(0,1) = 30;  mat_result(1,1) = 75;
    mat_result(0,2) = 45;  mat_result(1,2) = 90;

    const ack::GenericMatrix<int, 2, 3> mat_bis = mat * 3;
    mat *= 3;

    for(std::size_t y {0}; y < mat.rows; ++y)
        for(std::size_t x {0}; x < mat.columns; ++x) {
            assert(mat(x,y) == mat_result(x,y) && "tst multiplication factor failed");
            assert(mat_bis(x,y) == mat_result(x,y) && "tst multiplication factor failed");
        }

__ack__END_TEST


void tst_multiplication_matrix() __ack__START_TEST

    ack::GenericMatrix<int, 4, 2> mat_1;
    mat_1(0,0) = 1;  mat_1(1,0) = 3;  mat_1(2,0) = 5;  mat_1(3,0) = -2;
    mat_1(0,1) = 0;  mat_1(1,1) = 2;  mat_1(2,1) = 4;  mat_1(3,1) = -3;

    ack::GenericMatrix<int, 2, 4> mat_2;
    mat_2(0,0) =  4;  mat_2(1,0) =  1;
    mat_2(0,1) =  5;  mat_2(1,1) =  2;
    mat_2(0,2) =  6;  mat_2(1,2) =  3;
    mat_2(0,3) = -6;  mat_2(1,3) = -5;

    ack::GenericMatrix<int, 4, 2>::matrix_multiplied mat_result;
    mat_result(0,0) = 61;  mat_result(1,0) = 32;
    mat_result(0,1) = 52;  mat_result(1,1) = 31;

    const auto mat = mat_1 * mat_2;

    for(std::size_t y {0}; y < mat.rows; ++y)
        for(std::size_t x {0}; x < mat.columns; ++x)
            assert(mat(x,y) == mat_result(x,y) && "tst multiplication matrix failed");

__ack__END_TEST


void tst_transposed() __ack__START_TEST


__ack__END_TEST


void tst_get_vector_column() __ack__START_TEST

    ack::GenericMatrix<int, 3, 3> mat;
    mat(0,0) = 1;  mat(1,0) = 2;  mat(2,0) = 3;
    mat(0,1) = 4;  mat(1,1) = 5;  mat(2,1) = 6;
    mat(0,2) = 7;  mat(1,2) = 8;  mat(2,2) = 9;

    ack::GenericMatrix<int, 1, 3> row_vector_result;
    row_vector_result(0,0) = 2;
    row_vector_result(0,1) = 5;
    row_vector_result(0,2) = 8;

    const auto row_vector {mat.get_column(1)};

    for(std::size_t y {0}; y < row_vector.rows; ++y)
        for(std::size_t x {0}; x < row_vector.columns; ++x)
            assert(row_vector(x,y) == row_vector_result(x,y) && "tst get_vector_row failed");

__ack__END_TEST


void tst_get_vector_row() __ack__START_TEST

    ack::GenericMatrix<int, 3, 3> mat;
    mat(0,0) = 1;  mat(1,0) = 2;  mat(2,0) = 3;
    mat(0,1) = 4;  mat(1,1) = 5;  mat(2,1) = 6;
    mat(0,2) = 7;  mat(1,2) = 8;  mat(2,2) = 9;

    ack::GenericMatrix<int, 3, 1> row_vector_result;
    row_vector_result(0,0) = 4; row_vector_result(1,0) = 5; row_vector_result(2,0) = 6;

    const auto row_vector {mat.get_row(1)};

    for(std::size_t y {0}; y < row_vector.rows; ++y)
        for(std::size_t x {0}; x < row_vector.columns; ++x)
            assert(row_vector(x,y) == row_vector_result(x,y) && "tst get_vector_row failed");

    __ack__END_TEST


int main(int argc, char **argv)
{
    /* constructors */
    ack::GenericMatrix<int, 5, 5> mat_char {};
    for(std::size_t y {0}; y < mat_char.rows; ++y)
        for(std::size_t x {0}; x < mat_char.columns; ++x)
            assert(mat_char(x,y) == 0 && "tst constructor default");

    ack::GenericMatrix<float, 7, 3> mat_float {3.1415};
    for(std::size_t y {0}; y < mat_float.rows; ++y)
        for(std::size_t x {0}; x < mat_float.columns; ++x)
            assert(mat_float(x,y) == 3.1415f && "tst constructor with arg failed");

    tst_fill();
    /* only GenericMatrix type number */
    tst_addition();
    tst_multiplication_factor();
    tst_multiplication_matrix();
    tst_get_vector_column();
    tst_get_vector_row();

    std::cout << "\ntst print matrix :\n";
    // Print Matrix Tests :
    std::cout << mat_char << "\n"
              << "\n"
              << mat_float << "\n"
              << std::flush;

    return 0;
}
