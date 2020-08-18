/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-18 - 10 h 12
 * 
 * 
 * MIT License
 * 
 * Copyright (c) 2020 Six Jonathan
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

namespace FoxMath::Matrix
{

    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    constexpr inline
    size_t GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::vectorLength () const noexcept
    {
        if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
            return TColumnSize;
        else 
            return TRowSize;
    }

    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    constexpr inline
    size_t GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::numberOfVectorInMatrix () const noexcept
    {
        if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
            return TRowSize;
        else 
            return TColumnSize;
    }

} /*namespace FoxMath::Matrix*/
