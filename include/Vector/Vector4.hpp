/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-09 - 14 h 57
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

#include "Vector/GenericVector.hpp"
#include "Types/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>, Type::IsSame, Type::Pack

namespace FoxMath::Vector
{
    template <typename TType>
    class Vector4 : public Vector<4, TType>
    {
        private:
    
        protected:
    
        #pragma region attribut
        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods
        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        Vector4 ()					                = default;
        Vector4 (const Vector4& other)			    = default;
        Vector4 (Vector4&& other)				    = default;
        virtual ~Vector4 ()				            = default;
        Vector4& operator=(Vector4 const& other)    = default;
        Vector4& operator=(Vector4 && other)		= default;

        /**
         * @brief Construct a new vector with it's base type
         * 
         * @tparam TTlengthOther 
         * @param other 
         */
        template <size_t TTlengthOther>
        Vector4 (const Vector<TTlengthOther, TType>& other)
            : Vector<4, TType>(other) {}


        /**
         * @brief Variadic templated constructor to init member
         * @example `FoxMath::Vector::Vector<4, int> vec (1, 1, 4)` or `FoxMath::Vector::Vector<4, int> vec (1, 4)`
         * @tparam T 
         * @tparam Sfinae IsSame 
         */
        template<typename... T, Type::IsSame<Type::Pack<TType, T...>, Type::Pack<T..., TType>> = true,
        Type::IsLessThanOrEqualTo<sizeof...(T), 4> = true>
        explicit inline constexpr
        Vector4 (T... args) noexcept
            : Vector<4, TType>(args...) {}

        /**
         * @brief Variadic templated constructor to init member with vector and scalar
         * @example `FoxMath::Vector::Vector<10, int> vect(FoxMath::Vector::Vector<5, int>(), 4, 41)`
         * @tparam TLengthOther 
         * @tparam TScalarArgs
         */
        template<size_t TLengthOther, typename... TScalarArgs, 
        Type::IsSame<Type::Pack<TType, TScalarArgs...>, Type::Pack<TScalarArgs..., TType>> = true,
        Type::IsLessThanOrEqualTo<sizeof...(TScalarArgs) + TLengthOther, 4> = true,
        Type::IsLessThan<TLengthOther, 4> = true>
        explicit inline constexpr
        Vector4 (const Vector<TLengthOther, TType>& other, TScalarArgs... args) noexcept
            : Vector<4, TType>(other, args...) {}

        #pragma endregion //!constructor/destructor
    
        #pragma region methods
        #pragma endregion //!methods
    
        #pragma region accessor
        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector4& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector4& operator=(const Vector<TLengthOther, TTypeOther>& other) noexcept
        {
            Vector<4, TType>::operator=(other);
            return *this;
        }

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector4& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector4& operator=(TscalarType scalar) noexcept
        {
            Vector<4, TType>::operator=(scalar);
            return *this;
        }

        #pragma endregion //!operator
    
        #pragma region convertor

        #pragma endregion //!convertor
    
        #pragma region static attribut

        static constexpr inline Vector4 zero      = Vector4(static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector4 one       = Vector4(static_cast<TType>(1), static_cast<TType>(1), static_cast<TType>(1), static_cast<TType>(0));
		static constexpr inline Vector4 up        = Vector4(static_cast<TType>(0), static_cast<TType>(1), static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector4 down      = Vector4(static_cast<TType>(0), static_cast<TType>(-1), static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector4 right     = Vector4(static_cast<TType>(1), static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector4 left      = Vector4(static_cast<TType>(-1), static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector4 forward   = Vector4(static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(1), static_cast<TType>(0));
		static constexpr inline Vector4 backward  = Vector4(static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(-1), static_cast<TType>(0));

        #pragma endregion //! static attribut
    };

    template <typename TType>
    using Vec4          = Vector4<TType>;

    using Vector4f      = Vector4<float>;
    using Vec4f         = Vector4f;
    using Vector4d      = Vector4<double>;
    using Vec4d         = Vector4d;
    using Vector4ld     = Vector4<long double>;
    using Vec4ld        = Vector4ld;

    using Vector4uc     = Vector4<unsigned char>;
    using Vec4uc        = Vector4uc;
    using Vector4c      = Vector4<char>;
    using Vec4c         = Vector4c;
    using Vector4ui     = Vector4<unsigned int>;
    using Vec4ui        = Vector4ui;
    using Vector4i      = Vector4<int>;
    using Vec4i         = Vector4i;
    using Vector4lui    = Vector4<long unsigned int>;
    using Vec4lui       = Vector4lui;
    using Vector4st     = Vector4<size_t>;
    using Vec4st        = Vector4st;
    using Vector4li     = Vector4<long int>;
    using Vec4li        = Vector4li;
    
    using Vector4b      = Vector4<bool>;
    using Vec4b         = Vector4b;

} /*namespace FoxMath::Vector*/
