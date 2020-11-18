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
    :   m_axis  (axis),
        m_angle (angle)
{}

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