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


template <EAngleType TAngleType, typename TType>
template<typename TTypeScalar, Type::IsArithmetic<TType> = true>
inline constexpr
Angle<TAngleType, TType>::Angle (TTypeScalar angle) noexcept
    : m_angle {static_cast<TType>(angle)}
{}

template <EAngleType TAngleType, typename TType>
inline constexpr
Angle<EAngleType::Degres, TType> Angle<TAngleType, TType>::convertFromRadianToDegres() const noexcept
{
    return Angle<EAngleType::Radian, TType>(m_angle * static_cast<TType>(180) / static_cast<TType>(3.14159265358979323846264L));
}

template <EAngleType TAngleType, typename TType>
inline constexpr
Angle<EAngleType::Radian, TType> Angle<TAngleType, TType>::convertFromDegresToRadian() const noexcept
{
    return Angle<EAngleType::Degres, TType>(m_angle * static_cast<TType>(3.14159265358979323846264L) / static_cast<TType>(180));
}

template <EAngleType TAngleType, typename TType>
inline constexpr
Angle<EAngleType::Degres, TType> Angle<TAngleType, TType>::toDegres() const noexcept
{
    if constexpr (TAngleType == EAngleType::Degres)
        return m_angle;

    return  convertFromRadianToDegres();
}

template <EAngleType TAngleType, typename TType>
inline constexpr
Angle<EAngleType::Radian, TType> Angle<TAngleType, TType>::toRadian() const noexcept
{
    if constexpr (TAngleType == EAngleType::Radian)
        return m_angle;
        
    return  convertFromDegresToRadian();
}

template <EAngleType TAngleType, typename TType>
inline constexpr
const TType& Angle<TAngleType, TType>::getAngle() const noexcept
{
    return m_angle;
}

template <EAngleType TAngleType, typename TType>
inline constexpr
EAngleType Angle<TAngleType, TType>::getType() const noexcept
{
    return TAngleType;
}

template <EAngleType TAngleType, typename TType>
template<typename TTypeScalar, Type::IsArithmetic<TType> = true>
inline constexpr
Angle<EAngleType::Degres, TType>& Angle<TAngleType, TType>::setAngle(TTypeScalar newAngle) noexcept
{
    m_angle = newAngle;
    return *this;
}

inline constexpr
Angle<EAngleType::Degres, float> operator"" _deg(long double angleDeg) noexcept
{
    return Angle<EAngleType::Degres, float>(angleDeg);
}

inline constexpr
Angle<EAngleType::Degres, float> operator"" _deg(unsigned long long int      angleDeg) noexcept
{
    return Angle<EAngleType::Degres, float>(angleDeg);
}

inline constexpr
Angle<EAngleType::Radian, float> operator"" _rad(long double angleRad) noexcept
{
    return Angle<EAngleType::Radian, float>(angleRad);
}

inline constexpr
Angle<EAngleType::Radian, float> operator"" _rad(unsigned long long int      angleRad) noexcept
{
    return Angle<EAngleType::Radian, float>(angleRad);
};

template <EAngleType TAngleType, typename TType>
inline constexpr
std::ostream& 	operator<<		(std::ostream& out, const Angle<TAngleType, TType>& angle) noexcept
{
    out << angle.getAngle() << ' ' << angleTypeToString(angle.getType());

    return out;  
}

template <EAngleType TAngleType, typename TType>
inline constexpr
std::istream& 	operator>>		(std::istream& in, const Angle<TAngleType, TType>& angle) noexcept
{
        in >> angle.getAngle() >> ' ' >> angleTypeToString(angle.getType());

    return in;  
}