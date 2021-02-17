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
#include <limits>
#include <algorithm> //std::clamp
#include "Types/SFINAEShorthand.hpp" //IsArithmetic<TType>
#include "Vector/Vector3.hpp" //Vector3<TType>
#include "Matrix/Matrix3.hpp" //Matrix3
#include "Numeric/Limits.hpp" //Vector3<TType>
#include "Angle/Angle.hpp" //Angle<EAngleType::Radian, TType>

namespace FoxMath
{
    /*Use of IsArithmetic*/
    template <typename TType = float, IsArithmetic<TType> = true>
    class Quaternion;

    template <typename TType>
    class Quaternion<TType>
    {
        private:
    
        public:
            
        #pragma region attribut

        union
        {
            struct
            {
                TType m_x;
                TType m_y;
                TType m_z;
                TType m_w;
            };

            Vector3<TType>  m_xyz;
            std::array<TType, 4>    m_data {};
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

        /**
         * @brief Create quaternion based on axis and angle
         * 
         */
        explicit inline constexpr
        Quaternion (Vector3<TType> axis, Angle<EAngleType::Radian, TType> angle = Angle<EAngleType::Radian, TType>(0)) noexcept;
    
        /**
         * @brief Create quaternion based on it's paramter
         * 
         */
        explicit inline constexpr
        Quaternion (TType x, TType y, TType z, TType w) noexcept;

        #pragma endregion //!constructor/destructor
    
        #pragma region methods
        
        /**
         * @brief Get the Squared Magnitude of the quaternion
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getSquaredMagnitude() const noexcept;

        /**
         * @brief Get the Magnitude of the quation
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getMagnitude() const noexcept;

        /**
         * @brief Check if quaternion squared magnitude is less than epsilon. Quaternion can express rotaiton only if it is unit
         * 
         * @param epsilon 
         * @return true 
         * @return false 
         */
        [[nodiscard]] inline constexpr
        bool isRotation(TType epsilon = std::numeric_limits<TType>::epsilon()) const noexcept;

        /**
         * @brief Normalize the quaternion it self
         * 
         * @return constexpr Quaternion& 
         */
        inline constexpr
        Quaternion& normalize() noexcept;

        /**
         * @brief get the normalize quaternion
         * 
         * @return constexpr Quaternion& 
         */
        [[nodiscard]] inline constexpr
        Quaternion getNormalize() const noexcept;

        /**
         * @brief Perform conjugate of the quaternion in self : q4 - iq1 - jq2 - kq3
         * 
         * @return constexpr Quaternion& 
         */
        inline constexpr
        Quaternion& conjugate() noexcept;

        /**
         * @brief get the perform conjugate of the quaternion : q4 - iq1 - jq2 - kq3
         * 
         * @return constexpr Quaternion& 
         */
        [[nodiscard]] inline constexpr
        Quaternion getConjugate() const noexcept;

        /**
         * @brief Perform the inverse of the quaternion in self : q^-1. If is uni
         * 
         * @return constexpr Quaternion& 
         */
        inline constexpr
        Quaternion& inverse() noexcept;

        /**
         * @brief Perform the inverse of the quaternion : q^-1. If is uni
         * 
         * @return constexpr Quaternion& 
         */
        [[nodiscard]] inline constexpr
        Quaternion getInverse() const noexcept;


        /**
         * @brief Compute the angle of the quaternion
         * 
         * @return constexpr Angle<EAngleType::Radian, TType> 
         */
        [[nodiscard]] inline constexpr
        Angle<EAngleType::Radian, TType> getAngle() const noexcept;

        /**
         * @brief Compute the axis of the quaternion
         * 
         * @return constexpr Vector3<TType> 
         */
        [[nodiscard]] inline constexpr
        Vector3<TType> getAxis() const noexcept;

        /**
         * @brief Get the Rotation Matrix of the quaternion
         * 
         * @tparam TMatrixConvention 
         * @return constexpr Matrix3<TType, TMatrixConvention> 
         */
        template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
        [[nodiscard]] inline constexpr
        Matrix3<TType, TMatrixConvention> getRotationMatrix() const noexcept;

        /**
         * @brief Perform dot product between 2 quaternions
         * 
         * @param other 
         * @return constexpr Vector3<TType> 
         */
        [[nodiscard]] inline constexpr
        TType dot(const Quaternion<TType>& other) const noexcept;

        /**
         * @brief Rotate vector with current quaternion. Is optimized only for 1 vector, else use RotateVectos that use matricial forme.
         *          Use Rodrigues formula and not q * v * q^-1 for optimization raison.
         * 
         * @param vec
         */
        template <typename TTypeVector>
        inline constexpr
        void rotateVector(Vector3<TTypeVector>& vec) const noexcept;

        /**
         * @brief Perform the rotation of the vector with the formula : (q1 * q2) * v * (q1 * q2)^-1.
         *        Rotation is firstly on q2 and then on q1
         * 
         * @param vec
         */
        template <typename TTypeVector>
        inline constexpr
        void globalRotateVector(const Quaternion<TType>& otherQuat, Vector3<TTypeVector>& vec) const noexcept;

