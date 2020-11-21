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
Quaternion<TType>& Quaternion<TType>::conjugate() noexcept
{
    m_xyz = -m_xyz;
    return *this;
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
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator*=(TType scalar) noexcept
{
    m_xyz   *= scalar;
    m_w     *= scalar;
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

template <typename TType>
inline constexpr
std::ostream& 	operator<<		(std::ostream& out, const Quaternion<TType>& quaternion) noexcept
{
    out << "x = " << quaternion.getX() << " | y = " << quaternion.getY() << " | z = " << quaternion.getZ() << " | w = " << quaternion.getW();

    return out;  
}