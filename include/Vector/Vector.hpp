/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-05 - 10 h 28
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

#include <array> //std::array
#include <stddef.h> //sizt_t
#include <iostream> //ostream, istream
#include <cassert> //assert
#include <cstring> //memset
#include <cmath> //sqrt

#include "../Type/TypeTraitsAlias.hpp" //Type::IsArithmetic<TType>, Type::IsSame, Type::Pack
#include "../Numeric/Limits.hpp" //isSame

namespace FoxMath::Vector
{
    /*Use of IsArithmetic*/
    template <size_t TLength, typename TType = float, Type::IsArithmetic<TType> = true>
    class Vector;

    /*Specilisation of Vector class*/
    template <size_t TLength, typename TType>
    class Vector<TLength, TType>
    {
        private:
    
        protected:
    
        #pragma region attribut

        std::array<TType, TLength> m_data {};

        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods
        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        /**
         * @brief Default constructor, doesn't init the vector's member at zero to optimize class
         * 
         */
        constexpr inline 
        Vector () noexcept                          = default;

        constexpr inline
        Vector (const Vector& other)			    = default;
        
        constexpr inline 
        Vector (Vector&& other)				        = default;
        
        ~Vector ()				                    = default;
        
        constexpr inline 
        Vector& operator=(Vector const& other)		= default;
        
        constexpr inline 
        Vector& operator=(Vector && other)			= default;
    
        /**
         * @brief Variadic templated constructor to init member
         * @example `FoxMath::Vector::Vector<2, int> vec (1, 1, 3)` or `FoxMath::Vector::Vector<2, int> vec (1, 2)`
         * @tparam T 
         * @tparam Sfinae IsSame 
         */
        template<typename... T, Type::IsSame<Type::Pack<TType, T...>, Type::Pack<T..., TType>> = true>
        explicit inline constexpr
        Vector (T... args) noexcept;

        /**
         * @brief Variadic templated constructor to init member with vector and scalar
         * @example `FoxMath::Vector::Vector<10, int> vect(FoxMath::Vector::Vector<5, int>(), 22, 31)`
         * @tparam TLengthOther 
         * @tparam TScalarArgs
         */
        template<size_t TLengthOther, typename... TScalarArgs, 
        Type::IsSame<Type::Pack<TType, TScalarArgs...>, Type::Pack<TScalarArgs..., TType>> = true,
        Type::IsLessThanOrEqualTo<sizeof...(TScalarArgs) + TLengthOther, TLength> = true,
        Type::IsLessThan<TLengthOther, TLength> = true>
        explicit inline constexpr
        Vector (const Vector<TLengthOther, TType>& other, TScalarArgs... args) noexcept;

        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        /**
         * @brief Fill vector's member with scalar value
         * 
         */
        inline constexpr  
        void fill (const TType scalar) noexcept;

        /**
         * @brief Return squartLength of vector. More optimize to compare distance than length
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType squartLength () const noexcept;

        /**
         * @brief return magnitude of the vector 
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType length () const noexcept;
        
        /**
         * @brief Normalize the vector. If the vector is null (all components are set to 0), nothing is done.
         * 
         * @return constexpr Vector& 
         */
        inline constexpr
		Vector& 	    normalize	        () noexcept;

        /**
         * @brief  Returns the normalized vector. If the vector is null (all components are set to 0), then vector zero is returned.
         * 
         * @return constexpr const Vector& 
         */
        [[nodiscard]] inline constexpr
        Vector      getNormalized		() const noexcept;

        /**
         * @brief Clamp the vector's length to max value
         * 
         * @param maxLength 
         * @return constexpr Vector& 
         */
        inline constexpr
        Vector&         clampLength         (TType maxLength) noexcept;

        /**
         * @brief Get the Clamped Length object
         * 
         * @param maxLength 
         * @return constexpr Vector 
         */
        [[nodiscard]] inline constexpr
        Vector         getClampedLength         (TType maxLength) const noexcept;

        /**
         * @brief Perform dot product with another vector
         * 
         * @param other 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType           dot		            (const Vector& other) const noexcept;

        /**
         * @brief perform cross product with another vector
         * 
         * @param other 
         * @return constexpr Vector& 
         */
        inline constexpr
        Vector&         cross	            (const Vector& other) noexcept;