        /**
         * @brief Perform the rotation of the vector with the formula : (q2 * q1) * v * (q2 * q1)^-1.
         *        Rotation is firstly on q1 and then on q2
         * 
         * @param vec
         */
        template <typename TTypeVector>
        inline constexpr
        void localRotateVector(const Quaternion<TType>& otherQuat, Vector3<TTypeVector>& vec) const noexcept;

        /**
         * @brief Get the Global Smallest Diffence With Other quaternion. Use formula : q2 * q1^-1
         * 
         * @param otherQuat 
         * @return constexpr Quaternion<TType> 
         */
        [[nodiscard]] inline constexpr
        Quaternion<TType> getGlobalSmallestDiffenceWithOther(const Quaternion<TType>& otherQuat) const noexcept;

        /**
         * @brief Get the Global Smallest Diffence With Other quaternion. Use formula : q1^-1 * q2
         * 
         * @param otherQuat 
         * @return constexpr Quaternion<TType> 
         */
        [[nodiscard]] inline constexpr
        Quaternion<TType> getLocalSmallestDiffenceWithOther(const Quaternion<TType>& otherQuat) const noexcept;

        /**
         * @brief Perform a cyllindric interpolation rotation between start and end.
         *        cyllindric interpolation is better than lerp for exigute rotaion but more expensive.
         *        Furthermore cyllindric interpolation maintain constante angular speed
         * 
         * @tparam TShortestPath : true if the ratio must use the shotedt path. Else more optimized but can go with the largest path to goal 
         * @tparam TClampedRatio : true if the ratio must be clamped between 0 and 1. Else more optimized but can create erronate rotation if ratio is incorrect
         * @param startQuat 
         * @param endQuat 
         * @param t 
         */
        template <bool TShortestPath = true, bool TClampedRatio = true>
        inline constexpr
        void sLerp(const Quaternion<TType>& startQuat, const Quaternion<TType>& endQuat, TType t) noexcept;

        /**
         * @brief Perform a linear interpolation rotation between start and end. Angulare speed and rotation is not safe
         * 
         * @tparam TShortestPath : true if the ratio must use the shotedt path. Else more optimized but can go with the largest path to goal 
         * @tparam TClampedRatio : true if the ratio must be clamped between 0 and 1. Else more optimized but can create erronate rotation if ratio is incorrect
         * @param startQuat 
         * @param endQuat 
         * @param t 
         */
        template <bool TShortestPath = true, bool TClampedRatio = true>
        inline constexpr
        void lerp(const Quaternion<TType>& startQuat, const Quaternion<TType>& endQuat, TType t) noexcept;

        /**
         * @brief Perform a linear interpolation rotation between start and end qnd normalize the resulte. Angulare speed is not safe
         * 
         * @tparam TShortestPath : true if the ratio must use the shotedt path. Else more optimized but can go with the largest path to goal 
         * @tparam TClampedRatio : true if the ratio must be clamped between 0 and 1. Else more optimized but can create erronate rotation if ratio is incorrect
         * @param startQuat 
         * @param endQuat 
         * @param t 
         */
        template <bool TShortestPath = true, bool TClampedRatio = true>
        inline constexpr
        void nLerp(const Quaternion<TType>& startQuat, const Quaternion<TType>& endQuat, TType t) noexcept;


        #pragma endregion //!methods
    
        #pragma region static methods

        /**
         * @brief Rotate vector with current quaternion. Is optimized only for 1 vector, else use RotateVectos that use matricial forme
         * 
         * @param vec 
         * @param unitAxis 
         * @param angle 
         */
        template <typename TTypeVector, typename TTypeAxis>
        static inline constexpr
        void rotateVector(Vector3<TTypeVector>& vec, const Vector3<TTypeAxis>& unitAxis, Angle<EAngleType::Radian, TType> angle) noexcept
        {
            //Rodrigues formula with quaternion is better than quat * vec * quat.getInverse()
            const TType cosAngle = std::cos(static_cast<TType>(angle));
            vec = cosAngle * vec + (static_cast<TType>(1) - cosAngle) * vec.dot(unitAxis) * unitAxis + std::sin(static_cast<TType>(angle)) * unitAxis.getCross(vec);
        }

        template <typename TTypeVector, typename TTypeAxis>
        static inline constexpr
        void rotateVector2(Vector3<TTypeVector>& vec, const Vector3<TTypeAxis>& unitAxis, Angle<EAngleType::Radian, TType> angle) noexcept
        {
            Quaternion<TType> quat (unitAxis, angle);
            quat = quat * vec * quat.getInverse();
            vec = quat.getXYZ();
        }

        /**
         * @brief Get the Global Smallest Diffence With Other quaternion. Use formula : q2 * q1^-1
         * 
         * @param otherQuat 
         * @return constexpr Quaternion<TType> 
         */
        [[nodiscard]] inline constexpr
        Quaternion<TType> getGlobalSmallestDiffenceWithOther(const Quaternion<TType>& q1, const Quaternion<TType>& q2) noexcept
        {
            return q1.getGlobalSmallestDiffenceWithOther(q2);
        }

