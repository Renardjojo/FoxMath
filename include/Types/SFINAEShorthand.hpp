/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-05 - 09 h 35
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

#include <type_traits>

namespace FoxMath::Type
{
    /**
     * @brief Sfinae shorthand for std::is_signed_v
     * @note us
     * @tparam T Type to test
     */
    template<typename T>
    using IsSigned = std::enable_if_t<std::is_signed_v<T>, bool>;

    /**
     * @brief Viariadic form of IsSigned
     * 
     * @tparam TType 
     */
    template<typename... TType>
    using IsAllSigned = std::enable_if_t<(std::is_signed_v<TType> && ...), bool>;

    /**
     * @brief Sfinae shorthand for std::is_unsigned_v
     * @note usage : `template<IsUnsigned<T> = true>`
     * @tparam T Type to test
     */
    template<typename T>
    using IsUnsigned = std::enable_if_t<std::is_unsigned_v<T>, bool>;

    /**
     * @brief Viariadic form of IsUnsigned
     * 
     * @tparam TType 
     */
    template<typename... TType>
    using IsAllUnsigned = std::enable_if_t<(std::is_unsigned_v<TType> && ...), bool>;

    /**
     * @brief Sfinae shorthand for std::is_arithmetic_v
     * @note usage : `template<IsArithmetic<T> = true>`
     * @tparam T Type to test
     */
    template<typename T>
    using IsArithmetic = std::enable_if_t<std::is_arithmetic_v<T>, bool>;

    /**
     * @brief Viariadic form of IsArithmetic
     * 
     * @tparam TType 
     */
    template<typename... TType>
    using IsAllArithmetic = std::enable_if_t<(std::is_arithmetic_v<TType> && ...), bool>;

    /**
     * @brief Sfinae shorthand for std::is_floating_point_v
     * @note usage : `template<IsFloatingPoint<T> = true>`
     * @tparam T Type to test
     */
    template<typename T>
    using IsFloatingPoint = std::enable_if_t<std::is_floating_point_v<T>, bool>;

    /**
     * @brief Viariadic form of IsFloatingPoint
     * 
     * @tparam TType 
     */
    template<typename... TType>
    using IsAllFloatingPoint = std::enable_if_t<(std::is_floating_point_v<TType> && ...), bool>;

    /**
     * @brief Sfinae shorthand for std::is_same
     * @note usage : `template<IsSame<T1, T2> = true>`. Can be use with Pack : `template<typename... VT, Type::IsSame<Type::Pack<T, VT...>, Type::Pack<T..., VT>> = true>`
     * @tparam TType1 to test
     * @tparam TType2 to test
     */
    template<typename TType1, typename TType2>
    using IsSame = std::enable_if_t<std::is_same_v<TType1, TType2>, bool>;

    /**
     * @brief Viariadic form of IsSame
     * 
     * @tparam TBase 
     * @tparam TTypeOther 
     */
    template<typename TBase, typename... TTypeOther>
    using IsAllSame = std::enable_if_t<(std::is_same_v<TBase, TTypeOther> && ...), bool>;

    /**
     * @brief Sfinae shorthand for std::is_constructible_v
     * 
     * @tparam TBase 
     * @tparam TArgs 
     */
    template<typename TBase, typename ...TArgs>
    using IsConstructible = std::enable_if_t<std::is_constructible_v<TBase, TArgs...>, bool>;


    /**
     * @brief Sfinae shorthand for std::is_convertible_v
     * 
     * @tparam TTypeFrom 
     * @tparam TTypeTo 
     */
    template<typename TTypeFrom, typename TTypeTo>
    using IsConvertible = std::enable_if_t<std::is_convertible_v<TTypeFrom, TTypeTo>, bool>;

    /**
     * @brief Sfinae shorthand for operator==
     * @note usage :
     * @tparam A to test
     * @tparam B to test
     */
    template<auto A, auto B>
    using IsEqualTo = std::enable_if_t<(A == B), bool>;

    /**
     * @brief Sfinae shorthand for operator!=
     * @note usage :
     * @tparam A to test
     * @tparam B to test
     */
    template<auto A, auto B>
    using IsNotEqualTo = std::enable_if_t<(A != B), bool>;

    /**
     * @brief Sfinae shorthand for operator<
     * @note usage :
     * @tparam A to test
     * @tparam B to test
     */
    template<auto A, auto B>
    using IsLessThan = std::enable_if_t<(A < B), bool>;

    /**
     * @brief Sfinae shorthand for operator>
     * @note usage :
     * @tparam A to test
     * @tparam B to test
     */
    template<auto A, auto B>
    using IsGreaterThan = std::enable_if_t<(A > B), bool>;

    /**
     * @brief Sfinae shorthand for operator<=
     * @note usage :
     * @tparam A to test
     * @tparam B to test
     */
    template<auto A, auto B>
    using IsLessThanOrEqualTo = std::enable_if_t<(A <= B), bool>;
    
    /**
     * @brief Sfinae shorthand for operator>=
     * @note usage :
     * @tparam A to test
     * @tparam B to test
     */
    template<auto A, auto B>
    using IsGreaterThanOrEqualTo = std::enable_if_t<(A >= B), bool>;

} /*namespace FoxMath::Type*/