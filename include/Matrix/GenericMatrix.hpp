/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-18 - 08 h 31
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

#include "Matrix/EMatrixConvention.hpp" //EMatrixConvention
#include "Types/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>
#include "Vector/GenericVector.hpp" //Vector::GenericVector
#include "Types/Implicit.hpp"

#include <array> //std::array

namespace FoxMath::Matrix
{
    /*Use of IsArithmetic*/
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor,
                Type::IsNotEqualTo<TRowSize, 0> = true, 
                Type::IsNotEqualTo<TColumnSize, 0> = true,
                Type::IsArithmetic<TType> = true>
    class GenericMatrix;

    /*Specilisation of GenericMatrix class*/
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    class GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>
    {
        private:
    
        protected:

        #pragma region attribut/methods

        /**
         * @brief Return the length if internal vector
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr inline
        size_t vectorLength () const noexcept;

        /**
         * @brief Return the number of vector inside the matrix
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr inline
        size_t numberOfInternalVector () const noexcept;

        /**
         * @brief Return the number of data inside the matrix
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr inline
        size_t numberOfData () const noexcept;

        #pragma endregion //!attribut/methods

        #pragma region attribut

        using InternalVector = Vector::GenericVector<TType, vectorLength ()>;

        union
        {
            std::array<TType, TRowSize * TColumnSize> m_data {};
            std::array<InternalVector, numberOfInternalVector ()>  m_vector {};
        };

        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods
        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        constexpr inline
        GenericMatrix () noexcept 					                    = default;

        constexpr inline
        GenericMatrix (const GenericMatrix& other) noexcept			    = default;

        constexpr inline
        GenericMatrix (GenericMatrix&& other) noexcept				    = default;

        inline
        ~GenericMatrix () noexcept				                        = default;

        constexpr inline
        GenericMatrix& operator=(GenericMatrix const& other) noexcept	= default;

        constexpr inline
        GenericMatrix& operator=(GenericMatrix && other) noexcept		= default;
    
        #pragma endregion //!constructor/destructor
    
        #pragma region methods
        #pragma endregion //!methods
    
        #pragma region accessor

        /**
         * @brief   Returns a reference to the InternalVector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : use at(indexVector).at(indexElem) to access at the element
         * 
         * @param index 
         * @return constexpr InternalVector& 
         */
        [[nodiscard]] inline constexpr
		InternalVector& 	    at (size_t index) throw ();

        /**
         * @brief   Returns a const reference to the InternalVector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : use at(indexVector).at(indexElem) to access at the element
         * 
         * @param index 
         * @return constexpr const InternalVector& 
         */
        [[nodiscard]] inline constexpr
		const InternalVector& 	at (size_t index) const throw ();

        /**
         * @brief   Returns a reference to the element at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : to avoid this check, use that form [indexVec][indexElem]. These both operators are inline and have no impact on read latency 
         * 
         * @param index 
         * @return constexpr TType& 
         */
        [[nodiscard]] inline constexpr
		TType& 	    getData	(size_t index) throw();

        /**
         * @brief   Returns a const reference to the element at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : to avoid this check, use that form [indexVec][indexElem]. These both operators are inline and have no impact on read latency 
         * 
         * @param index 
         * @return constexpr const TType& 
         */
        [[nodiscard]] inline constexpr
		const TType& 	    getData	(size_t index) const throw ();

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention&
         */
        [[nodiscard]] inline constexpr
		const EMatrixConvention& 	    getMatrixConvention	() const noexcept;

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention &
         */
        [[nodiscard]] inline constexpr
		const size_t& 	    getRowSize	() const noexcept;

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention&
         */
        [[nodiscard]] inline constexpr
		const size_t& 	    getColumnSize	() const noexcept;
        
        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma region member access operators

        /**
         * @brief   Returns a reference to the InternalVector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : use at[indexVector][indexElem] to access at the element
         * 
         * @param index 
         * @return constexpr InternalVector& 
         */
        [[nodiscard]] inline constexpr
		InternalVector& 	    operator[]	(size_t index) noexcept;

        /**
         * @brief   Returns a reference to the InternalVector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : use at[indexVector][indexElem] to access at the element
         * 
         * @param index 
         * @return constexpr const InternalVector& 
         */
        [[nodiscard]] inline constexpr
		const InternalVector& 	    operator[]	(size_t index) const noexcept;

        #pragma endregion //!member access operators
        #pragma region  assignment operators

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator+=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator+=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator-=(TscalarType scalar) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator-=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator*=(TscalarType scalar) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator*=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator/=(TscalarType scalar) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator/=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator%=(TscalarType scalar) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator%=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator&=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator&=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator|=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator|=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator^=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator^=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator<<=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator<<=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator>>=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator>>=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        #pragma endregion //!region assignment operators
        #pragma region increment decrement operators

        /**
         * @brief  pre-increment operator
         * 
         * @return constexpr GenericVector& 
         */
        inline constexpr
		GenericVector& 	operator++	() noexcept;

        /**
         * @brief pre-decrement operator
         * 
         * @return constexpr GenericVector& 
         */
        inline constexpr
		GenericVector& 	operator--	() noexcept;
        
        /**
         * @brief post-increment  operator
         * 
         * @return constexpr GenericVector 
         */
        inline constexpr
		GenericVector 	    operator++	(int) noexcept;

        /**
         * @brief post-decrement operator
         * 
         * @return constexpr GenericVector 
         */
        inline constexpr
		GenericVector 	    operator--	(int) noexcept;

        #pragma endregion //!increment decrement operators
        #pragma region convertor

        /**
         * @brief Converte generic vector to another generic vector type
         * @note use static_cast<> to call this function. Is use only if you try to downgrade generic vector like static_cast<Vec3f>(vec4f). Else use the constructor
         * @example `FoxMath::Vector::Vector<2, float> rhs = static_cast<FoxMath::Vector::Vector<2, float>>(vec)`
         * @tparam TLengthOther 
         * @tparam TTypeOther 
         * @return GenericVector<TLengthOther, TTypeOther> 
         */
        template <size_t TLengthOther, typename TTypeOther>
        [[nodiscard]] implicit constexpr inline
        operator GenericVector<TLengthOther, TTypeOther>() const noexcept;

        #pragma endregion //!convertor
        #pragma endregion //!operators
    
    };

