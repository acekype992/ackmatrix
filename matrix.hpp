// MIT License
//
// Copyright (c) 2022 acekype992
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef ACK_MATRIX_HPP
#define ACK_MATRIX_HPP

#include "matrix_traits.hpp"
#include <algorithm>
#include <concepts>
#include <numeric>
#include <ostream>
#include <iostream>

namespace ack {


template<class Tp_, std::size_t M_, std::size_t N_>
requires std::integral<Tp_> || std::floating_point<Tp_>
class basic_numeric_matrix;


template<std::size_t M_, std::size_t N_> using MatrixInt = basic_numeric_matrix<int, M_, N_>;
template<std::size_t M_, std::size_t N_> using MatrixF = basic_numeric_matrix<float, M_, N_>;


template<class Tp_, std::size_t M_, std::size_t N_>
basic_numeric_matrix<Tp_, M_, N_>
                    operator+(basic_numeric_matrix<Tp_, M_, N_> lhs,
                                const basic_numeric_matrix<Tp_, M_, N_> &rhs) noexcept
{
    lhs += rhs;
    return lhs;
}


template<class Tp_, std::size_t M_, std::size_t N_>
basic_numeric_matrix<Tp_, M_, N_>
                    operator-(basic_numeric_matrix<Tp_, M_, N_> lhs,
                                const basic_numeric_matrix<Tp_, M_, N_> &rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}


template<class Tp_, std::size_t M_, std::size_t N_>
basic_numeric_matrix<Tp_, M_, MatrixInt<N_, M_>::columns>
                    operator*(const basic_numeric_matrix<Tp_, M_, N_> &lhs,
                                const basic_numeric_matrix<Tp_, N_, M_> &rhs) noexcept
{
    MatrixInt<lhs.rows, rhs.columns> result;
    std::size_t rx_counter {0};
    std::size_t ry_counter {0};

    for(std::size_t y {0}; y < lhs.rows; ++y)
    {
        const auto current_row {lhs.get_row(y)};
        for(std::size_t x {0}; x < rhs.columns; ++x)
        {
            const auto current_column {rhs.get_column(x)};
            Tp_ val {0};
            for(std::size_t j {0}; j < N_; ++j)
                val += current_row(0, j) * current_column(j, 0);

            result(y, x) = val;
        }
    }

    return result;
}


template<class Tp_, std::size_t M_, std::size_t N_>
std::ostream& operator<<(std::ostream &stream, const basic_numeric_matrix<Tp_, M_, N_> &matrix)
{
    for(std::size_t y {0}; y < matrix.rows; ++y)
    {
        for(std::size_t x {0}; x < matrix.columns; ++x)
            stream << matrix(y, x) << " ";

        stream << (y < matrix.rows -1 ? "\n" : "");
    }

    return stream;
}



template<class Tp_, std::size_t M_, std::size_t N_>
requires std::integral<Tp_> || std::floating_point<Tp_>
class basic_numeric_matrix final
{
    using _mx_traits = matrix_traits<Tp_, M_, N_>;
    using matrix_type = typename _mx_traits::container_type;

public:
    using size_type = std::size_t;
    using value_type = Tp_;

    static inline constexpr const size_type rows {M_};
    static inline constexpr const std::size_t columns {N_};

    using row_vector    = basic_numeric_matrix<Tp_, 1, N_>;
    using column_vector = basic_numeric_matrix<Tp_, M_, 1>;
    using matrix_transposed = basic_numeric_matrix<Tp_, N_, M_>;
    using matrix_multiplied = basic_numeric_matrix<Tp_, M_, matrix_transposed::columns>;


    basic_numeric_matrix()
    {
        fill(value_type{});
    }


    basic_numeric_matrix(const value_type &data)
    {
        fill(data);
    }


    ~basic_numeric_matrix() noexcept = default;


    void fill(value_type value) noexcept
    {
        std::ranges::fill_n(mx_.data(), rows * columns, value);
    }


    matrix_transposed transposed() const
    {
        matrix_transposed mxT;

        for(std::size_t y {0}; y < rows; ++y)
            for(std::size_t x {0}; x < columns; ++x)
                mxT(x, y) = (*this)(y, x);

        return mxT;
    }


    const value_type& operator()(size_type row, size_type column) const noexcept
    {
        return mx_[_mx_traits::offset(row, column)];
    }


    value_type& operator()(size_type row, size_type column) noexcept
    {
        return mx_[_mx_traits::offset(row, column)];
    }


    basic_numeric_matrix& operator*=(value_type factor) noexcept
    {
        for(std::size_t y {0}; y < rows; ++y)
            for(std::size_t x {0}; x < columns; ++x)
                (*this)(y, x) *= factor;

        return *this;
    }


    basic_numeric_matrix& operator+=(const basic_numeric_matrix &other) noexcept
    {
        for(std::size_t y {0}; y < rows; ++y)
            for(std::size_t x {0}; x < columns; ++x)
                (*this)(y, x) += other(y, x);

        return *this;
    }


    basic_numeric_matrix& operator-=(const basic_numeric_matrix &other) noexcept
    {
        for(std::size_t y {0}; y < rows; ++y)
            for(std::size_t x {0}; x < columns; ++x)
                (*this)(y, x) -= other(y, x);

        return *this;
    }


    row_vector get_row(size_type index) const noexcept
    {
        row_vector row;
        for(size_type n {0}; n < N_; ++n)
            row(0, n) = (*this)(index, n);

        return row;
    }


    column_vector get_column(size_type index) const noexcept
    {
        column_vector column;
        for(size_type m {0}; m < M_; ++m)
            column(m, 0) = (*this)(m, index);

        return column;
    }


private:
    matrix_type mx_;
};

} // ack

#endif // ACK_BINARY_FILE_HPP
