/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-24 - 14 h 15
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

#include "Matrix/GenericMatrix.hpp"
#include "Types/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>, Type::IsSame, Type::Pack
#include "Types/Implicit.hpp" //implicit

namespace FoxMath::Matrix
{
    /*By inherance size cannot be equal to zero and TType must be arythmetic*/
    template <size_t TSize, typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    class SquareMatrix : public GenericMatrix<TSize, TSize, TType, TMatrixConvention>
    {
        private:
    
        protected:
    
        #pragma region attribut
        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods

        /**
         * @brief return the determinant of minor element in function of M aij.
         * 
         * @param i : start to 0 just to n - 1 
         * @param j : start to 0 just to n - 1
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr  
        TType		getMinor		(size_t i, size_t j) const noexcept;

        /**
         * @brief return the result of coeficient multipliate by his cofactor multipliate by the signe : (-1)^(i+j) * minor(i, j)
         * 
         * @param i : start to 0 just to n - 1 
         * @param j : start to 0 just to n - 1
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr  
        TType		getCofactor		(size_t i, size_t j) const noexcept;
            
        /**
         * @brief return the cofactor matrix of the current matrix.
         * 
         * @return constexpr SquareMatrix 
         */
        [[nodiscard]] inline constexpr  
        SquareMatrix		getCoMatrix		() const noexcept;

        /**
         * @brief transpose the cofactor matrix.
         * 
         */
        inline constexpr  
        void		tranformCoMatToAdjointMat		() noexcept;

        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        constexpr inline
        SquareMatrix () noexcept                                            = default;

        constexpr inline
        SquareMatrix (const SquareMatrix& other) noexcept			        = default;

        constexpr inline
        SquareMatrix (SquareMatrix&& other) noexcept				        = default;

        inline
        ~SquareMatrix () noexcept				                            = default;

        constexpr inline
        SquareMatrix& operator=(SquareMatrix const& other) noexcept			= default;

        constexpr inline
        SquareMatrix& operator=(SquareMatrix && other) noexcept			    = default;
    
        /**
         * @brief Construct a new matrix with it's base type
         * 
         * @tparam TTlengthOther 
         * @param other 
         */
        constexpr inline
        SquareMatrix (const GenericMatrix<TSize, TSize, TType, TMatrixConvention>& other) noexcept;

        /**
         * @brief Aggregate initialization for scalar
         * 
         * @note : If the number of initializer clauses is less than the number of members or initializer list is completely empty, the remaining members are value-initialized. 
         * If a member of a reference type is one of these remaining members, the program is ill-formed.
         * 
         * @example `FoxMath::Matrix::SquareMatrix<2, int> mat (1, 1, 3)` or `FoxMath::Matrix::SquareMatrix<2, int> mat (1, 2)`
         * 
         * @tparam T 
         * @tparam true 
         * @tparam true 
         */
        template<typename... T, Type::IsAllSame<TType, T...> = true>
        explicit inline constexpr
        SquareMatrix (T... args) noexcept;

        /**
         * @brief Aggregate initialization for vector
         * 
         * @note : If the number of initializer clauses is less than the number of members or initializer list is completely empty, the remaining members are value-initialized. 
         * If a member of a reference type is one of these remaining members, the program is ill-formed.
         * 
         * @example `FoxMath::Matrix::SquareMatrix<2, int> mat (Vec2f(1, 1), Vec2f(3))` or `FoxMath::Matrix::SquareMatrix<2, int> mat (Vec2f(1.f, 2.f))`
         * 
         * @tparam T 
         * @tparam true 
         * @tparam true 
         */
        template<typename... T>
        explicit inline constexpr
        SquareMatrix (T... args) noexcept;


        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        /**
         * @brief affect identity to matrix
         * 
         * @return constexpr SquareMatrix& 
         */
        inline constexpr  
        SquareMatrix& generateIdentity () noexcept;

        /**
         * @brief Transpose the matrix on itself. Only square matrix can do that because of static matrix
         * 
         * @return constexpr SquareMatrix& 
         */
        inline constexpr  
        SquareMatrix&		transpose		() noexcept;

        /**
         * @brief return true of false if matrix is orthogonal. If M*M.transpose() = I.
         * 
         * @return true 
         * @return false 
         */
        [[nodiscard]] inline constexpr  
        bool		isOrtho		() const noexcept;
    
        /**
         * @brief Calcul the derteminant of square matrix X*X.
         *		  If determinant is geometrical area betwen eache vector in matrix.
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr  
        TType		getDeterminant		() const noexcept;

        /**
         * @brief reserse matrix if it's possible, else return false. 
         * If function if orthogonal, this function return the transposate of matrix.
         * or empty
         * 
         * @return Matrix return empty matrix if reverse is not possible
         */
        [[nodiscard]] inline constexpr  
        SquareMatrix		getReverse		() const noexcept;

        /**
         * @brief reserse matrix if it's possible, else return false.
         * If function if orthogonal, matrix will be transpose.
         * or empty
         * 
         */
        inline constexpr 
        void		reverse		() noexcept;

        #pragma endregion //!methods

        #pragma region static methods

        /**
         * @brief Return true if the number of column and row is same.
         * 
         * @return true
         */
        [[nodiscard]] static inline constexpr
		bool 	    isSquare	() noexcept
        {
            return true;
        }

        /**
         * @brief Get identity matrix.
         * 
         * @return constexpr SquareMatrix& 
         */
        [[nodiscard]] static inline constexpr  
        GenericMatrix<TSize, TSize, TType, TMatrixConvention> identity () noexcept
        {
            assert (isSquare());

            SquareMatrix rst;
            rst.generateIdentity();
            return rst;
        }

        #pragma endregion //!static methods

        #pragma region accessor
        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator

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
        template <size_t TSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
        [[nodiscard]] implicit constexpr inline
        operator SquareMatrix<TSizeOther, TTypeOther, TMatrixConventionOther>() const noexcept;

        #pragma endregion //!operator
    
        #pragma region convertor
        #pragma endregion //!convertor
    };

    #include "Matrix/SquareMatrix.inl"

} /*namespace FoxMath::Matrix*/
