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
#include "Macro/CrossInheritanceCompatibility.hpp"

namespace FoxMath::Vector
{
    template <typename TType = float>
    class Vector4 : public GenericVector<4, TType>
    {
        private:
    
        using Parent = GenericVector<4, TType>;

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
        Vector4 () noexcept			                        = default;

        constexpr inline  
        Vector4 (const Vector4& other) noexcept             = default;

        constexpr inline
        Vector4 (Vector4&& other) noexcept				    = default;

        inline
        ~Vector4 ()	noexcept			                    = default;

        constexpr inline
        Vector4& operator=(Vector4 const& other) noexcept   = default;

        constexpr inline
        Vector4& operator=(Vector4 && other) noexcept		= default;

        DECLARE_CROSS_INHERITANCE_COMPATIBILTY(Vector4, Parent, GenericVector)

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
        TType getX() const noexcept { return Parent::m_data[0];}

        /**
         * @brief get member Y
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getY() const noexcept { return Parent::m_data[1];}

        /**
         * @brief get member Z
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getZ() const noexcept { return Parent::m_data[2];}

        /**
         * @brief get member X
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getW() const noexcept { return Parent::m_data[3];}

        #pragma endregion //!accessor
    
        #pragma region mutator

        /**
         * @brief Set member X
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newX 
         * @return constexpr Vector4& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector4& setX(TscalarType newX) noexcept { Parent::m_data[0] = static_cast<TType>(newX);}

        /**
         * @brief Set member Y
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newY 
         * @return constexpr Vector4& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector4& setY(TscalarType newY) noexcept { Parent::m_data[1] = static_cast<TType>(newY);}

        /**
         * @brief Set member Z
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newZ 
         * @return constexpr Vector4& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector4& setZ(TscalarType newZ) noexcept { Parent::m_data[2] = static_cast<TType>(newZ);}

        /**
         * @brief Set member W
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param newW 
         * @return constexpr Vector4& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr
        Vector4& setW(TscalarType newW) noexcept { Parent::m_data[3] = static_cast<TType>(newW);}

        #pragma endregion //!inheritance compatibility
    
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

    template <typename TType = float>
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
