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
    class Vector3 : public Vector<3, TType>
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
        Vector3 () noexcept			                        = default;

        constexpr inline  
        Vector3 (const Vector3& other) noexcept             = default;

        constexpr inline
        Vector3 (Vector3&& other) noexcept				    = default;

        inline
        ~Vector3 ()	noexcept			                    = default;

        constexpr inline
        Vector3& operator=(Vector3 const& other) noexcept   = default;

        constexpr inline
        Vector3& operator=(Vector3 && other) noexcept		= default;

        /**
         * @brief Construct a new vector with it's base type
         * 
         * @tparam TTlengthOther 
         * @param other 
         */
        template <size_t TTlengthOther>
        constexpr inline
        Vector3 (const Vector<TTlengthOther, TType>& other) noexcept
            : Vector<3, TType>(other) {}


        /**
         * @brief Variadic templated constructor to init member
         * @example `FoxMath::Vector::Vector<3, int> vec (1, 1, 3)` or `FoxMath::Vector::Vector<3, int> vec (1, 3)`
         * @tparam T 
         * @tparam Sfinae IsSame 
         */
        template<typename... T, Type::IsAllSame<TType, T...> = true,
        Type::IsLessThanOrEqualTo<sizeof...(T), 3> = true>
        explicit inline constexpr
        Vector3 (T... args) noexcept
            : Vector<3, TType>(args...) {}

        /**
         * @brief Variadic templated constructor to init member with vector and scalar
         * @example `FoxMath::Vector::Vector<10, int> vect(FoxMath::Vector::Vector<5, int>(), 3, 31)`
         * @tparam TLengthOther 
         * @tparam TScalarArgs
         */
        template<size_t TLengthOther, typename... TScalarArgs, 
        Type::IsAllSame<TType, TScalarArgs...> = true,
        Type::IsLessThanOrEqualTo<sizeof...(TScalarArgs) + TLengthOther, 3> = true,
        Type::IsLessThan<TLengthOther, 3> = true>
        explicit inline constexpr
        Vector3 (const Vector<TLengthOther, TType>& other, TScalarArgs... args) noexcept
            : Vector<3, TType>(other, args...) {}

        #pragma endregion //!constructor/destructor
    
        #pragma region methods
        #pragma endregion //!methods
    
        #pragma region accessor

        /**
         * @brief get member X
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getX() const noexcept { return Vector<3, TType>::m_data[0];}

        /**
         * @brief get member Y
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getY() const noexcept { return Vector<3, TType>::m_data[1];}

        /**
         * @brief get member Z
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getZ() const noexcept { return Vector<3, TType>::m_data[2];}

        #pragma endregion //!accessor

        /**
         * @brief Set member X
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newX 
         * @return constexpr Vector3& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector3& setX(TscalarType newX) noexcept { Vector<3, TType>::m_data[0] = static_cast<TType>(newX);}

        /**
         * @brief Set member Y
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newY 
         * @return constexpr Vector3& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector3& setY(TscalarType newY) noexcept { Vector<3, TType>::m_data[1] = static_cast<TType>(newY);}

        /**
         * @brief Set member Z
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newZ 
         * @return constexpr Vector3& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector3& setZ(TscalarType newZ) noexcept { Vector<3, TType>::m_data[2] = static_cast<TType>(newZ);}
    
        #pragma region mutator
    
        #pragma region operator

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector3& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector3& operator=(const Vector<TLengthOther, TTypeOther>& other) noexcept
        {
            Vector<3, TType>::operator=(other);
            return *this;
        }

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector3& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector3& operator=(TscalarType scalar) noexcept
        {
            Vector<3, TType>::operator=(scalar);
            return *this;
        }

        #pragma endregion //!operator
    
        #pragma region convertor

        #pragma endregion //!convertor
    
        #pragma region static attribut

        static constexpr inline Vector3 zero      = Vector3(static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector3 one       = Vector3(static_cast<TType>(1), static_cast<TType>(1), static_cast<TType>(1));
		static constexpr inline Vector3 up        = Vector3(static_cast<TType>(0), static_cast<TType>(1), static_cast<TType>(0));
		static constexpr inline Vector3 down      = Vector3(static_cast<TType>(0), static_cast<TType>(-1), static_cast<TType>(0));
		static constexpr inline Vector3 right     = Vector3(static_cast<TType>(1), static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector3 left      = Vector3(static_cast<TType>(-1), static_cast<TType>(0), static_cast<TType>(0));
		static constexpr inline Vector3 forward   = Vector3(static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(1));
		static constexpr inline Vector3 backward  = Vector3(static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(-1));

        #pragma endregion //! static attribut
    };

    template <typename TType = float>
    using Vec3          = Vector3<TType>;

    using Vector3f      = Vector3<float>;
    using Vec3f         = Vector3f;
    using Vector3d      = Vector3<double>;
    using Vec3d         = Vector3d;
    using Vector3ld     = Vector3<long double>;
    using Vec3ld        = Vector3ld;

    using Vector3uc     = Vector3<unsigned char>;
    using Vec3uc        = Vector3uc;
    using Vector3c      = Vector3<char>;
    using Vec3c         = Vector3c;
    using Vector3ui     = Vector3<unsigned int>;
    using Vec3ui        = Vector3ui;
    using Vector3i      = Vector3<int>;
    using Vec3i         = Vector3i;
    using Vector3lui    = Vector3<long unsigned int>;
    using Vec3lui       = Vector3lui;
    using Vector3st     = Vector3<size_t>;
    using Vec3st        = Vector3st;
    using Vector3li     = Vector3<long int>;
    using Vec3li        = Vector3li;
    
    using Vector3b      = Vector3<bool>;
    using Vec3b         = Vector3b;

} /*namespace FoxMath::Vector*/
