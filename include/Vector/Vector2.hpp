/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-09 - 11 h 06
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
    template <typename TType = float>
    class Vector2 : public Vector<2, TType>
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
    
        constexpr inline
        Vector2 () noexcept			                        = default;

        constexpr inline  
        Vector2 (const Vector2& other) noexcept             = default;

        constexpr inline
        Vector2 (Vector2&& other) noexcept				    = default;

        inline
        ~Vector2 ()	noexcept			                    = default;

        constexpr inline
        Vector2& operator=(Vector2 const& other) noexcept   = default;

        constexpr inline
        Vector2& operator=(Vector2 && other) noexcept		= default;

        /**
         * @brief Construct a new vector with it's base type
         * 
         * @tparam TTlengthOther 
         * @param other 
         */
        template <size_t TTlengthOther>
        inline constexpr
        Vector2 (const Vector<TTlengthOther, TType>& other) noexcept
            : Vector<2, TType>(other) {}

        /**
         * @brief Variadic templated constructor to init member
         * @example `FoxMath::Vector::Vector<2, int> vec (1, 1, 3)` or `FoxMath::Vector::Vector<2, int> vec (1, 2)`
         * @tparam T 
         * @tparam Sfinae IsSame 
         */
        template<typename... T, Type::IsAllSame<TType, T...> = true,
        Type::IsLessThanOrEqualTo<sizeof...(T), 2> = true>
        explicit inline constexpr
        Vector2 (T... args) noexcept
            : Vector<2, TType>(args...) {}

        /**
         * @brief Variadic templated constructor to init member with vector and scalar
         * @example `FoxMath::Vector::Vector<10, int> vect(FoxMath::Vector::Vector<5, int>(), 22, 31)`
         * @tparam TLengthOther 
         * @tparam TScalarArgs
         */
        template<size_t TLengthOther, typename... TScalarArgs, 
        Type::IsAllSame<TType, TScalarArgs...> = true,
        Type::IsLessThanOrEqualTo<sizeof...(TScalarArgs) + TLengthOther, 2> = true,
        Type::IsLessThan<TLengthOther, 2> = true>
        explicit inline constexpr
        Vector2 (const Vector<TLengthOther, TType>& other, TScalarArgs... args) noexcept
            : Vector<2, TType>(other, args...) {}

        #pragma endregion //!constructor/destructor
    
        #pragma region methods


        // /**
        //  * @brief turn Vec2 in counterclockwise
        //  * 
        //  * @param angleDeg 
        //  * @return Vec2& 
        //  */
        // inline constexpr
        // Vec2& 	rotate			(const Angle::Angle<Angle::EAngleType::Radian, TType>& angle) noexcept;

        // [[nodiscard]] inline constexpr
        // Vec2  	getRotate 		(const Angle::Angle<Angle::EAngleType::Radian, TType>& angle) const noexcept;

        // inline constexpr
        // Vec2&  	rotated90 		() noexcept;
    
        // [[nodiscard]] inline constexpr
        // Vec2  	getRotated90 	() const noexcept;

        // inline constexpr
        // Vec2&  	rotated180 		() noexcept;

        // [[nodiscard]] inline constexpr
        // Vec2  	getRotated180	() const noexcept;

        // inline constexpr
        // Vec2&  	rotated270 		() noexcept;

        // [[nodiscard]] inline constexpr
        // Vec2  	getRotated270 	() const noexcept;

        #pragma endregion //!methods
    
        #pragma region accessor

        /**
         * @brief get member X
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getX() const noexcept { return Vector<2, TType>::m_data[0];}

        /**
         * @brief get member Y
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getY() const noexcept { return Vector<2, TType>::m_data[1];}

        #pragma endregion //!accessor

        /**
         * @brief Set member X
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newX 
         * @return constexpr Vector2& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector2& setX(TscalarType newX) noexcept { Vector<2, TType>::m_data[0] = static_cast<TType>(newX);}

        /**
         * @brief Set member Y
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newY 
         * @return constexpr Vector2& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector2& setY(TscalarType newY) noexcept { Vector<2, TType>::m_data[1] = static_cast<TType>(newY);}
    
        #pragma region mutator

        #pragma endregion //!mutator
    
        #pragma region operator

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector2& 
         */

        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector2& operator=(const Vector<TLengthOther, TTypeOther>& other) noexcept
        {
            Vector<2, TType>::operator=(other);
            return *this;
        }

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector2& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector2& operator=(TscalarType scalar) noexcept
        {
            Vector<2, TType>::operator=(scalar);
            return *this;
        }

        #pragma endregion //!operator
    
        #pragma region convertor        
        #pragma endregion //!convertor
    
        #pragma region static attribut

        static constexpr inline Vector2 zero = Vector2(static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector2 one = Vector2(static_cast<TType>(1), static_cast<TType>(1));

        #pragma endregion //! static attribut
    };

    template <typename TType = float>
    using Vec2          = Vector2<TType>;

    using Vector2f      = Vector2<float>;
    using Vec2f         = Vector2f;
    using Vector2d      = Vector2<double>;
    using Vec2d         = Vector2d;
    using Vector2ld     = Vector2<long double>;
    using Vec2ld        = Vector2ld;

    using Vector2uc     = Vector2<unsigned char>;
    using Vec2uc        = Vector2uc;
    using Vector2c      = Vector2<char>;
    using Vec2c         = Vector2c;
    using Vector2ui     = Vector2<unsigned int>;
    using Vec2ui        = Vector2ui;
    using Vector2i      = Vector2<int>;
    using Vec2i         = Vector2i;
    using Vector2lui    = Vector2<long unsigned int>;
    using Vec2lui       = Vector2lui;
    using Vector2st     = Vector2<size_t>;
    using Vec2st        = Vector2st;
    using Vector2li     = Vector2<long int>;
    using Vec2li        = Vector2li;
    
    using Vector2b      = Vector2<bool>;
    using Vec2b         = Vector2b;

} /*namespace FoxMath::Vector*/
