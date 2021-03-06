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
#include "Types/SFINAEShorthand.hpp" //IsArithmetic<TType>, IsSame, Pack
#include "Types/Implicit.hpp" //implicit
#include "Angle/Angle.hpp"
#include "Macro/CrossInheritanceCompatibility.hpp"
#include "Algorythm/Numeric.hpp" //powSigned

namespace FoxMath
{
    /*By inherance size cannot be equal to zero and TType must be arythmetic*/
    template <size_t TSize, typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    class SquareMatrix : public GenericMatrix<TSize, TSize, TType, TMatrixConvention>
    {
        private:
    
            using Parent = GenericMatrix<TSize, TSize, TType, TMatrixConvention>;

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
    
        DECLARE_CROSS_INHERITANCE_COMPATIBILTY(SquareMatrix, Parent, GenericMatrix)

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
        SquareMatrix&		reverse		() noexcept;

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

        /**
         * @brief Create a Rotation Arround Axis Matrix object
         * 
         * @param unitAxis : Vector to use. Must be unit
         * @param angleRad 
         * @return SquareMatrix 
         */
        [[nodiscard]] static inline constexpr
        SquareMatrix createRotationArroundAxisMatrix (const GenericVector<TSize, TType>& unitAxis, Angle<EAngleType::Radian, TType> angle) noexcept
        {
            assert(unitAxis == static_cast<TType>(1)); //assert if axis is not unit

            SquareMatrix rst;

            const TType s = std::sin(static_cast<TType>(angle));
            const TType c = std::cos(static_cast<TType>(angle));
            const TType t = (static_cast<TType>(1) - c);

            for (size_t i = 0; i < TSize; i++)
            {
                for (size_t j = 0; j < TSize; j++)
                {
                    const TType rotTrigo = (i == j) ? c : s * unitAxis[(TSize - i) - j];

                    if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
                    {
                        const signed char sign = (i < j) ? -powSign(i + j) : powSign(i + j);
                        rst.getData(i * TSize + j) = t * unitAxis[i] * unitAxis[j] + sign * rotTrigo;
                    }
                    else
                    {
                        const signed char sign = (i > j) ? -powSign(i + j) : powSign(i + j);
                        rst.getData(i * TSize + j) = t * unitAxis[i] * unitAxis[j] + sign * rotTrigo;
                    }
                }
            }

            return rst;
        }


        /**
         * @brief Create a Translation Matrix object
         * 
         * @param vecTranslation 
         * @return constexpr SquareMatrix 
         */
        [[nodiscard]] static inline constexpr
        SquareMatrix<TSize + 1, TType, TMatrixConvention> createTranslationMatrix (const GenericVector<TSize, TType>& vecTranslation) noexcept
        {
            SquareMatrix<TSize + 1, TType, TMatrixConvention> rst;
            rst.generateIdentity();

            const size_t lastVectorIndex = TSize * (TSize + 1);

            for (size_t i = 0; i < TSize; i++)
            {
                rst.getData(lastVectorIndex + i) = vecTranslation[i];
            }

            return rst;
        }

        /**
         * @brief Create a Scale Matrix object
         * 
         * @param vecScale 
         * @return constexpr SquareMatrix 
         */
        [[nodiscard]] static inline constexpr
        SquareMatrix createScaleMatrix (const GenericVector<TSize, TType>& vecScale) noexcept
        {
            SquareMatrix rst;
            rst.fill(static_cast<TType>(0));

            for (size_t i = 0; i < TSize; i++)
            {
                rst.getData(i * TSize + i) = vecScale[i];
            }
            rst.getData(TSize * TSize - 1) = static_cast<TType>(1);

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
         * @example `FoxMath::Matrix<2, 3, float> rhs = static_cast<FoxMath::Matrix<8, 2, int, EMatrixConvention::RowMajor>>(lhs)`
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

} /*namespace FoxMath*/
