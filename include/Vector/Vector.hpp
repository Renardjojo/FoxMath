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

//TODO: add scalar and other operator

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

        ::std::array<TType, TLength> m_data;

        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods
        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        constexpr inline 
        Vector ();
        
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
        Vector (T... args);

        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        /**
         * @brief Fill vector's member with scalar value
         * 
         */
        inline constexpr  
        void fill (const TType scalar);

        [[nodiscard]] inline constexpr
        TType squartLength () const;

        [[nodiscard]] inline constexpr
        TType length () const;

/*
		float 		dotProduct	 	(const Vec3& other) const;
		static float dot(const Vec3& vec1, const Vec3& vec2) { return vec1.dotProduct(vec2); }

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
		static Vec3 	cross		(const Vec3& vec1, const Vec3& vec2) { return vec1.getCross(vec2); }

		static Vec3 	lerp		(const Vec3& vec1, const Vec3& vec2, float t);
        */

        #pragma endregion //!methods
    
        #pragma region accessor
        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma region member access operators

        [[nodiscard]] inline constexpr
		TType& 	    operator[]	(size_t index);

        [[nodiscard]] inline constexpr
		const TType& 	    operator[]	(size_t index) const;

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
		Vector& operator=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator=(TscalarType scalar);

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
		Vector& operator+=(TscalarType scalar);

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
		Vector& operator+=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator-=(TscalarType scalar);

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
		Vector& operator-=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator*=(TscalarType scalar);

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
		Vector& operator*=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator/=(TscalarType scalar);

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
		Vector& operator/=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator%=(TscalarType scalar);

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
		Vector& operator%=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator&=(TscalarType scalar);

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
		Vector& operator&=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator|=(TscalarType scalar);

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
		Vector& operator|=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator^=(TscalarType scalar);

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
		Vector& operator^=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator<<=(TscalarType scalar);

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
		Vector& operator<<=(const Vector<TLengthOther, TTypeOther>& other);

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
		Vector& operator>>=(TscalarType scalar);

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
		Vector& operator>>=(const Vector<TLengthOther, TTypeOther>& other);

        #pragma endregion //!region assignment operators
        #pragma region increment decrement operators

        /**
         * @brief  pre-increment operator
         * 
         * @return constexpr Vector& 
         */
        inline constexpr
		Vector& 	operator++	();

        /**
         * @brief pre-decrement operator
         * 
         * @return constexpr Vector& 
         */
        inline constexpr
		Vector& 	operator--	();
        
        /**
         * @brief post-increment  operator
         * 
         * @return constexpr Vector 
         */
        inline constexpr
		Vector 	    operator++	(int);

        /**
         * @brief post-decrement operator
         * 
         * @return constexpr Vector 
         */
        inline constexpr
		Vector 	    operator--	(int);

        #pragma endregion //!increment decrement operators
        #pragma region convertor

        template <size_t TLengthOther, typename TTypeOther>
        constexpr inline explicit 
        operator Vector<TLengthOther, TTypeOther>() const;

        #pragma endregion //!convertor
    };

    #pragma region arithmetic operators

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator+(Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator-(Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator+(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator+(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator+(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator-(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator-(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator-(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator*(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator*(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator*(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator/(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator/(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator/(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator%(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator%(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator%(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator&(Vector<TLength, TType> const& vec1, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator&(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator&(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator|(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator|(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator|(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator^(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator^(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator^(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator<<(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator<<(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator<<(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator>>(Vector<TLength, TType> const& vec, TType scalar);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator>>(TType scalar, Vector<TLength, TType> const& vec);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator>>(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    Vector<TLength, TType> operator~(Vector<TLength, TType> const& vec);

    #pragma endregion //!logical operators
    #pragma region logical operators
    
    template <size_t TLength>
	[[nodiscard]] inline constexpr
    Vector<TLength, bool> operator!(Vector<TLength, bool> const& vec);
	
    template <size_t TLength>
	[[nodiscard]] inline constexpr
    Vector<TLength, bool> operator&&(Vector<TLength, bool> const& vec1, Vector<TLength, bool> const& vec2);

	template <size_t TLength>
	[[nodiscard]] inline constexpr
    Vector<TLength, bool> operator||(Vector<TLength, bool> const& vec1, Vector<TLength, bool> const& vec2);
    
    #pragma endregion //!logical operators
    #pragma region comparision operators

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator==(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator==(Vector<TLength, TType> const& vec, TType scalar);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator==(TType scalar, Vector<TLength, TType> const& vec);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator!=(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator!=(Vector<TLength, TType> const& vec, TType scalar);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator!=(TType scalar, Vector<TLength, TType> const& vec);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<(Vector<TLength, TType> const& vec, TType scalar);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<(TType scalar, Vector<TLength, TType> const& vec);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>(Vector<TLength, TType> const& vec, TType scalar);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>(TType scalar, Vector<TLength, TType> const& vec);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<=(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<=(Vector<TLength, TType> const& vec, TType scalar);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator<=(TType scalar, Vector<TLength, TType> const& vec);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>=(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>=(Vector<TLength, TType> const& vec, TType scalar);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    bool operator>=(TType scalar, Vector<TLength, TType> const& vec);

    #pragma endregion //!comparision operators
    #pragma region stream operators

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    std::ostream& 	operator<<		(std::ostream& out, const Vector<TLength, TType>& vec);

    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    std::istream& 	operator>>		(std::istream& in, const Vector<TLength, TType>& vec);

    #pragma endregion //!stream operators

    #include "Vector.inl"

} /*namespace FoxMath::Vector*/