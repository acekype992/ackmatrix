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

#ifndef ACK_MATRIX_TRAITS_HPP
#define ACK_MATRIX_TRAITS_HPP

#include <array>
#include <cassert>

namespace ack {

template<class Tp_, std::size_t M_, std::size_t N_>
struct matrix_traits
{
    using container_type = std::array<Tp_, M_*N_>;
    using size_type = std::size_t;

    static constexpr
    size_type offset(size_type row, size_type column) noexcept
    {
        assert(row < M_ && "Invalid line requested.");
        assert(column < N_ && "Invalid column requested.");
        return column * M_ + row;
    }
};

} // ack

#endif // ACK_MATRIX_TRAITS_HPP
