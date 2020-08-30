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

#include "Types/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>
#include "Types/StrongType.hpp"
#include "Types/Operators/Bitwise.hpp"
#include "Types/Operators/Arithmetic.hpp"
#include "Types/Operators/Comparison.hpp"
#include "Angle/EAngleType.hpp"
#include "Types/Implicit.hpp"

namespace FoxMath::Angle
{
    template <EAngleType TAngleType>
    struct AnglePhantom {};

    /*Use of IsArithmetic*/
    template <EAngleType TAngleType, typename TType, Type::IsArithmetic<TType> = true>
    class Angle;

    template <EAngleType TAngleType, typename TType>
    class Angle<TAngleType, TType> 
    :   public Type::StrongType <TType, AnglePhantom<TAngleType>>,
        public Type::Operator::Arithmetic       <Angle<TAngleType, TType>>,
        public Type::Operator::Comparison       <Angle<TAngleType, TType>>,
        public Type::Operator::Bitwise          <Angle<TAngleType, TType>>
    {
        private:
    
        protected:

        using Base = Type::StrongType <TType, AnglePhantom<TAngleType>>;
    
        #pragma region attribut

        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods

        /**
         * @brief Force conversion from radian to degree
         * 
         * @tparam TOtherType 
         * @return constexpr Angle<EAngleType::Degree, TOtherType> 
         */
        template <typename TOtherType = TType>
        [[nodiscard]] inline constexpr
        Angle<EAngleType::Degree, TOtherType> convertFromRadianToDegree() const noexcept;

        /**
         * @brief Force conversion from degree to radian
         * 
         * @tparam TOtherType 
         * @return constexpr Angle<EAngleType::Radian, TOtherType> 
         */
        template <typename TOtherType = TType>
        [[nodiscard]] inline constexpr
        Angle<EAngleType::Radian, TOtherType> convertFromDegreeToRadian() const noexcept;

        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        Angle () noexcept				                = default;

        Angle (const Angle& other) noexcept				= default;

        Angle (Angle&& other) noexcept				    = default;

        ~Angle () noexcept				                = default;
        
        Angle& operator=(Angle const& other) noexcept	= default;

        Angle& operator=(Angle && other) noexcept       = default;

        template<typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
        explicit inline constexpr
        Angle (TTypeScalar angle) noexcept;
    
        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        /**
         * @brief return degree angle
         * 
         * @tparam TOtherType 
         * @return constexpr Angle<EAngleType::Degree, TOtherType> 
         */
        template <typename TOtherType = TType>
        [[nodiscard]] inline constexpr
        Angle<EAngleType::Degree, TOtherType> toDegree() const noexcept;

        /**
         * @brief return radian angle
         * 
         * @tparam TOtherType 
         * @return constexpr Angle<EAngleType::Radian, TOtherType> 
         */
        template <typename TOtherType = TType>
        [[nodiscard]] inline constexpr
        Angle<EAngleType::Radian, TOtherType> toRadian() const noexcept;

        #pragma endregion //!methods
    
        #pragma region accessor

        [[nodiscard]] inline constexpr
        const TType& getAngle() const noexcept;

        [[nodiscard]] inline constexpr
        EAngleType getType() const noexcept;

        #pragma endregion //!accessor
    
        #pragma region mutator

        template<typename TTypeScalar, Type::IsArithmetic<TType> = true>
        inline constexpr
        Angle<EAngleType::Degree, TType>& setAngle(TTypeScalar newAngle) noexcept;

        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma endregion //!operator
    
        #pragma region convertor

        /**
         * @brief Degree/Radian angle conversion and type conversion
         * @tparam TOtherType New precision
         */
        template <EAngleType TOtherAngleType, typename TOtherType>
        [[nodiscard]]
        implicit constexpr inline
        operator Angle<TOtherAngleType, TOtherType>() const noexcept;

        #pragma endregion //!convertor
    
    };

    #pragma region litteral conversion 
    
    /**
     * @brief litteral convertion for degree
     * @example 90.896_deg
     * 
     */
    [[nodiscard]] inline constexpr
    Angle<EAngleType::Degree, long double> operator"" _deg(long double angleDeg) noexcept;
    
    /**
     * @brief litteral convertion for degree
     * @example 90_deg
     * 
     */
    [[nodiscard]] inline constexpr
    Angle<EAngleType::Degree, unsigned long long int> operator"" _deg(unsigned long long int      angleDeg) noexcept;

    /**
     * @brief litteral convertion for rad
     * @example 1.5874_rad
     * 
     */
    [[nodiscard]] inline constexpr
    Angle<EAngleType::Radian, long double> operator"" _rad(long double angleRad) noexcept;
    
    /**
     * @brief litteral convertion for rad
     * @example 3_rad
     * 
     */
    [[nodiscard]] inline constexpr
    Angle<EAngleType::Radian, unsigned long long int> operator"" _rad(unsigned long long int      angleRad) noexcept;

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
    template <EAngleType TAngleType, typename TType>
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
    template <EAngleType TAngleType, typename TType>
    [[nodiscard]] inline constexpr
    std::istream& 	operator>>		(std::istream& in, const Angle<TAngleType, TType>& angle) noexcept;

    #pragma endregion //!stream operators

} /*namespace FoxMath::Angle*/
