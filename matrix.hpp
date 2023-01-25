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
#include <cassert>
#include <vector>


namespace ack {


template<class T_>
class Matrix
{
    using element_type      = T_;
    using container_type    = std::vector<T_>;
    using size_type         = std::size_t;

public:
    Matrix() noexcept : columns_ {0}, rows_ {0}
    {}

    explicit Matrix(size_type columns, size_type rows)
        : columns_ {columns}
        , rows_ {rows}
    {
        mx_.resize(columns * rows_, element_type{});
    }

    explicit Matrix(size_type columns, size_type rows, const element_type &data)
        : columns_ {columns}
        , rows_ {rows}
    {
        mx_.resize(columns * rows_, data);
    }

    ~Matrix() noexcept = default;


    element_type operator()(size_type column, size_type row) const noexcept
    {
        return mx_[Matrix::at(column, row)];
    }

    element_type& operator()(size_type column, size_type row) noexcept
    {
        return mx_[Matrix::at(column, row)];
    }

    void create(size_type columns, size_type rows)
    {
        columns_ = columns;
        rows_ = rows;

        mx_.clear();
        mx_.reserve(columns_ * rows_);
    }

    void create(size_type columns, size_type rows, const element_type &element)
    {
        columns_ = columns;
        rows_ = rows;

        mx_.clear();
        mx_.resize(columns_ * rows_, element);
    }

    void fill(const element_type &value) noexcept
    {
        std::ranges::fill_n(mx_.data(), rows_ * columns_, value);
    }

    container_type& data_container() const
    {
        return mx_;
    }

private:
    size_type at(std::size_t column, std::size_t row) const noexcept
    {
        assert(row < rows_ && "Invalid row requested.");
        assert(column < columns_ && "Invalid column requested.");
        return column * rows_ + row;
    }

    size_type columns_;
    size_type rows_;

    std::vector<element_type> mx_;

};

} // ack

#endif // ACK_MATRIX_HPP
