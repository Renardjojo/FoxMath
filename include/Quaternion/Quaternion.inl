/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-11 - 10 h 38
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

template <typename TType>
inline constexpr
Quaternion<TType>::Quaternion (Vector::Vector3<TType> axis, Angle::Angle<Angle::EAngleType::Radian, TType> angle) noexcept
{
    const TType halfAngle    = static_cast<TType>(angle) / static_cast<TType>(2);
    const TType halfSinAngle = std::sin(halfAngle);
    const TType halfCosAngle = std::cos(halfAngle);

    axis.normalize();

    m_data = {halfSinAngle * axis.getX(), halfSinAngle * axis.getY(), halfSinAngle * axis.getZ(), halfCosAngle};
}

template <typename TType>
inline constexpr
Quaternion<TType>::Quaternion (TType x, TType y, TType z, TType w) noexcept
    :   m_data  {x, y, z, w}
{}

template <typename TType>
inline constexpr
TType Quaternion<TType>::getSquaredMagnitude() const noexcept
{
    return m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;
}

template <typename TType>
inline constexpr
TType Quaternion<TType>::getMagnitude() const noexcept
{
    return std::sqrt(getSquaredMagnitude());
}

template <typename TType>
inline constexpr
bool Quaternion<TType>::isRotation(TType epsilon) const noexcept
{
    return std::abs(getSquaredMagnitude() - static_cast<TType>(1)) <= epsilon;
}

template <typename TType>
inline constexpr
Quaternion<TType>& Quaternion<TType>::normalize() noexcept
{
    const TType magnitude = getMagnitude();
    m_xyz /= magnitude;
    m_w /= magnitude;
    return *this;
}

template <typename TType>
inline constexpr
Quaternion<TType> Quaternion<TType>::getNormalize() const noexcept
{
    Quaternion<TType> rst (*this);
    rst.normalize();
    return rst;
}

template <typename TType>
inline constexpr
Quaternion<TType>& Quaternion<TType>::conjugate() noexcept
{
    m_xyz = -m_xyz;
    return *this;
}

template <typename TType>
inline constexpr
Quaternion<TType> Quaternion<TType>::getConjugate() const noexcept
{
    Quaternion<TType> rst (*this);
    rst.conjugate();
    return rst;
}

template <typename TType>
inline constexpr
Quaternion<TType>& Quaternion<TType>::inverse() noexcept
{
    *this = conjugate() / getSquaredMagnitude();
    return *this;
}

template <typename TType>
inline constexpr
Quaternion<TType> Quaternion<TType>::getInverse() const noexcept
{
    Quaternion<TType> rst (*this);
    rst.inverse();
    return rst;
}

template <typename TType>
inline constexpr
Angle::Angle<Angle::EAngleType::Radian, TType> Quaternion<TType>::getAngle() const noexcept
{
    return Angle::Angle<Angle::EAngleType::Radian, TType>(std::acos(m_w) * static_cast<TType>(2));
}


template <typename TType>
inline constexpr
Vector::Vector3<TType> Quaternion<TType>::getAxis() const noexcept
{
    return m_xyz / (std::sin(static_cast<TType>(getAngle()) / static_cast<TType>(2)));
}

template <typename TType>
template <Matrix::EMatrixConvention TMatrixConvention = Matrix::EMatrixConvention::RowMajor>
[[nodiscard]] inline constexpr
Matrix::Matrix3<TType, TMatrixConvention> Quaternion<TType>::getRotationMatrix() const noexcept
{
    const TType one = static_cast<TType>(1); 
    const TType two = static_cast<TType>(2);
    const TType twoX = two * m_x;
    const TType twoY = two * m_y;
    const TType twoZ = two * m_z;
    const TType twoXX = twoX * m_x;
    const TType twoXY = twoX * m_y;
    const TType twoXZ = twoX * m_z;
    const TType twoXW = twoX * m_w;
    const TType twoYY = twoY * m_y;
    const TType twoYZ = twoY * m_z;
    const TType twoYW = twoY * m_w;
    const TType twoZZ = twoZ * m_z;
    const TType twoZW = twoZ * m_w;

    const Vector::Vector3<TType> vec1 (one - twoYY - twoZZ, twoXY + twoZW, twoXZ - twoYW);
    const Vector::Vector3<TType> vec2 (twoXY - twoZW, one - twoXX - twoZZ, twoYZ + twoXW);
    const Vector::Vector3<TType> vec3 (twoXZ + twoYW, twoYZ - twoXW, one - twoXX - twoYY);

    Matrix::Mat3<TType, TMatrixConvention> rst ({vec1, vec2, vec3});
    return rst / getSquaredMagnitude();
}

