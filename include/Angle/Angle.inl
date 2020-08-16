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
    :   Type::StrongType <TType, AnglePhantom> {angle}
{}

template <EAngleType TAngleType, typename TType>
inline constexpr
Angle<EAngleType::Degree, TType> Angle<TAngleType, TType>::convertFromRadianToDegree() const noexcept
{
    return Angle<EAngleType::Degree, TType>(Base::m_value * static_cast<TType>(180) / static_cast<TType>(3.14159265358979323846264L));
}

template <EAngleType TAngleType, typename TType>
inline constexpr
Angle<EAngleType::Radian, TType> Angle<TAngleType, TType>::convertFromDegreeToRadian() const noexcept
{
    return Angle<EAngleType::Radian, TType>(Base::m_value * static_cast<TType>(3.14159265358979323846264L) / static_cast<TType>(180));
}

template <EAngleType TAngleType, typename TType>
inline constexpr
Angle<EAngleType::Degree, TType> Angle<TAngleType, TType>::toDegree() const noexcept
{
    if constexpr (TAngleType == EAngleType::Degree)
        return Base::m_value;

    return  convertFromRadianToDegree();
}

template <EAngleType TAngleType, typename TType>
inline constexpr
Angle<EAngleType::Radian, TType> Angle<TAngleType, TType>::toRadian() const noexcept
{
    if constexpr (TAngleType == EAngleType::Radian)
        return Base::m_value;
        
    return  convertFromDegreeToRadian();
}

template <EAngleType TAngleType, typename TType>
inline constexpr
const TType& Angle<TAngleType, TType>::getAngle() const noexcept
{
    return Base::m_value;
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
Angle<EAngleType::Degree, TType>& Angle<TAngleType, TType>::setAngle(TTypeScalar newAngle) noexcept
{
    Base::m_value = newAngle;
    return *this;
}

template <EAngleType TAngleType, typename TType>
template <typename TOtherType>
constexpr inline
Angle<TAngleType, TType>::operator Angle<EAngleType::Degree, TOtherType>() const noexcept
{
    return toDegree();
}

template <EAngleType TAngleType, typename TType>
template <typename TOtherType>
constexpr inline 
Angle<TAngleType, TType>::operator Angle<EAngleType::Radian, TOtherType>() const noexcept
{
    return toRadian();
}

inline constexpr
Angle<EAngleType::Degree, float> operator"" _deg(long double angleDeg) noexcept
{
    return Angle<EAngleType::Degree, float>(angleDeg);
}

inline constexpr
Angle<EAngleType::Degree, float> operator"" _deg(unsigned long long int      angleDeg) noexcept
{
    return Angle<EAngleType::Degree, float>(angleDeg);
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