        /**
         * @brief Get the Cross object
         * 
         * @param other 
         * @return constexpr Vector 
         */
        [[nodiscard]] inline constexpr
        Vector         getCross	            (const Vector& other) const noexcept;

        /**
         * @brief Performs a linear interpolation between 2 vectors of the same type.
         * 
         * @param other 
         * @param t 
         * @return constexpr Vector& 
         */
        inline constexpr
        Vector& 	    lerp		        (const Vector& other, TType t) noexcept;

        [[nodiscard]] inline constexpr
        Vector 	        getLerp		        (const Vector& other, TType t) const noexcept;

        /**
         * @brief Performs a reflection with a normal vector
         * 
         * @param normalNormalized : Normal must be normalized
         * @return constexpr Vector& 
         */
        inline constexpr
        Vector&         reflect		        (const Vector& normalNormalized) noexcept;

        /**
         * @brief Get the Reflection object
         * 
         * @param normalNormalized 
         * @return constexpr Vector 
         */
        [[nodiscard]] inline constexpr
        Vector 	        getReflection		 (const Vector& normalNormalized) const noexcept;

        /**
         * @brief Set the magnitude of the current vector
         * 
         * @param newLength 
         * @return constexpr Vector& 
         */
        inline constexpr
        Vector& 	    setLength		     (TType newLength) noexcept;

        /**
         * @brief return true if vector is colineaire this other vector. Comput cross product. If cross product is near of zero, vectors is colinear
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        [[nodiscard]] inline constexpr
		bool 	isColinearTo	(const Vector& other) noexcept;

        /**
         * @brief return true if vector is perpendicular this other vector. Comput dot product. If dot product is near of zero, vectors is colinear
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        [[nodiscard]] inline constexpr
		bool 	isPerpendicularTo	(const Vector& other) noexcept;

        /**
         * @brief Area correspond to the ares of parralelogram formed by the two vectors.
         * 
         * @param other 
         * @return TType 
         */
        [[nodiscard]] inline constexpr
		TType getParallelogramArea		(const Vector& other) const noexcept;

        /**
         * @brief Comput aera of triangle in function of 3 points
         * 
         * @param other 
         * @return TType 
         */
        [[nodiscard]] inline constexpr
		TType getTriangleArea		(const Vector& other) const noexcept;

        /**
         * @brief rotate vector around another unit vector. This function assert if axis is not unit
         * 
         * @param unitAxis 
         * @param angleRad 
         */
        inline constexpr
		Vector& rotateAroundAxis (const Vector& unitAxis, TType angleRad) noexcept;

        /**
         * @brief Get the Rotation Around Axis object
         * 
         * @param unitAxis 
         * @param angleRad 
         * @return Vector 
         */
        [[nodiscard]] inline constexpr
		Vector getRotationAroundAxis (const Vector& unitAxis, TType angleRad) const noexcept;

        /**
         * @brief Get the projection with another vector
         * 
         * @param other 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getScalarProjectionWith(const Vector& other) const noexcept;

        /**
         * @brief Get the rejection with another vector
         * 
         * @param other 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getScalarRejectionWith(const Vector& other) const noexcept;

        /**
         * @brief Get the Vector projection with another
         * 
         * @param other 
         * @return constexpr Vector 
         */
        [[nodiscard]] inline constexpr
		Vector getVectorProjectionWith(const Vector& other) const noexcept;

        /**
         * @brief Get the Vector rejection with another
         * 
         * @param other 
         * @return constexpr Vector 
         */
        [[nodiscard]] inline constexpr
		Vector getVectorRejectionWith(const Vector& other) const noexcept;

        #pragma endregion //!methods
    
        #pragma region static methods

        /**
         * @brief perform dot product with both vector
         * 
         * @param lhs 
         * @param rhs 
         * @return constexpr TType 
         */
        [[nodiscard]] static inline constexpr
        TType           dot		            (const Vector& lhs, const Vector& rhs) noexcept
        {
            return lhs.dot(rhs); 
        }

