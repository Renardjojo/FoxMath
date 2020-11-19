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
Quaternion<TType>::Quaternion (const Vector::Vector3<TType>& axis, Angle::Angle<Angle::EAngleType::Radian, TType> angle) noexcept
    :   m_angle (angle),
        m_axis  (axis)
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
    return std::abs(getSquaredMagnitude() - static_cast<TType>(1)) < epsilon * epsilon;
}

template <typename TType>
inline constexpr
Quaternion<TType>& Quaternion<TType>::normalize() noexcept
{
    const TType magnitude = getMagnitude();
    m_x /= magnitude;
    m_y /= magnitude;
    m_z /= magnitude;
    m_w /= magnitude;
    return *this;
}

template <typename TType>
template <typename TTypeOther>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator+=(const Quaternion<TTypeOther>& other) noexcept
{
    m_angle += other.getAngle();
    m_axis  += other.getAxis();
    return *this;
}


template <typename TType>
template <typename TTypeOther>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator-=(const Quaternion<TTypeOther>& other) noexcept
{
    m_angle -= other.getAngle();
    m_axis  -= other.getAxis();
    return *this;
}

template <typename TType>
template <typename TTypeOther>
inline constexpr
Quaternion<TType>& Quaternion<TType>::operator*=(const Quaternion<TTypeOther>& other) noexcept
{
    Angle::Angle<Angle::EAngleType::Radian, TType> angleTemp = m_angle * other.getAngle() - Angle::Angle<Angle::EAngleType::Radian, TType>(Vector::Vector3<TType>::dot(m_axis, other.getAxis()));
    m_axis  =   static_cast<TType>(m_angle) * other.getAxis() +
                static_cast<TType>(other.getAngle()) * m_axis +
                Vector::Vector3<TType>::cross(m_axis, other.getAxis());
    
    m_angle = std::move(angleTemp);
    
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
    return Quaternion<TType>(-quat.getAxis(), -quat.getAngle());
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


template <typename TType>
inline constexpr
std::ostream& 	operator<<		(std::ostream& out, const Quaternion<TType>& quaternion) noexcept
{
    out << quaternion.getAngle() << ' ' << quaternion.getAxis();

    return out;  
}

template <typename TType>
inline constexpr
std::istream& 	operator>>		(std::istream& in, const Quaternion<TType>& quaternion) noexcept
{
    in >> quaternion.getAngle() >> ' ' >> quaternion.getAxis();

    return in;  
}