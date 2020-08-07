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
         * @brief return length of the vector 
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
		Vector& 	normalize	    () noexcept;

        /**
         * @brief  Returns the normalized vector. If the vector is null (all components are set to 0), then vector zero is returned.
         * 
         * @return constexpr const Vector& 
         */
        [[nodiscard]] inline constexpr
        const Vector& getNormalized		() const noexcept;

/*
		float 		dotProduct	 	(const Vec3& other) const;
		static float dot(const Vec3& lhs, const Vec3& rhs) { return lhs.dotProduct(rhs); }

		//same as get magnitude
		float 		length		 		() 			 const;
		float 		squartLength 		() 			 const;

		//creat unit vector
		Vec3& 	normalize		();
		Vec3 	getNormalize	() const;

		//clamp magnitude
		Vec3& clampLength(float max);

		//cross product between 2 vectors
		void 			cross		(const Vec3& other);
		Vec3 			cross	    (const Vec3& other) const;
		static Vec3 	cross		(const Vec3& lhs, const Vec3& rhs) { return lhs.getCross(rhs); }

		static Vec3 	lerp		(const Vec3& lhs, const Vec3& rhs, float t);
        */

        #pragma endregion //!methods
    
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
    Vector<TLength, TType> operator-(Vector<TLength, TType> lhs, Vector<TLength, TType> rhs) noexcept;

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