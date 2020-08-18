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

#include "Matrix/EMatrixConvention.hpp" //EmatrixConvention
#include "Types/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>
#include "Vector/GenericVector.hpp" //Vector::GenericVector

#include <array> //std::array

namespace FoxMath::Matrix
{
    /*Use of IsArithmetic*/
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor, Type::IsArithmetic<TType> = true>
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
        size_t numberOfVectorInMatrix () const noexcept;

        #pragma endregion //!attribut/methods

        #pragma region attribut

        union
        {
            std::array<TType, TRowSize * TColumnSize> m_data {};
            std::array<Vector::GenericVector<TType, vectorLength ()>, numberOfVectorInMatrix ()>  m_vector {};
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
        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma endregion //!operator
    
        #pragma region convertor
        #pragma endregion //!convertor
    
    };

    #include "GenericMatrix.inl"

} /*namespace FoxMath::Matrix*/


class Matrix
{


    public :

    Matrix () {}

    const Vector3f& getC1() const { return columnsVec.x;}
};