        /**
         * @brief perform cross product with both vector
         * 
         * @param lhs 
         * @param rhs 
         * @return constexpr Vector
         */
        [[nodiscard]] static inline constexpr
        Vector         cross	            (const Vector& lhs, const Vector& rhs) noexcept
        {
            return lhs.getCross(rhs); 
        }


        /**
         * @brief 
         * 
         * @param lhs 
         * @param rhs : normalize normal
         * @return constexpr Vector 
         */
        [[nodiscard]] static inline constexpr
        Vector         reflect	            (const Vector& vec, const Vector& normalizedNormal) noexcept
        {
            return vec.getReflection(normalizedNormal);
        }


        /**
         * @brief 
         * 
         * @param lhs 
         * @param rhs 
         * @return constexpr Vector 
         */
        [[nodiscard]] static inline constexpr
        Vector         lerp	            (const Vector& vecStart, const Vector& vecEnd, TType t) noexcept
        {
            return vecStart.getLerp(vecEnd, t);
        }

        /**
         * @brief Comput aera of parallelogram in function of 3 points
         * 
         * @param pt1 
         * @param pt2 
         * @param pt3 
         * @return TType 
         */
        [[nodiscard]] static inline constexpr
		TType parallelogramArea		(const Vector& pt1, const Vector& pt2, const Vector& pt3) noexcept
        {
            return (pt2 - pt1).getParallelogramArea(pt3 - pt1);
        }

        /**
         * @brief Comput aera of triangle in function of 3 points
         * 
         * @param pt1 
         * @param pt2 
         * @param pt3 
         * @return TType 
         */
        [[nodiscard]] static inline constexpr
		TType triangleArea		(const Vector& pt1, const Vector& pt2, const Vector& pt3) noexcept
        {
            return (pt2 - pt1).getTriangleArea(pt3 - pt1);
        }

        #pragma endregion //!static methods

        #pragma region accessor
        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma region member access operators

        [[nodiscard]] inline constexpr
		TType& 	    operator[]	(size_t index) noexcept;

        [[nodiscard]] inline constexpr
		const TType& 	    operator[]	(size_t index) const noexcept;

        #pragma endregion //!member access operators
        #pragma region  assignment operators

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator+=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator+=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator-=(TscalarType scalar) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator-=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator*=(TscalarType scalar) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator*=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator/=(TscalarType scalar) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator/=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator%=(TscalarType scalar) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator%=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator&=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator&=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator|=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator|=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator^=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator^=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator<<=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator<<=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr Vector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		Vector& operator>>=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr Vector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		Vector& operator>>=(const Vector<TLengthOther, TTypeOther>& other) noexcept;

        #pragma endregion //!region assignment operators
        #pragma region increment decrement operators

        /**
         * @brief  pre-increment operator
         * 
         * @return constexpr Vector& 
         */
        inline constexpr
		Vector& 	operator++	() noexcept;

        /**
         * @brief pre-decrement operator
         * 
         * @return constexpr Vector& 
         */
        inline constexpr
		Vector& 	operator--	() noexcept;
        
        /**
         * @brief post-increment  operator
         * 
         * @return constexpr Vector 
         */
        inline constexpr
		Vector 	    operator++	(int) noexcept;

        /**
         * @brief post-decrement operator
         * 
         * @return constexpr Vector 
         */
        inline constexpr
		Vector 	    operator--	(int) noexcept;

        #pragma endregion //!increment decrement operators
        #pragma region convertor

        /**
         * @brief Converte vector to another vector type
         * @note use static_cast<> to call this function
         * @example `FoxMath::Vector::Vector<2, float> rhs = static_cast<FoxMath::Vector::Vector<2, float>>(vec)`
         * @tparam TLengthOther 
         * @tparam TTypeOther 
         * @return Vector<TLengthOther, TTypeOther> 
         */
        template <size_t TLengthOther, typename TTypeOther>
        constexpr inline explicit 
        operator Vector<TLengthOther, TTypeOther>() const noexcept;

        #pragma endregion //!convertor
    };

    #pragma region arithmetic operators

