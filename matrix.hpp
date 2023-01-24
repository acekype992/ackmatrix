// MIT License
//
// Copyright (c) 2022 - 2023 acekype992
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

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <numeric>
#include <ostream>

namespace ack {

template<class T_, std::size_t N_, std::size_t M_>
class basic_matrix;

template<class T_, std::size_t N_, std::size_t M_>
requires std::integral<T_> || std::floating_point<T_>
using basic_numeric_matrix = basic_matrix<T_, N_, M_>;

template<std::size_t N_, std::size_t M_> using MatrixF  = basic_numeric_matrix<float, N_, M_>;
template<std::size_t N_, std::size_t M_> using MatrixI  = basic_numeric_matrix<int, N_, M_>;
template<std::size_t N_, std::size_t M_> using MatrixU  = basic_numeric_matrix<unsigned int, N_, M_>;


///
/// \brief The basic_matrix class
///
template<class T_, std::size_t N_, std::size_t M_>
class basic_matrix
{
public:
    using element_type      = T_;
    using container_type    = std::array<T_, N_ * M_>;
    using matrix_type       = basic_matrix<T_, N_, M_>;
    using size_type         = std::size_t;

    static inline constexpr const std::size_t   columns {N_};
    static inline constexpr const size_type     rows    {M_};

    basic_matrix()
    {
        fill(element_type{});
    }

    basic_matrix(const element_type &data)
    {
        fill(data);
    }

    ~basic_matrix() noexcept = default;

    element_type operator()(size_type column, size_type row) const noexcept
    {
        return mx_[matrix_type::at(column, row)];
    }

    element_type& operator()(size_type column, size_type row) noexcept
    {
        return mx_[matrix_type::at(column, row)];
    }

    void fill(element_type value) noexcept
    {
        std::ranges::fill_n(mx_.data(), rows * columns, value);
    }

    container_type* data_container() const
    {
        return &mx_;
    }

private:
    size_type at(std::size_t column, std::size_t row) const noexcept
    {
        assert(row < M_ && "Invalid line requested.");
        assert(column < N_ && "Invalid column requested.");
        return column * M_ + row;
    }

    container_type mx_;
};


///
/// \brief Specialization of basic_matrix class
/// requires integral or floating
///
template<class T_, std::size_t N_, std::size_t M_>
requires std::integral<T_> ||  std::floating_point<T_>
class basic_matrix<T_, N_, M_>
{
    using matrix_type = basic_matrix<T_, N_, M_>;

public:
    using container_type    = std::array<T_, N_ * M_>;
    using size_type         = std::size_t;
    using value_type        = T_;

    static inline constexpr const size_type     rows    {M_};
    static inline constexpr const size_type   columns {N_};

    using row_vector        = basic_matrix<T_, N_, 1>;
    using column_vector     = basic_matrix<T_, 1, M_>;
    using matrix_transposed = basic_matrix<T_, M_, N_>;
    using matrix_multiplied = basic_matrix<T_, M_, matrix_transposed::columns>;

    basic_matrix()
    {
        fill(value_type{});
    }


    basic_matrix(const value_type &data)
    {
        fill(data);
    }


    ~basic_matrix() noexcept = default;


    void fill(value_type value) noexcept
    {
        std::ranges::fill_n(mx_.data(), rows * columns, value);
    }


    matrix_transposed transposed() const
    {
        matrix_transposed mxT;

        for(std::size_t y {0}; y < mxT.rows; ++y)
            for(std::size_t x {0}; x < mxT.columns; ++x)
                mxT(x, y) = (*this)(y, x);

        return mxT;
    }

    value_type operator()(size_type row, size_type column) const noexcept
    {
        return mx_[matrix_type::at(row, column)];
    }


    value_type& operator()(size_type row, size_type column) noexcept
    {
        return mx_[matrix_type::at(row, column)];
    }


    basic_matrix& operator*=(value_type factor) noexcept
    {
        for(std::size_t y {0}; y < rows; ++y)
            for(std::size_t x {0}; x < columns; ++x)
                (*this)(x, y) *= factor;

        return *this;
    }

    basic_matrix& operator+=(const basic_matrix &other) noexcept
    {
        for(std::size_t y {0}; y < rows; ++y)
            for(std::size_t x {0}; x < columns; ++x)
                (*this)(x, y) += other(x, y);

        return *this;
    }

    basic_matrix& operator-=(const basic_matrix &other) noexcept
    {
        for(std::size_t y {0}; y < rows; ++y)
            for(std::size_t x {0}; x < columns; ++x)
                (*this)(x, y) -= other(x, y);

        return *this;
    }

    row_vector get_row(size_type index) const noexcept
    {
        row_vector row;
        for(size_type i {0}; i < columns; ++i)
            row(i, 0) = (*this)(i, index);

        return row;
    }

    column_vector get_column(size_type index) const noexcept
    {
        column_vector column;
        for(size_type i {0}; i < rows; ++i)
            column(0, i) = (*this)(index, i);

        return column;
    }

    container_type* data_container() const
    {
        return &mx_;
    }

    friend
    basic_numeric_matrix<T_, N_, M_>
                        operator+(basic_numeric_matrix<T_, N_, M_> lhs,
                                    const basic_numeric_matrix<T_, N_, M_> &rhs) noexcept
    {
        lhs += rhs;
        return lhs;
    }

    friend
    basic_numeric_matrix<T_, N_, M_>
                        operator-(basic_numeric_matrix<T_, N_, M_> lhs,
                                    const basic_numeric_matrix<T_, N_, M_> &rhs) noexcept
    {
        lhs -= rhs;
        return lhs;
    }

    friend
    basic_numeric_matrix<T_, N_, M_>
                        operator*(basic_numeric_matrix<T_, N_, M_> lhs,
                                    value_type rhs) noexcept
    {
        lhs *= rhs;
        return lhs;
    }

    friend
    matrix_multiplied
                        operator*(const basic_numeric_matrix<T_, N_, M_> &lhs,
                                    const basic_numeric_matrix<T_, M_, N_> &rhs) noexcept
    {
        matrix_multiplied result;
        std::size_t rx_counter {0};
        std::size_t ry_counter {0};

        for(std::size_t y {0}; y < lhs.rows; ++y)
        {
            const auto current_row {lhs.get_row(y)};
            for(std::size_t x {0}; x < rhs.columns; ++x)
            {
                const auto current_column {rhs.get_column(x)};
                T_ val {0};
                for(std::size_t j {0}; j < N_; ++j)
                    val += current_row(j, 0) * current_column(0, j);

                result(x, y) = val;
            }
        }

        return result;
    }

    friend
    std::ostream& operator<<(std::ostream &stream, const basic_numeric_matrix<T_, N_, M_> &matrix)
    {
        for(std::size_t y {0}; y < matrix.rows; ++y)
        {
            for(std::size_t x {0}; x < matrix.columns; ++x)
                stream << matrix(x, y) << " ";

            stream << (y < matrix.rows -1 ? "\n" : "");
        }

        return stream;
    }


private:
    size_type at(std::size_t column, std::size_t row) const noexcept
    {
        assert(row < M_ && "Invalid line requested.");
        assert(column < N_ && "Invalid column requested.");
        return column * M_ + row;
    }

    container_type mx_;
};


} // ack

#endif // ACK_BINARY_FILE_HPP