        /**
         * @brief Get the Global Smallest Diffence With Other quaternion. Use formula : q1^-1 * q2
         * 
         * @param otherQuat 
         * @return constexpr Quaternion<TType> 
         */
        [[nodiscard]] inline constexpr
        Quaternion<TType> getLocalSmallestDiffenceWithOther(const Quaternion<TType>& q1, const Quaternion<TType>& q2) noexcept
        {
            return q1.getLocalSmallestDiffenceWithOther(q2);
        }

        /**
         * @brief Perform the rotation of the vector with the formula : (q1 * q2) * v * (q1 * q2)^-1.
         *        Rotation is firstly on q2 and then on q1
         * 
         * @param vec
         */
        template <typename TTypeVector>
        inline constexpr
        void globalRotateVector(const Quaternion<TType>& q1, const Quaternion<TType>& q2, Vector3<TTypeVector>& vec) noexcept
        {
            q1.GlobalRotateVector(q2, vec);
        }

        /**
         * @brief Perform the rotation of the vector with the formula : (q2 * q1) * v * (q2 * q1)^-1.
         *        Rotation is firstly on q1 and then on q2
         * 
         * @param vec
         */
        template <typename TTypeVector>
        inline constexpr
        void localRotateVector(const Quaternion<TType>& q1, const Quaternion<TType>& q2, Vector3<TTypeVector>& vec) noexcept
        {
            q1.LocalRotateVector(q2, vec);
        }

        #pragma endregion //!static methods

        #pragma region accessor

        [[nodiscard]] inline constexpr
        TType getX() const noexcept { return m_x; }

        [[nodiscard]] inline constexpr
        TType getY() const noexcept { return m_y; }

        [[nodiscard]] inline constexpr
        TType getZ() const noexcept { return m_z; }

        [[nodiscard]] inline constexpr
        TType getW() const noexcept { return m_w; }

        [[nodiscard]] inline constexpr
        Vector3<TType> getXYZ() const noexcept { return m_xyz; }

        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator

        #pragma region assignment operators

        /**
         * @brief addition assignment 
         * 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeOther>
		inline constexpr
		Quaternion& operator+=(const Quaternion<TTypeOther>& other) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeOther>
		inline constexpr
		Quaternion& operator-=(const Quaternion<TTypeOther>& other) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeOther>
		inline constexpr
		Quaternion& operator*=(const Quaternion<TTypeOther>& other) noexcept;

        /**
         * @brief multiplication with a scalar number
         * 
         * @tparam TTypeScalar 
         * @param scalar 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
		inline constexpr
		Quaternion& operator*=(TTypeScalar scalar) noexcept;

        /**
         * @brief multiplication with a vector
         * 
         * @tparam TTypeVector 
         * @param vec 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeVector, IsArithmetic<TTypeVector> = true>
		inline constexpr
		Quaternion& operator*=(Vector3<TTypeVector> vec) noexcept;

        /**
         * @brief division with a scalar number
         * 
         * @tparam TTypeScalar 
         * @param scalar 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
		inline constexpr
		Quaternion& operator/=(TTypeScalar scalar) noexcept;

        #pragma endregion //!assignment operators
        #pragma endregion //!operator
    
        #pragma region convertor
        #pragma endregion //!convertor    

        #pragma region static attribut

        static constexpr inline Quaternion identity  = Quaternion(static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(0), static_cast<TType>(1));

        #pragma endregion //! static attribut
    };

    #pragma region arithmetic operators

    /**
     * @brief unary plus 
     * 
     * @tparam TType 
     * @param quat 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator+(const Quaternion<TType>& quat) noexcept;

    /**
     * @brief unary minus 
     * 
     * @tparam TType 
     * @param quat 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator-(const Quaternion<TType>& quat) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeOther>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator+(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeOther>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator-(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeOther>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator*(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept;

    /**
     * @brief multiplication of quaternion with a scale
     * 
     * @tparam TType 
     * @tparam TTypeScalar 
     * @param quat 
     * @param scalar 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator*(Quaternion<TType> quat, TTypeScalar scalar) noexcept;

    /**
     * @brief multiplication of quaternion with a vector
     * 
     * @tparam TType 
     * @tparam TTypeVector 
     * @param quat 
     * @param vec 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeVector, IsArithmetic<TTypeVector> = true>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator*(Quaternion<TType> quat, const Vector3<TTypeVector>& vec) noexcept;

    /**
     * @brief division of quaternion with a scale
     * 
     * @tparam TType 
     * @tparam TTypeScalar 
     * @param quat 
     * @param scalar 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator/(Quaternion<TType> quat, TTypeScalar scalar) noexcept;

    /**
     * @brief multiplication of quaternion with a scale
     * 
     * @tparam TType 
     * @tparam TTypeScalar 
     * @param scalar 
     * @param quat 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator*(TTypeScalar scalar, Quaternion<TType> quat) noexcept;


    #pragma endregion //!arithmetic operators

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

    #pragma endregion //!stream operators

    #include "Quaternion.inl"

} /*namespace FoxMath*/