template <typename TType>
inline constexpr
TType Quaternion<TType>::dot(const Quaternion<TType>& other) const noexcept
{
    return m_w * other.getW() + m_x * other.getX() + m_y * other.getY() + m_z * other.getZ(); 
}

template <typename TType>
template <typename TTypeVector>
inline constexpr
void Quaternion<TType>::RotateVector(Vector::Vector3<TTypeVector>& vec) const noexcept
{
    //Rodrigues formula with quaternion is better than quat * vec * quat.getInverse()
    TType angle = static_cast<TType>(getAngle());
    Vector::Vector3<TType> unitAxis = getAxis();

    const TType cosAngle = std::cos(static_cast<TType>(angle));
    vec = cosAngle * vec + (static_cast<TType>(1) - cosAngle) * vec.dot(unitAxis) * unitAxis + std::sin(static_cast<TType>(angle)) * unitAxis.getCross(vec);
}

template <typename TType>
template <typename TTypeVector>
inline constexpr
void Quaternion<TType>::GlobalRotateVector(const Quaternion<TType>& otherQuat, Vector::Vector3<TTypeVector>& vec) const noexcept
{
    const Quaternion<TType> q1q2 = (*this) * otherQuat;
    vec = (q1q2 * vec * q1q2.getInverse()).getXYZ();
}

template <typename TType>
template <typename TTypeVector>
inline constexpr
void Quaternion<TType>::LocalRotateVector(const Quaternion<TType>& otherQuat, Vector::Vector3<TTypeVector>& vec) const noexcept
{
    const Quaternion<TType> q2q1 = otherQuat * (*this);
    vec = (q2q1 * vec * q2q1.getInverse()).getXYZ();
}

template <typename TType>
[[nodiscard]] inline constexpr
Quaternion<TType> Quaternion<TType>::getGlobalSmallestDiffenceWithOther(const Quaternion<TType>& otherQuat) const noexcept
{
    return otherQuat * getInverse();
}

template <typename TType>
[[nodiscard]] inline constexpr
Quaternion<TType> Quaternion<TType>::getLocalSmallestDiffenceWithOther(const Quaternion<TType>& otherQuat) const noexcept
{
    return getInverse() * otherQuat;
}

template <typename TType>
template <bool TShortestPath, bool TClampedRatio>
inline constexpr
void Quaternion<TType>::sLerp(const Quaternion<TType>& startQuat, const Quaternion<TType>& endQuat, TType t) noexcept
{
    if constexpr (TShortestPath)
        t = std::clamp<TType>(t, static_cast<TType>(0), static_cast<TType>(0));

    const TType angle = std::acos(startQuat.dot(endQuat));
    TType conjugateT = static_cast<TType>(1) - t;

    /*if constexpr (TShortestPath)
    {
        conjugateT *=(startQuat.dot(endQuat) < static_cast<TType>(0) ? -static_cast<TType>(1) : static_cast<TType>(1);
    }*/

    *this = (startQuat * std::sin(conjugateT * angle) + endQuat * std::sin(t * angle)) / std::sin(angle);
}

template <typename TType>
template <bool TShortestPath, bool TClampedRatio>
inline constexpr
void Quaternion<TType>::lerp(const Quaternion<TType>& startQuat, const Quaternion<TType>& endQuat, TType t) noexcept
{
    if constexpr (TShortestPath)
        t = std::clamp<TType>(t, static_cast<TType>(0), static_cast<TType>(0));

    TType conjugateT = static_cast<TType>(1) - t;

    if constexpr (TShortestPath)
        conjugateT *= startQuat.dot(endQuat) < static_cast<TType>(0) ? -static_cast<TType>(1) : static_cast<TType>(1);

    *this = conjugateT * startQuat + t * endQuat;
}

