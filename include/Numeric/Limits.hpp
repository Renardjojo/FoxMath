/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-06 - 22 h 09
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

#include <limits> //std::numeric_limits<T>::espilon()
#include <cmath> //abs
#include "../Type/SFINAShorthand.hpp" // Type::IsArithmetic<T>

namespace FoxMath::Numeric
{
    template<typename T, Type::IsArithmetic<T> = true>
    inline constexpr
    bool isSame(T v1, T v2)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return std::abs(v1 - v2) <= std::numeric_limits<T>::epsilon();
        }
        else
        {
            return v1 == v2; 
        }
    }

    template<typename T, Type::IsArithmetic<T> = true>
    inline constexpr
    bool isSameAsZero(T v1)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return std::abs(v1) <= std::numeric_limits<T>::epsilon(); 
        }
        else
        {
            return v1 == static_cast<T>(0); 
        }
    }

} /*namespace FoxMath::Numeric*/
