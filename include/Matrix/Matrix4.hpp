/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-25 - 20 h 26
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
#include "Angle/Angle.hpp"

namespace FoxMath::Matrix
{
    template <typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    class Matrix4 :  public SquareMatrix<4, TType, TMatrixConvention>
    {
        private:

        using Parent = SquareMatrix<4, TType, TMatrixConvention>;

        protected:

        #pragma region attribut
        #pragma endregion //!attribut

        #pragma region methods
        #pragma endregion //!methods

        public:

        #pragma region constructor/destructor

        constexpr inline
        Matrix4 () noexcept 					                = default;

        constexpr inline
        Matrix4 (const Matrix4& other) noexcept			        = default;

        constexpr inline
        Matrix4 (Matrix4&& other) noexcept				        = default;

        inline
        ~Matrix4 () noexcept				                    = default;

        constexpr inline
        Matrix4& operator=(Matrix4 const& other) noexcept		= default;

        constexpr inline
        Matrix4& operator=(Matrix4 && other) noexcept			= default;

        DECLARE_CROSS_INHERITANCE_COMPATIBILTY(Matrix4, Parent, SquareMatrix)

        #pragma endregion //!constructor/destructor

        #pragma region methods
        #pragma endregion //!methods

        #pragma region static methods

        /**
         * @brief Create a Look At View objectreates a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an UP vector.
         * 
         * @note translation is apply 
         * 
         * @param from : Specifies the position of the from point.
         * @param to : Specifies the position of the reference point.
         * @param up : Specifies the direction of the up vector. 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline
        Matrix4 createLookAtView (const Vector::Vec3<TType> & from, const Vector::Vec3<TType> & to, const Vector::Vec3<TType> & up) noexcept
        {
            const Vector::Vec3<TType>   forward ((to - from).getNormalized());
            const Vector::Vec3<TType>   side    (forward.getCross(up).getNormalized());
            const Vector::Vec3<TType>   vUp     (side.getCross(forward));
            const TType                 zero    {static_cast<TType>(0)};
            const TType                 one     {static_cast<TType>(1)};

            return Matrix4( side.getX() , vUp.getX() , -forward.getX()	, -side.dot(from),
                            side.getY() , vUp.getY() , -forward.getY()	, -vUp.dot(from),
                            side.getZ() , vUp.getZ() , -forward.getZ()	, forward.dot(from),
                            zero	    , zero       ,  zero		    , one);
        }

        /**
         * @brief Create a Ortho Matrix object. This matrix correspond to an orthographic camera. Parameter define the camera's frustum
         * 
         * @param left 
         * @param right
         * @param bottom 
         * @param top 
         * @param nearVal 
         * @param farVal 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline
        Matrix4 createOrthoMatrix	(TType left, TType right, TType bottom, TType top, TType nearVal, TType farVal) noexcept
        {
            const TType zero    {static_cast<TType>(0)};
            const TType one     {static_cast<TType>(1)};
            const TType two     {static_cast<TType>(2)};

            const TType a11 = two / (right - left);
            const TType a22 = two / (top - bottom);
            const TType a33 = -two / (farVal - nearVal);

            const TType tx = (right + left) / (right - left);
            const TType ty = (top + bottom) / (top - bottom);  
            const TType tz = (farVal + nearVal)/ (farVal - nearVal);

            return Matrix4 (    a11,    zero,   zero,   tx,
                                zero,   a22,    zero,   ty,
                                zero,   zero,   a33,    tz,
                                zero,   zero,   zero,   one);
        }

        /**
         * @brief Create a Perspective Matrix object. This matrix correspond to an perspective camera. Parameter define the camera's frustum
         * 
         * @param aspect 
         * @param near 
         * @param far 
         * @param fov 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline
        Matrix4 createPerspectiveMatrix 	(TType aspect, TType near, TType far, Angle::Angle<Angle::EAngleType::Radian, TType> fov) noexcept
        {
            const TType zero    {static_cast<TType>(0)};
            const TType one     {static_cast<TType>(1)};
            const TType two     {static_cast<TType>(2)};

            const TType scale = std::tan(static_cast<TType>(fov) / two) * near;
            const TType rigth = aspect * scale;

            const TType left   = -rigth;
            const TType top    = scale;
            const TType bottom = -scale;

            const TType a11 = two * near / (rigth - left);
            const TType a22 = two * near / (top - bottom);
            const TType a31 = (rigth + left) / (rigth - left);
            const TType a32 = (top + bottom) / (top - bottom);
            const TType a33 = -(far + near) / (far - near);
            const TType a43 = -two * far * near / (far - near);
            const TType zDir = -one;


            return Matrix4( a11,    zero,   zero,   zero,
                            zero,   a22,    zero,   zero,
                            a31,    a32,    a33,    a43,
                            zero,   zero,   zDir,   zero);
        }

        /**
         * @brief Create a Projection Matrix object. Create projection Mat4 to pass from 3D to 2D.
         * 
         * @param distance the distance between pin hole and user
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline
        Matrix4 createProjectionMatrix		(TType distance) noexcept
        {
            const TType zero    {static_cast<TType>(0)};
            const TType one     {static_cast<TType>(1)};
            const TType p       {one / distance};

            return Matrix4( one,    zero,   zero,   zero,
                            zero,   one,    zero,   zero,
                            zero,   zero,   one,    zero,
                            zero,   zero,   p  ,    zero);
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
    using Mat4          = Matrix4<TType, TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4f      = Matrix4<float, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4f         = Matrix4f<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4d      = Matrix4<double, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4d         = Matrix4d<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4ld     = Matrix4<long double, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4ld        = Matrix4ld<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4uc     = Matrix4<unsigned char, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4uc        = Matrix4uc<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4c      = Matrix4<char, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4c         = Matrix4c<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4ui     = Matrix4<unsigned int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4ui        = Matrix4ui<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4i      = Matrix4<int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4i         = Matrix4i<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4lui    = Matrix4<long unsigned int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4lui       = Matrix4lui<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4st     = Matrix4<size_t, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4st        = Matrix4st<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4li     = Matrix4<long int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4li        = Matrix4li<TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix4b      = Matrix4<bool, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat4b         = Matrix4b<TMatrixConvention>;

} /*namespace FoxMath::Matrix*/