template <typename TType>
template <typename TTypeOther>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator+=(const Quaternion<TTypeOther>& other) noexcept
{
    m_xyz   += other.getXYZ();
    m_w     += other.getW();
    return *this;
}


template <typename TType>
template <typename TTypeOther>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator-=(const Quaternion<TTypeOther>& other) noexcept
{
    m_xyz   -= other.getXYZ();
    m_w     -= other.getW();
    return *this;
}

template <typename TType>
template <typename TTypeOther>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator*=(const Quaternion<TTypeOther>& other) noexcept
{
    TType WTemp = m_w * other.getW() - Vector::Vector3<TType>::dot(m_xyz, other.getXYZ());
    m_xyz  =   static_cast<TType>(m_w) * other.getXYZ() +
                static_cast<TType>(other.getW()) * m_xyz +
                Vector::Vector3<TType>::cross(m_xyz, other.getXYZ());
    
    m_w = std::move(WTemp);
    
    return *this;
}

template <typename TType>
template <typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator*=(TTypeScalar scalar) noexcept
{
    m_xyz   *= static_cast<TType>(scalar);
    m_w     *= static_cast<TType>(scalar);
    return *this;
}

template <typename TType>
template <typename TTypeVector, Type::IsArithmetic<TTypeVector> = true>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator*=(Vector::Vector3<TTypeVector> vec) noexcept
{
    TType WTemp = -Vector::Vector3<TType>::dot(m_xyz, vec);
    m_xyz  =   static_cast<TType>(m_w) * vec +
                Vector::Vector3<TType>::cross(m_xyz, vec);
    
    m_w = std::move(WTemp);
    
    return *this;
}

template <typename TType>
template <typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator/=(TTypeScalar scalar) noexcept
{
    m_xyz   /= static_cast<TType>(scalar);
    m_w     /= static_cast<TType>(scalar);
    return *this;
}

template <typename TType>
inline constexpr
Quaternion<TType> operator+(const Quaternion<TType>& quat) noexcept
{
    return quat;
}

template <typename TType>
inline constexpr
Quaternion<TType> operator-(const Quaternion<TType>& quat) noexcept
{
    return Quaternion<TType>(-quat.GetX(), -quat.GetY(), -quat.GetZ(), -quat.GetW());
}

template <typename TType, typename TTypeOther>
inline constexpr
Quaternion<TType> operator+(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept
{
    return lhs += rhs;
}

template <typename TType, typename TTypeOther>
inline constexpr
Quaternion<TType> operator-(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept
{
    return lhs -= rhs;
}

template <typename TType, typename TTypeOther>
inline constexpr
Quaternion<TType> operator*(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept
{
    return lhs *= rhs;
}
   
template <typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Quaternion<TType> operator*(Quaternion<TType> quat, TTypeScalar scalar) noexcept
{
    return quat *= static_cast<TType>(scalar);
}

template <typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Quaternion<TType> operator*(TTypeScalar scalar, Quaternion<TType> quat) noexcept
{
    return quat *= static_cast<TType>(scalar);
}

template <typename TType, typename TTypeVector, Type::IsArithmetic<TTypeVector> = true>
inline constexpr
Quaternion<TType> operator*(Quaternion<TType> quat, const Vector::Vector3<TTypeVector>& vec) noexcept
{
    return quat *= vec;
}

template <typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Quaternion<TType> operator/(Quaternion<TType> quat, TTypeScalar scalar) noexcept
{
    return quat /= static_cast<TType>(scalar);
}

template <typename TType>
inline constexpr
std::ostream& 	operator<<		(std::ostream& out, const Quaternion<TType>& quaternion) noexcept
{
    out << quaternion.getW() << ' ' << quaternion.getX() << ' ' << quaternion.getY() << ' ' << quaternion.getZ();

    return out;  
}