    #pragma region arithmetic operators

    /**
     * @brief unary plus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> const& vec) noexcept;

    /**
     * @brief unary minus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator+(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> lhs, const GenericVector< TLengthOther, TTypeOther>& rhs) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator-(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> lhs, const GenericVector<TLengthOther, TTypeOther>& rhs) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator*(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator*(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator*(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator/(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator/(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator/(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator%(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator%(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator%(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator&(GenericVector<TLength, TType> lhs, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator&(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise AND 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator&(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator|(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise OR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator|(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator|(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator^(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator^(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator^(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator<<(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator<<(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator<<(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise right shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator>>(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator>>(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator>>(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise NOT
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator~(GenericVector<TLength, TType> vec) noexcept;

    #pragma endregion //!logical operators
    #pragma region logical operators
    
    /**
     * @brief negation
     * 
     * @tparam TLength 
     * @param vec 
     * @return constexpr GenericVector<TLength, bool> 
     */
    template <size_t TLength>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, bool> operator!(GenericVector<TLength, bool> vec) noexcept;
	
    /**
     * @brief AND
     * 
     * @tparam TLength 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, bool> 
     */
    template <size_t TLength, size_t TLengthOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, bool> operator&&(GenericVector<TLength, bool> lhs, GenericVector<TLengthOther, bool> const& rhs) noexcept;

    /**
     * @brief inclusive OR
     * 
     * @tparam TLength 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, bool> 
     */
	template <size_t TLength, size_t TLengthOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, bool> operator||(GenericVector<TLength, bool> lhs, GenericVector<TLengthOther, bool> const& rhs) noexcept;
    
    #pragma endregion //!logical operators
    #pragma region comparision operators

    /**
     * @brief equal to
     * @note    if VECTOR_OPERATOR_EGALE_COMPARE_LENGTH is define, this function compare length of the both generic vector. Else it compare the both member.
     *          By default, VECTOR_OPERATOR_EGALE_COMPARE_LENGTH is not define
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator==(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator==(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator==(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator!=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator!=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator!=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator<(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator>(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator<=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator>=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

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
    template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    std::ostream& 	operator<<		(std::ostream& out, const GenericVector<TLength, TType>& vec) noexcept;

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
    std::istream& 	operator>>		(std::istream& in, const GenericVector<TLength, TType>& vec) noexcept;

    #pragma endregion //!stream operators

    #include "GenericMatrix.inl"

    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    using Matrix = GenericVector<TRowSize, TColumnSize, TType, TMatrixConvention>;

    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    using Mat = Matrix<TRowSize, TColumnSize, TType, TMatrixConvention>;

} /*namespace FoxMath::Matrix*/