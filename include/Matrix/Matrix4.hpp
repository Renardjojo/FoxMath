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
    template <typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
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

        /**
         * @brief Create rotation on X axis only
         * 
         * @param rotRadz 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline 
        Matrix4 createXRotationMatrix		(Angle::Angle<Angle::EAngleType::Radian, TType> rotRadx) //rot of axis Y to axis Z arround X
        {
            const TType cosT = std::cos(static_cast<TType>(rotRadx));
            const TType sinT = std::sin(static_cast<TType>(rotRadx));
            const TType zero  = static_cast<TType>(0);
            const TType one  = static_cast<TType>(1);

            return Matrix4 {    one, zero , zero , zero,
                                zero, cosT,-sinT, zero,
                                zero, sinT, cosT, zero,
                                zero, zero , zero , one};
        }

        /**
         * @brief Create rotation on Y axis only
         * 
         * @param rotRadz 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline 
        Matrix4 createYRotationMatrix		(Angle::Angle<Angle::EAngleType::Radian, TType> rotRady) //rot of axis Z to axis X arround Y
        {
            const TType cosT = std::cos(static_cast<TType>(rotRady));
            const TType sinT = std::sin(static_cast<TType>(rotRady));
            const TType zero  = static_cast<TType>(0);
            const TType one  = static_cast<TType>(1);

            return Matrix4{     cosT , zero, sinT, zero,
                                zero  , one, zero , zero,
                                -sinT, zero, cosT, zero,
                                zero  , zero, zero , one};
        }

        /**
         * @brief Create rotation on Z axis only
         * 
         * @param rotRadz 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline 
        Matrix4 createZRotationMatrix		(Angle::Angle<Angle::EAngleType::Radian, TType> rotRadz) //rot of axis X to axis Y arround Z
        {
            const TType cosT = std::cos(static_cast<TType>(rotRadz));
            const TType sinT = std::sin(static_cast<TType>(rotRadz));
            const TType zero  = static_cast<TType>(0);
            const TType one  = static_cast<TType>(1);

            return Matrix4{ cosT, -sinT, zero, zero,
                            sinT,  cosT, zero, zero,
                            zero ,  zero , one, zero,
                            zero ,  zero , zero, one};
        }

        /**
         * @brief Create a Fixed Angle Euler Rotation Matrix object
         * 
         * @param rVec 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline //TODO: Transform (space an right and and left hand referential!)
        Matrix4 createFixedAngleEulerRotationMatrix	(const Vector::Vec3<TType>& rVec)
        {
            const TType cosTX = std::cos(static_cast<TType>(rVec.getX()));
            const TType sinTX = std::sin(static_cast<TType>(rVec.getX()));
            const TType cosTY = std::cos(static_cast<TType>(rVec.getY()));
            const TType sinTY = std::sin(static_cast<TType>(rVec.getY()));
            const TType cosTZ = std::cos(static_cast<TType>(rVec.getZ()));
            const TType sinTZ = std::sin(static_cast<TType>(rVec.getZ()));
            const TType zero  = static_cast<TType>(0);
            const TType one  = static_cast<TType>(1);

            /*Right hand convention*/
            const TType r1 = cosTY * cosTZ;
            const TType r2 = -cosTX * sinTZ + sinTX * sinTY * cosTZ;
            const TType r3 = sinTX * sinTZ + cosTX * sinTY * cosTZ ;
            const TType r4 = cosTY * sinTZ;
            const TType r5 = cosTX * cosTZ + sinTX * sinTY * sinTZ;
            const TType r6 = -sinTX * cosTZ + cosTX * sinTY * sinTZ;
            const TType r7 = -sinTY;
            const TType r8 = sinTX * cosTY;
            const TType r9 = cosTX * cosTY;

            return Matrix4{ r1,   r2,   r3,   zero,
                            r4,   r5,   r6,   zero,
                            r7,   r8,   r9,   zero,
                            zero, zero, zero, one};
        }

        /**
         * @brief Create TRS matrix based on translation/rotation/Scale step. This matrix is differente than SRT
         * 
         * @param translVec 
         * @param rotVec 
         * @param scaleVec 
         * @return constexpr Matrix4 
         */
        [[nodiscard]] static constexpr inline
        Matrix4 createTRSMatrix(const Vector::Vec3<TType>& translVec, const Vector::Vec3<TType>& rotVec, const Vector::Vec3<TType>& scaleVec)
        {
            if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
            {
                const TType cosTX = std::cos(static_cast<TType>(rotVec.getX()));
                const TType cosTY = std::cos(static_cast<TType>(rotVec.getY()));
                const TType cosTZ = std::cos(static_cast<TType>(rotVec.getZ()));

                const TType sinTX = std::sin(static_cast<TType>(rotVec.getX()));
                const TType sinTY = std::sin(static_cast<TType>(rotVec.getY()));
                const TType sinTZ = std::sin(static_cast<TType>(rotVec.getZ()));

                const TType zero  = static_cast<TType>(0);
                const TType one  = static_cast<TType>(1);

                const TType sxR1 = cosTY * cosTZ * scaleVec.getX();
                const TType sxR2 = (-cosTX * sinTZ + sinTX * sinTY * cosTZ) * scaleVec.getX();
                const TType sxR3 = (sinTX * sinTZ + cosTX * sinTY * cosTZ) * scaleVec.getX();
                const TType syR4 = cosTY * sinTZ * scaleVec.getY();
                const TType syR5 = (cosTX * cosTZ + sinTX * sinTY * sinTZ) * scaleVec.getY();
                const TType syR6 = (-sinTX * cosTZ + cosTX * sinTY * sinTZ) * scaleVec.getY();
                const TType szR7 = -sinTY * scaleVec.getZ();
                const TType szR8 = sinTX * cosTY * scaleVec.getZ();
                const TType szR9 = cosTX * cosTY * scaleVec.getZ();

                const TType tx = translVec.getX() * sxR1 + translVec.getY() * sxR2 + translVec.getZ() * sxR3;
                const TType ty = translVec.getX() * syR4 + translVec.getY() * syR5 + translVec.getZ() * syR6;
                const TType tz = translVec.getX() * szR7 + translVec.getY() * szR8 + translVec.getZ() * szR9;

                return Matrix4{ sxR1, sxR2, sxR3, tx,
                                syR4, syR5, syR6, ty,
                                szR7, szR8, szR9, tz,
                                zero, zero, zero, one};
            }
            else
            {
                const TType cosTX = std::cos(static_cast<TType>(rotVec.getX()));
                const TType cosTY = std::cos(static_cast<TType>(rotVec.getY()));
                const TType cosTZ = std::cos(static_cast<TType>(rotVec.getZ()));

                const TType sinTX = std::sin(static_cast<TType>(rotVec.getX()));
                const TType sinTY = std::sin(static_cast<TType>(rotVec.getY()));
                const TType sinTZ = std::sin(static_cast<TType>(rotVec.getZ()));

                const TType zero  = static_cast<TType>(0);
                const TType one  = static_cast<TType>(1);

                const TType r1 = cosTY * cosTZ;
                const TType r2 = -cosTX * sinTZ + sinTX * sinTY * cosTZ;
                const TType r3 = sinTX * sinTZ + cosTX * sinTY * cosTZ ;
                const TType r4 = cosTY * sinTZ;
                const TType r5 = cosTX * cosTZ + sinTX * sinTY * sinTZ;
                const TType r6 = -sinTX * cosTZ + cosTX * sinTY * sinTZ;
                const TType r7 = -sinTY;
                const TType r8 = sinTX * cosTY;
                const TType r9 = cosTX * cosTY;

                return Matrix4{ r1 * scaleVec.getX(), r2 * scaleVec.getY(), r3 * scaleVec.getZ(), translVec.getX(),
                                r4 * scaleVec.getX(), r5 * scaleVec.getY(), r6 * scaleVec.getZ(), translVec.getY(),
                                r7 * scaleVec.getX(), r8 * scaleVec.getY(), r9 * scaleVec.getZ(), translVec.getZ(),
                                zero                , zero                , zero                , one};
            }
        }

        [[nodiscard]] static constexpr inline
        Matrix4 createSRTMatrix(const Vector::Vec3<TType>& scaleVec, const Vector::Vec3<TType>& rotVec, const Vector::Vec3<TType>& translVec)
        {
            if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
            {
                const TType cosTX = std::cos(static_cast<TType>(rotVec.getX()));
                const TType cosTY = std::cos(static_cast<TType>(rotVec.getY()));
                const TType cosTZ = std::cos(static_cast<TType>(rotVec.getZ()));

                const TType sinTX = std::sin(static_cast<TType>(rotVec.getX()));
                const TType sinTY = std::sin(static_cast<TType>(rotVec.getY()));
                const TType sinTZ = std::sin(static_cast<TType>(rotVec.getZ()));

                const TType zero  = static_cast<TType>(0);
                const TType one  = static_cast<TType>(1);

                const TType r1 = cosTY * cosTZ;
                const TType r2 = -cosTX * sinTZ + sinTX * sinTY * cosTZ;
                const TType r3 = sinTX * sinTZ + cosTX * sinTY * cosTZ ;
                const TType r4 = cosTY * sinTZ;
                const TType r5 = cosTX * cosTZ + sinTX * sinTY * sinTZ;
                const TType r6 = -sinTX * cosTZ + cosTX * sinTY * sinTZ;
                const TType r7 = -sinTY;
                const TType r8 = sinTX * cosTY;
                const TType r9 = cosTX * cosTY;

                return Matrix4{ r1 * scaleVec.getX(), r2 * scaleVec.getY(), r3 * scaleVec.getZ(), translVec.getX(),
                                r4 * scaleVec.getX(), r5 * scaleVec.getY(), r6 * scaleVec.getZ(), translVec.getY(),
                                r7 * scaleVec.getX(), r8 * scaleVec.getY(), r9 * scaleVec.getZ(), translVec.getZ(),
                                zero                , zero                , zero                , one};
            }
            else
            {
                const TType cosTX = std::cos(static_cast<TType>(rotVec.getX()));
                const TType cosTY = std::cos(static_cast<TType>(rotVec.getY()));
                const TType cosTZ = std::cos(static_cast<TType>(rotVec.getZ()));

                const TType sinTX = std::sin(static_cast<TType>(rotVec.getX()));
                const TType sinTY = std::sin(static_cast<TType>(rotVec.getY()));
                const TType sinTZ = std::sin(static_cast<TType>(rotVec.getZ()));

                const TType zero  = static_cast<TType>(0);
                const TType one  = static_cast<TType>(1);

                const TType sxR1 = cosTY * cosTZ * scaleVec.getX();
                const TType sxR2 = (-cosTX * sinTZ + sinTX * sinTY * cosTZ) * scaleVec.getX();
                const TType sxR3 = (sinTX * sinTZ + cosTX * sinTY * cosTZ) * scaleVec.getX();
                const TType syR4 = cosTY * sinTZ * scaleVec.getY();
                const TType syR5 = (cosTX * cosTZ + sinTX * sinTY * sinTZ) * scaleVec.getY();
                const TType syR6 = (-sinTX * cosTZ + cosTX * sinTY * sinTZ) * scaleVec.getY();
                const TType szR7 = -sinTY * scaleVec.getZ();
                const TType szR8 = sinTX * cosTY * scaleVec.getZ();
                const TType szR9 = cosTX * cosTY * scaleVec.getZ();

                const TType tx = translVec.getX() * sxR1 + translVec.getY() * sxR2 + translVec.getZ() * sxR3;
                const TType ty = translVec.getX() * syR4 + translVec.getY() * syR5 + translVec.getZ() * syR6;
                const TType tz = translVec.getX() * szR7 + translVec.getY() * szR8 + translVec.getZ() * szR9;

                return Matrix4{ sxR1, sxR2, sxR3, tx,
                                syR4, syR5, syR6, ty,
                                szR7, szR8, szR9, tz,
                                zero, zero, zero, one};
            }
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


    template <typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4          = Matrix4<TType, TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4f      = Matrix4<float, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4f         = Matrix4f<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4d      = Matrix4<double, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4d         = Matrix4d<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4ld     = Matrix4<long double, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4ld        = Matrix4ld<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4uc     = Matrix4<unsigned char, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4uc        = Matrix4uc<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4c      = Matrix4<char, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4c         = Matrix4c<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4ui     = Matrix4<unsigned int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4ui        = Matrix4ui<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4i      = Matrix4<int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4i         = Matrix4i<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4lui    = Matrix4<long unsigned int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4lui       = Matrix4lui<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4st     = Matrix4<size_t, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4st        = Matrix4st<TMatrixConvention>;

    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4li     = Matrix4<long int, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4li        = Matrix4li<TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Matrix4b      = Matrix4<bool, TMatrixConvention>;
    
    template <EMatrixConvention TMatrixConvention = EMatrixConvention::RowMajor>
    using Mat4b         = Matrix4b<TMatrixConvention>;

} /*namespace FoxMath::Matrix*/
