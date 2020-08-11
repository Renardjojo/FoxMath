/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-11 - 10 h 14
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

#include "../Type/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>
#include "AngleType.hpp" // EAngleType

namespace FoxMath::Angle
{
    /*Use of IsArithmetic*/
    template <AngleType::EAngleType TAngleType, typename TType, Type::IsArithmetic<TType> = true>
    class Angle;

    template <AngleType::EAngleType TAngleType, typename TType>
    class Angle<TAngleType, TType>
    {
        private:
    
        protected:
    
        #pragma region attribut

        TType m_angle;

        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods

        [[nodiscard]] inline constexpr
        Angle<AngleType::Degres, TType> convertFromRadianToDegres() const noexcept;

        [[nodiscard]] inline constexpr
        Angle<AngleType::Radian, TType> convertFromDegresToRadian() const noexcept;

        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        Angle ()					            = default;
        Angle (const Angle& other)			    = default;
        Angle (Angle&& other)				    = default;
        ~Angle ()				                = default;
        Angle& operator=(Angle const& other)	= default;
        Angle& operator=(Angle && other)		= default;

        template<typename TTypeScalar, Type::IsArithmetic<TType> = true>
        inline constexpr
        Angle (TTypeScalar angle) noexcept;
    
        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        /**
         * @brief return degres angle
         * 
         * @return constexpr Angle<AngleType::Radian, TType> 
         */
        [[nodiscard]] inline constexpr
        Angle<AngleType::Degres, TType> toDegres() const noexcept;

        /**
         * @brief return radian angle
         * 
         * @return constexpr Angle<AngleType::Radian, TType> 
         */
        [[nodiscard]] inline constexpr
        Angle<AngleType::Radian, TType> toRadian() const noexcept;

        #pragma endregion //!methods
    
        #pragma region accessor

        [[nodiscard]] inline constexpr
        const TType& getAngle() const noexcept;

        [[nodiscard]] inline constexpr
        AngleType getType() const noexcept;

        #pragma endregion //!accessor
    
        #pragma region mutator

        template<typename TTypeScalar, Type::IsArithmetic<TType> = true>
        inline constexpr
        Angle<AngleType::Degres, TType>& setAngle(TTypeScalar newAngle) noexcept;

        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma endregion //!operator
    
        #pragma region convertor
        #pragma endregion //!convertor
    
    };

    #pragma region litteral conversion 
    
    /**
     * @brief litteral convertion for degres
     * @example 90.896_deg
     * 
     */
    [[nodiscard]] inline constexpr
    Angle<AngleType::Degres, float> operator"" _deg(long double angleDeg) noexcept;
    
    /**
     * @brief litteral convertion for degres
     * @example 90_deg
     * 
     */
    [[nodiscard]] inline constexpr
    Angle<AngleType::Degres, float> operator"" _deg(unsigned long long int      angleDeg) noexcept;

    /**
     * @brief litteral convertion for rad
     * @example 1.5874_rad
     * 
     */
    [[nodiscard]] inline constexpr
    Angle<AngleType::Radian, float> operator"" _rad(long double angleRad) noexcept;
    
    /**
     * @brief litteral convertion for rad
     * @example 3_rad
     * 
     */
    [[nodiscard]] inline constexpr
    Angle<AngleType::Radian, float> operator"" _rad(unsigned long long int      angleRad) noexcept;

    #pragma endregion //!litteral conversion 

    #include "Angle.inl"

    #pragma region stream operators

    /**
     * @brief output stream
     * 
     * @tparam TAngleType 
     * @tparam TType 
     * @param out 
     * @param angle 
     * @return constexpr std::ostream& 
     */
    template <AngleType::EAngleType TAngleType, typename TType>
    [[nodiscard]] inline constexpr
    std::ostream& 	operator<<		(std::ostream& out, const Angle<TAngleType, TType>& angle) noexcept;

    /**
     * @brief input streams
     * 
     * @tparam TAngleType 
     * @tparam TType 
     * @param in 
     * @param angle 
     * @return constexpr std::istream& 
     */
    template <AngleType::EAngleType TAngleType, typename TType>
    [[nodiscard]] inline constexpr
    std::istream& 	operator>>		(std::istream& in, const Angle<TAngleType, TType>& angle) noexcept;

    #pragma endregion //!stream operators


} /*namespace FoxMath::Angle*/
