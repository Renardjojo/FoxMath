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
#include "Types/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>, Type::IsSame, Type::Pack
#include "Vector/GenericVector.hpp" //Vector::GenericVector
#include "Types/Implicit.hpp" //implicit
#include "Numeric/Limits.hpp" //isSameAsZero

#include <iostream> //ostream, istream
#include <array> //std::array
#include <utility> //std::swap
#include <cmath> //std::pow //TODO: std::pow is not constexr

/*Only if c++ >= 2020*/
#if __cplusplus >= 201709L
#include <cstring> //std::memcpy
#include <type_traits> //std::is_constant_evaluated
#endif

namespace FoxMath::Vector
{
    template <size_t TSize, typename TType, Matrix::EMatrixConvention TMatrixConvention>
    class NewGenericVector;
}

namespace FoxMath::Matrix
{
    /*Define default template arg and apply template condition*/
    template <size_t TRowSize, size_t TColumnSize, typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor,
                Type::IsNotEqualTo<TRowSize, 0> = true, 
                Type::IsNotEqualTo<TColumnSize, 0> = true,
                Type::IsArithmetic<TType> = true>
    class GenericMatrix;

    /*Specilisation of GenericMatrix class*/
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    class GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>
    {
        public:
    
        #pragma region static attribut

        /**
         * @brief Return the length if internal vector
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr static inline
        size_t vectorLength () noexcept
        {
            if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
                return TRowSize;
            else 
                return TColumnSize;
        }

        /**
         * @brief Return the number of vector inside the matrix
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr static inline
        size_t numberOfInternalVector () noexcept
        {
            if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
                return TColumnSize;
            else 
                return TRowSize;
        }

        /**
         * @brief Return the number of data inside the matrix
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr static inline
        size_t numberOfData () noexcept
        {
            return TRowSize * TColumnSize;
        }

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention&
         */
        [[nodiscard]] static inline constexpr
		EMatrixConvention 	    getMatrixConvention	() noexcept
        {   
            return TMatrixConvention;
        }

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention &
         */
        [[nodiscard]] static inline constexpr
		size_t 	    getRowSize	() noexcept
        {
            return TRowSize;
        }

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention&
         */
        [[nodiscard]] static inline constexpr
		size_t 	    getColumnSize	() noexcept
        {
            return TColumnSize;
        }

        /**
         * @brief Return true if the number of column and row is same.
         * 
         * @return true 
         * @return false 
         */
        [[nodiscard]] static inline constexpr
		bool 	    isSquare	() noexcept
        {
            return TColumnSize == TRowSize;
        }

        /**
         * @brief return void matrix init with zero
         * 
         * @return constexpr GenericMatrix& 
         */
        [[nodiscard]] static inline constexpr  
        GenericMatrix zero () noexcept
        {
            GenericMatrix rst;
            rst.fill(static_cast<TType>(0));
            return rst;
        }

        #pragma endregion //! static attribut

        protected:

        #pragma region attribut

        using InternalVector = Vector::NewGenericVector<vectorLength(), TType, TMatrixConvention>;

        std::array<TType, numberOfData ()> m_data;

        #pragma endregion //!attribut
    
        #pragma region methods
        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        explicit constexpr inline
        GenericMatrix () noexcept;

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

        /**
         * @brief Aggregate initialization for scalar
         * 
         * @note : If the number of initializer clauses is less than the number of members or initializer list is completely empty, the remaining members are value-initialized. 
         * If a member of a reference type is one of these remaining members, the program is ill-formed.
         * 
         * @example `FoxMath::Matrix::Matrix<2, 2, int> mat (1, 1, 3)` or `FoxMath::Matrix::Matrix<2, 2, int> mat (1, 2)`
         * 
         * @tparam T 
         * @tparam true 
         * @tparam true 
         */
        template<typename... T, Type::IsAllSame<TType, T...> = true>
        explicit inline constexpr
        GenericMatrix (T... args) noexcept
            : m_data {}
        {
            if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
            {
                std::array<TType, numberOfData ()> dataRowMajor{args...};

                for (size_t i = 0; i < numberOfInternalVector(); i++)
                {
                    for (size_t j = 0; j < vectorLength(); j++)
                    {
                        m_data[i * vectorLength() + j] = dataRowMajor[j * numberOfInternalVector() + i];
                    }
                }               
            }
            else
            {
                m_data = std::array<TType, numberOfData ()>{args...};
            }
        }

        /**
         * @brief Aggregate initialization for vector
         * 
         * @note : If the number of initializer clauses is less than the number of members or initializer list is completely empty, the remaining members are value-initialized. 
         * If a member of a reference type is one of these remaining members, the program is ill-formed.
         * 
         * @example `FoxMath::Matrix::Matrix<2, 2, int> mat (Vec2f(1, 1), Vec2f(3))` or `FoxMath::Matrix::Matrix<2, 2, int> mat (Vec2f(1.f, 2.f))`
         * 
         * @tparam T 
         * @tparam true 
         * @tparam true 
         */
        explicit inline constexpr
        GenericMatrix (const std::initializer_list<InternalVector>& vecs) noexcept
            : m_data {}
        {
            assert (vecs.size() <= numberOfInternalVector());

            auto itVecs = vecs.begin();

            for (size_t i = 0; i < vecs.size(); i++)
            {
                for (size_t j = 0; j < vectorLength(); j++)
                {
                    m_data[i * numberOfInternalVector() + j] = (*itVecs)[j];
                }
                itVecs++;
            }
        }

        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        /**
         * @brief Fill generic vector's member with scalar value
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
        inline constexpr  
        GenericMatrix& fill (const TscalarType scalar) noexcept;

        /**
         * @brief Get the Transpose object. If the user wan't to change the convention it can add it in template arg
         * 
         * @note : If you really wan't to transpose matrix itself, you can use union : Matrix<4, 2> and Matrix<2, 4> share the same memory space
         * 
         * @tparam TMatrixConvention 
         * @return constexpr GenericMatrix<TColumnSize, TRowSize, TType, TMatrixConventionOther> 
         */
        template <EMatrixConvention TMatrixConventionOther = TMatrixConvention>
        [[nodiscard]] inline constexpr  
        GenericMatrix<TColumnSize, TRowSize, TType, TMatrixConventionOther>		getTransposed	() const noexcept;

        #pragma endregion //!methods
    
        #pragma region accessor

        /**
         * @brief Returns a reference to the data at index in the GenericMatrix
         * 
         * A similar member function, GenericMatrix::getDataAt, has the same behavior as this operator function,
         * except that GenericMatrix::getDataAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @param index 
         * @return constexpr TType& 
         */
        [[nodiscard]] inline constexpr
		TType& 	    getData	(size_t index) noexcept;

        /**
         * @brief Returns a reference to the data at index in the GenericMatrix
         * 
         * A similar member function, GenericMatrix::getDataAt, has the same behavior as this operator function,
         * except that GenericMatrix::getDataAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @param i : vector index
         * @param j : data on vector index
         * @return constexpr TType& 
         */
        [[nodiscard]] inline constexpr
		TType& 	    getData	(size_t i, size_t j) noexcept;

        /**
         * @brief Returns a reference to the data at index in the GenericMatrix
         * 
         * A similar member function, GenericMatrix::getDataAt, has the same behavior as this operator function,
         * except that GenericMatrix::getDataAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @param index 
         * @return constexpr const TType (avoid getData([...]) = [...])
         */
        [[nodiscard]] inline constexpr
		const TType	    getData	(size_t index) const noexcept;

        /**
         * @brief Returns a reference to the data at index in the GenericMatrix
         * 
         * A similar member function, GenericMatrix::getDataAt, has the same behavior as this operator function,
         * except that GenericMatrix::getDataAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * 
         * @param i : vector index
         * @param j : data on vector index
         * @return constexpr const TType (avoid getData([...]) = [...]) 
         */
        [[nodiscard]] inline constexpr
		const TType	    getData	(size_t i, size_t j) const noexcept;

        /**
         * @brief   Returns a const data to the vector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member GenericMatrix::getData(), that does not check against bounds.
         * 
         * @param index 
         * @return constexpr TType& 
         */
        [[nodiscard]] inline constexpr
		TType& 	    getDataAt	(size_t index) throw();

        /**
         * @brief   Returns a const data to the vector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member GenericMatrix::getData(), that does not check against bounds.
         * 
         * @param i : vector index
         * @param j : data on vector index
         * @return constexpr TType& 
         */
        [[nodiscard]] inline constexpr
		TType& 	    getDataAt	(size_t i, size_t j) throw();

        /**
         * @brief   Returns a const data to the vector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member GenericMatrix::getData(), that does not check against bounds.
         * 
         * @param index 
         * @return constexpr const TType (avoid getData([...]) = [...])
         */
        [[nodiscard]] inline constexpr
		const TType	    getDataAt	(size_t index) const throw ();

        /**
         * @brief   Returns a const data to the vector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member GenericMatrix::getData(), that does not check against bounds.
         * 
         * @param i : vector index
         * @param j : data on vector index
         * @return constexpr const Type (avoid getData([...]) = [...])
         */
        [[nodiscard]] inline constexpr
		const TType	    getDataAt	(size_t i, size_t j) const throw();

        /**
         * @brief Returns a reference to the vector at index in the GenericMatrix
         * 
         * A similar member function, GenericMatrix::getVectorAt, has the same behavior as this operator function,
         * except that GenericMatrix::getVectorAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @param index 
         * @return constexpr InternalVector& 
         */
        [[nodiscard]] inline constexpr
		InternalVector& 	    getVector	(size_t index) noexcept;

        /**
         * @brief Returns a reference to the vector at index in the GenericMatrix
         * 
         * A similar member function, GenericMatrix::getVectorAt, has the same behavior as this operator function,
         * except that GenericMatrix::getVectorAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @param index 
         * @return constexpr const InternalVector& 
         */
        [[nodiscard]] inline constexpr
		const InternalVector& 	    getVector	(size_t index) const noexcept;    

        /**
         * @brief   Returns a const reference to the vector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member GenericMatrix::getVector(), that does not check against bounds.
         * 
         * @param index 
         * @return constexpr InternalVector& 
         */
        [[nodiscard]] inline constexpr
		InternalVector& 	    getVectorAt	(size_t index) throw();

        /**
         * @brief   Returns a const reference to the vector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member GenericMatrix::getVector(), that does not check against bounds.
         * 
         * @param index 
         * @return constexpr const InternalVector& 
         */
        [[nodiscard]] inline constexpr
		const InternalVector& 	    getVectorAt	(size_t index) const throw ();
        
        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma region member access operators

        /**
         * @brief Returns a pointer to the data at index in the GenericMatrix
         * 
         * A similar member function, GenericMatrix::at, has the same behavior as this operator function,
         * except that GenericMatrix::at is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @note : use [indexVector][indexElem] to access at the element
         * 
         * @param index 
         * @return constexpr TType*
         */
        [[nodiscard,]] inline constexpr
		TType* 	    operator[]	(size_t index) noexcept;

        /**
         * @brief Returns a pointer to the data at index in the GenericMatrix
         * 
         * A similar member function, GenericMatrix::getDataAt, has the same behavior as this operator function,
         * except that GenericMatrix::getDataAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @note : use [indexVector][indexElem] to access at the element
         * 
         * @param index 
         * @return constexpr const const TType*
         */
        [[nodiscard]] inline constexpr
		const TType* 	    operator[]	(size_t index) const noexcept;

        #pragma endregion //!member access operators
        #pragma region  assignment operators

        /**
         * @brief fill the matrix with scalar assigned
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator+=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator+=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator-=(TscalarType scalar) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator-=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator*=(TscalarType scalar) noexcept;

        /**
         * @brief multiplication assignment. Only work if other is square.
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, 
        Type::IsEqualTo<TColumnSize, TRowSizeOther> = true,
        Type::IsEqualTo<TRowSizeOther, TColumnSizeOther> = true>
		inline constexpr
		GenericMatrix& operator*=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator/=(TscalarType scalar) noexcept;

        /**
         * @brief division assignment. Do not multiply this by the inverse of matrix but divide each member of ther by member of this
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator/=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator%=(TscalarType scalar) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator%=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator&=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator&=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator|=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator|=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator^=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator^=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator<<=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator<<=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator>>=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
		inline constexpr
		GenericMatrix& operator>>=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept;

        #pragma endregion //!region assignment operators
        #pragma region increment decrement operators

        /**
         * @brief  pre-increment operator
         * 
         * @return constexpr GenericMatrix& 
         */
        inline constexpr
		GenericMatrix& 	operator++	() noexcept;

        /**
         * @brief pre-decrement operator
         * 
         * @return constexpr GenericMatrix& 
         */
        inline constexpr
		GenericMatrix& 	operator--	() noexcept;
        
        /**
         * @brief post-increment  operator
         * 
         * @return constexpr GenericMatrix 
         */
        inline constexpr
		GenericMatrix 	    operator++	(int) noexcept;

        /**
         * @brief post-decrement operator
         * 
         * @return constexpr GenericMatrix 
         */
        inline constexpr
		GenericMatrix 	    operator--	(int) noexcept;

        #pragma endregion //!increment decrement operators
        #pragma region convertor

        /**
         * @brief Converte generic matrix to another generic matrix type
         * @note use static_cast<> to call this function. Is use only if you try to downgrade generic matrix like static_cast<Vec3f>(vec4f). Else use the constructor
         * @example `FoxMath::Matrix::Matrix<2, 3, float> rhs = static_cast<FoxMath::Matrix::Matrix<8, 2, int, EMatrixConvention::RowMajor>>(lhs)`
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @tparam TMatrixConventionOther 
         * @return GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
        [[nodiscard]] implicit constexpr inline
        operator GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>() const noexcept;


        #pragma endregion //!convertor
        #pragma endregion //!operators
    
    };

    #pragma region arithmetic operators

    /**
     * @brief unary plus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept;

    /**
     * @brief unary minus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, const GenericMatrix< TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& rhs) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& rhs) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator*(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator*(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther,
                Type::IsEqualTo<TColumnSize, TRowSizeOther> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSizeOther, TType, TMatrixConvention> operator*(const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& lhs, const GenericMatrix<TRowSizeOther, TColumnSizeOther, TType, TMatrixConvention>& rhs) noexcept;


    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise AND 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise OR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief bitwise right shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief bitwise NOT
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator~(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    #pragma endregion //!logical operators
    #pragma region logical operators

    /**
     * @brief negation
     * 
     * @tparam TRowSize 
     * @tparam TColumnSize 
     * @tparam TMatrixConvention 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> 
     */
    template <size_t TRowSize, size_t TColumnSize, EMatrixConvention TMatrixConvention>
    [[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> operator!(GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> mat) noexcept;
	
    /**
     * @brief AND
     * 
     * @tparam TRowSize 
     * @tparam TColumnSize 
     * @tparam TMatrixConvention 
     * @tparam TRowSizeOther 
     * @tparam TColumnSizeOther 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> 
     */
    template <size_t TRowSize, size_t TColumnSize, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther>
    [[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> operator&&(GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, bool, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief inclusive OR
     * 
     * @tparam TRowSize 
     * @tparam TColumnSize 
     * @tparam TMatrixConvention 
     * @tparam TRowSizeOther 
     * @tparam TColumnSizeOther 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> 
     */
    template <size_t TRowSize, size_t TColumnSize, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther>
    inline constexpr
    GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> operator||(GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, bool, TMatrixConvention> const& rhs) noexcept;

    #pragma endregion //!logical operators
    #pragma region comparision operators

    /**
     * @brief equal to
     * @note    if VECTOR_OPERATOR_EGALE_COMPARE_LENGTH is define, this function compare length of the both generic vector. Else it compare the both member.
     *          By default, VECTOR_OPERATOR_EGALE_COMPARE_LENGTH is not define
     * 
     * @tparam TRowSize 
     * @tparam TColumnSize 
     * @tparam TType 
     * @tparam TMatrixConvention 
     * @tparam TTypeOther 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator==(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSize, TColumnSize, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief Check if all element is same as the scalar
     * 
     * @tparam TRowSize 
     * @tparam TColumnSize 
     * @tparam TType 
     * @tparam TMatrixConvention 
     * @tparam TTypeScalar 
     * @param mat 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar>
    [[nodiscard]] inline constexpr
    bool operator==(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat, TTypeScalar scalar) noexcept;

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
    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator!=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept;

    /**
     * @brief Check if all element is not same as the scalar
     * 
     * @tparam TRowSize 
     * @tparam TColumnSize 
     * @tparam TType 
     * @tparam TMatrixConvention 
     * @tparam TTypeScalar 
     * @param mat 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar>
    [[nodiscard]] inline constexpr
    bool operator!=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat, TTypeScalar scalar) noexcept;

    #pragma endregion //!comparision operators
    #pragma region stream operators

    /**
     * @brief output stream
     * 
     * @note : define std::setprecision(n) before calling this operator to define floating point prescision like : 
     * i.e. : std::cout << std::setprecision(4) << std::fixed << << mat; (don't forgot to include <iomanip>)
     * You can also display the convention of vector with function matrixConventionToString. 
     * i.e. : std::cout << matrixConventionToString(mat.getMatrixConvention()) << std::endl << std::setprecision(4) << std::fixed << mat;
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param out 
     * @param mat 
     * @return constexpr std::ostream& 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    inline constexpr
    std::ostream& 	operator<<		(std::ostream& out, const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& mat) noexcept;

    /**
     * @brief input stream
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param out 
     * @param mat 
     * @return constexpr std::ostream& 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    inline constexpr
    std::istream& 	operator>>		(std::istream& in, const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& mat) noexcept;

    #pragma endregion //!stream operators

    /**
     * @brief This function solve a system of n equation of n unknow. 
     * @example q1 * x1 + q2 * x2 + q3 * x3 = v1 or q4 * x1 + q5 * x2 + q6 * x3 = v2
     * 
     * @note    Enter in parameter each coef under the form of matrix and each result under the form of colmun vector (other matrix) 
     *	        Assert if matrix of equation colum is under 1 or if one of all matrix is empty.
     * 
     * @tparam TSizeEquation 
     * @tparam TType 
     * @param eqCoef 
     * @param eqRslt 
     * @return constexpr GenericMatrix<TSizeEquation, TSizeEquation, TType, EMatrixConvention::RowMajor> 
     */
    template <size_t TSizeEquation, typename TType>
    [[nodiscard]] static inline constexpr 
    GenericMatrix<TSizeEquation, TSizeEquation, TType, EMatrixConvention::RowMajor> getSolvationNEquationOfNInknow		(const GenericMatrix<TSizeEquation, TSizeEquation, TType, EMatrixConvention::RowMajor>& eqCoef, const Vector::GenericVector<TSizeEquation, TType>& eqRslt) noexcept;

    #include "GenericMatrix.inl"

    template <size_t TRowSize, size_t TColumnSize, typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix = GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>;

    template <size_t TRowSize, size_t TColumnSize, typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat = Matrix<TRowSize, TColumnSize, TType, TMatrixConvention>;

} /*namespace FoxMath::Matrix*/