    /**
     * @brief unary plus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator+(Vector<TLength, TType> const& vec) noexcept;

    /**
     * @brief unary minus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator-(Vector<TLength, TType> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator+(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator+(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator+(Vector<TLength, TType> lhs, Vector<TLength, TType> rhs) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator-(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator-(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator-(Vector<TLength, TType> lhs, Vector<TLength, TType>& rhs) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator*(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator*(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator*(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator/(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator/(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator/(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator%(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator%(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator%(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator&(Vector<TLength, TType> lhs, TType scalar) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator&(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise AND 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator&(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator|(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief bitwise OR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator|(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator|(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator^(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator^(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator^(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator<<(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator<<(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator<<(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief bitwise right shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator>>(Vector<TLength, TType> vec, TType scalar) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator>>(TType scalar, Vector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator>>(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief bitwise NOT
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr Vector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator~(Vector<TLength, TType> vec) noexcept;

    #pragma endregion //!logical operators
    #pragma region logical operators
    
    /**
     * @brief negation
     * 
     * @tparam TLength 
     * @param vec 
     * @return constexpr Vector<TLength, bool> 
     */
    template <size_t TLength>
	[[nodiscard]] inline constexpr
    Vector<TLength, bool> operator!(Vector<TLength, bool> vec) noexcept;
	
    /**
     * @brief AND
     * 
     * @tparam TLength 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, bool> 
     */
    template <size_t TLength>
	[[nodiscard]] inline constexpr
    Vector<TLength, bool> operator&&(Vector<TLength, bool> lhs, Vector<TLength, bool> const& rhs) noexcept;

    /**
     * @brief inclusive OR
     * 
     * @tparam TLength 
     * @param lhs 
     * @param rhs 
     * @return constexpr Vector<TLength, bool> 
     */
	template <size_t TLength>
	[[nodiscard]] inline constexpr
    Vector<TLength, bool> operator||(Vector<TLength, bool> lhs, Vector<TLength, bool> const& rhs) noexcept;
    
    #pragma endregion //!logical operators
    #pragma region comparision operators

    /**
     * @brief equal to
     * @note    if VECTOR_OPERATOR_EGALE_COMPARE_LENGTH is define, this function compare length of the both vector. Else it compare the both member.
     *          By default, VECTOR_OPERATOR_EGALE_COMPARE_LENGTH is not define
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator==(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator==(Vector<TLength, TType> const& vec, TType scalar) noexcept;

    /**
     * @brief equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator==(TType scalar, Vector<TLength, TType> const& vec) noexcept;

    /**
     * @brief not equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator!=(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief not equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator!=(Vector<TLength, TType> const& vec, TType scalar) noexcept;

    /**
     * @brief not equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator!=(TType scalar, Vector<TLength, TType> const& vec) noexcept;

    /**
     * @brief less than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief less than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<(Vector<TLength, TType> const& vec, TType scalar) noexcept;

    /**
     * @brief less than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<(TType scalar, Vector<TLength, TType> const& vec) noexcept;

    /**
     * @brief greater than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief greater than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>(Vector<TLength, TType> const& vec, TType scalar) noexcept;

    /**
     * @brief greater than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>(TType scalar, Vector<TLength, TType> const& vec) noexcept;

    /**
     * @brief less than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<=(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief less than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<=(Vector<TLength, TType> const& vec, TType scalar) noexcept;

    /**
     * @brief less than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<=(TType scalar, Vector<TLength, TType> const& vec) noexcept;

    /**
     * @brief greater than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>=(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept;

    /**
     * @brief greater than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>=(Vector<TLength, TType> const& vec, TType scalar) noexcept;

    /**
     * @brief greater than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>=(TType scalar, Vector<TLength, TType> const& vec) noexcept;

    #pragma endregion //!comparision operators
    #pragma region stream operators

    /**
     * @brief output stream
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param out 
     * @param vec 
     * @return constexpr std::ostream& 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    std::ostream& 	operator<<		(std::ostream& out, const Vector<TLength, TType>& vec) noexcept;

    /**
     * @brief input stream
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param out 
     * @param vec 
     * @return constexpr std::ostream& 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    std::istream& 	operator>>		(std::istream& in, const Vector<TLength, TType>& vec) noexcept;

    #pragma endregion //!stream operators

    #include "Vector.inl"

} /*namespace FoxMath::Vector*/