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

#include <array>
#include "Vector/Vector3.hpp" //Vector::Vector3<TType>
#include "Angle/Angle.hpp" //Angle<Angle::EAngleType::Radian, TType>

namespace FoxMath::Quaternion
{
    template <typename TType = float>
    class Quaternion
    {
        private:
    
        protected:
            
        #pragma region attribut

        union
        {
            struct
            {
                
                Angle::Angle<Angle::EAngleType::Radian, TType> m_angle;
                Vector::Vector3<TType>           m_axis;
            };
            
            struct
            {
                TType m_x;
                TType m_y;
                TType m_z;
                TType m_w;
            };
            

            std::array<TType, 4> m_data {};
        };
        


        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods

        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        Quaternion () noexcept				                        = default;

        Quaternion (const Quaternion& other) noexcept				= default;

        Quaternion (Quaternion&& other) noexcept				    = default;

        ~Quaternion () noexcept				                        = default;
        
        Quaternion& operator=(Quaternion const& other) noexcept	    = default;

        Quaternion& operator=(Quaternion && other) noexcept         = default;

        explicit inline constexpr
        Quaternion (const Vector::Vector3<TType>& axis, Angle::Angle<Angle::EAngleType::Radian, TType> angle) noexcept;
    
        #pragma endregion //!constructor/destructor
    
        #pragma region methods
        #pragma endregion //!methods
    
        #pragma region accessor

        [[nodiscard]] inline constexpr
        Angle::Angle<Angle::EAngleType::Radian, TType> getAngle() const noexcept { return m_angle;}

        [[nodiscard]] inline constexpr
        const Vector::Vector3<TType>& getAxis() const noexcept { return m_axis;}

        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma endregion //!operator
    
        #pragma region convertor
        #pragma endregion //!convertor
    
    };

    #pragma region litteral conversion 
    #pragma endregion //!litteral conversion 

    #include "Quaternion.inl"

    #pragma region stream operators

    /**
     * @brief output stream
     * 
     * @tparam TType 
     * @param out 
     * @param angle 
     * @return constexpr std::ostream& 
     */
    template <typename TType>
    [[nodiscard]] inline constexpr
    std::ostream& 	operator<<		(std::ostream& out, const Quaternion<TType>& quaternion) noexcept;

    /**
     * @brief input streams
     * 
     * @tparam TType 
     * @param in 
     * @param angle 
     * @return constexpr std::istream& 
     */
    template <typename TType>
    [[nodiscard]] inline constexpr
    std::istream& 	operator>>		(std::istream& in, const Quaternion<TType>& quaternion) noexcept;

    #pragma endregion //!stream operators

} /*namespace FoxMath::Quaternion*/
