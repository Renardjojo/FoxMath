/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-25 - 20 h 25
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

#include "Matrix/SquareMatrix.hpp"
#include "Vector/Vector3.hpp"
#include "Macro/CrossInheritanceCompatibility.hpp"

namespace FoxMath::Matrix
{
    template <typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    class Matrix3 :  public SquareMatrix<3, TType, TMatrixConvention>
    {
        private:

        using Parent = SquareMatrix<3, TType, TMatrixConvention>;

        protected:

        #pragma region attribut
        #pragma endregion //!attribut

        #pragma region static attribut
        #pragma endregion //! static attribut

        #pragma region methods
        #pragma endregion //!methods

        public:

        #pragma region constructor/destructor

        constexpr inline
        Matrix3 () noexcept 					                = default;

        constexpr inline
        Matrix3 (const Matrix3& other) noexcept			        = default;

        constexpr inline
        Matrix3 (Matrix3&& other) noexcept				        = default;

        inline
        ~Matrix3 () noexcept				                    = default;

        constexpr inline
        Matrix3& operator=(Matrix3 const& other) noexcept		= default;

        constexpr inline
        Matrix3& operator=(Matrix3 && other) noexcept			= default;

        DECLARE_CROSS_INHERITANCE_COMPATIBILTY(Matrix3, Parent, SquareMatrix)

        #pragma endregion //!constructor/destructor

        #pragma region methods
        #pragma endregion //!methods

        #pragma region static metods

        /**
         * @brief Create a Look At View objectreates a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an UP vector. 
         * 
         * @note translation is not apply 
         * 
         * @param from : Specifies the position of the from point.
         * @param to : Specifies the position of the reference point.
         * @param up : Specifies the direction of the up vector. 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline
        Matrix3 createLookAtView (const Vector::Vec3<TType> & from, const Vector::Vec3<TType> & to, const Vector::Vec3<TType> & up) noexcept
        {
            const Vector::Vec3<TType> forward   ((to - from).getNormalized());
            const Vector::Vec3<TType> side      (forward.getCross(up).getNormalized());
            const Vector::Vec3<TType> vUp        (side.getCross(forward));

            return {    side.getX(), vUp.getX(), -forward.getX(),
                        side.getY(), vUp.getY(), -forward.getY(),
                        side.getZ(), vUp.getZ(), -forward.getZ()};
        }

        #pragma endregion //! static attribut

        #pragma region accessor
        #pragma endregion //!accessor

        #pragma region mutator
        #pragma endregion //!mutator

        #pragma region operator
        #pragma endregion //!operator

        #pragma region convertor
        #pragma endregion //!convertor

    };


    template <typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3          = Matrix3<TType, TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3f      = Matrix3<float, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3f         = Matrix3f<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3d      = Matrix3<double, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3d         = Matrix3d<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3ld     = Matrix3<long double, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3ld        = Matrix3ld<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3uc     = Matrix3<unsigned char, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3uc        = Matrix3uc<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3c      = Matrix3<char, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3c         = Matrix3c<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3ui     = Matrix3<unsigned int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3ui        = Matrix3ui<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3i      = Matrix3<int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3i         = Matrix3i<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3lui    = Matrix3<long unsigned int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3lui       = Matrix3lui<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3st     = Matrix3<size_t, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3st        = Matrix3st<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3li     = Matrix3<long int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3li        = Matrix3li<TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix3b      = Matrix3<bool, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat3b         = Matrix3b<TMatrixConvention>;

} /*namespace FoxMath::Matrix*/
