/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-05 - 11 h 14
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

#include <cassert> //assert
#include <string.h> //memset

template <size_t TLength, typename TType>
Vector<TLength, TType>::Vector()
{
    std::memset(m_data, 0, sizeof(TType) * TLength);
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] = static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] = scalar;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
TType&  Vector<TLength, TType>::operator[]	(size_t index)
{
    assert(index >= 0 && index < TLength);
    return m_data[index];
}

template <size_t TLength, typename TType>
inline constexpr
const TType&    Vector<TLength, TType>::operator[]	(size_t index) const
{
    assert(index >= 0 && index < TLength);
    return m_data[index];
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator+=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] += static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator+=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] += static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator-=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] -= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator-=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] -= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator*=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] *= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator*=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] *= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator/=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] /= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator/=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] /= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator%=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] %= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator%=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] %= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator&=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] &= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator&=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] &= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator|=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] |= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator|=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] |= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator^=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] ^= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator^=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] ^= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator<<=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] <<= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator<<=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] <<= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TScaleType, Type::IsArithmetic<TScaleType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator>>=(TScaleType scalar)
{
    for (TType& i : m_data)
    {
        m_data[i] >>= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator>>=(const Vector<TLengthOther, TTypeOther>& other)
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] >>= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr 
Vector<TLength, TType>& 	Vector<TLength, TType>::operator++	()
{
    for (TType& i : m_data)
    {
        ++i;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>& 	Vector<TLength, TType>::operator--	()
{
    for (TType& i : m_data)
    {
        --i;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::operator++	(int)
{
	Vector<TLength, TType> result(*this);
	++*this;
	return result;
}


template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::operator--	(int)
{
	Vector<TLength, TType> result(*this);
	--*this;
	return result;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
constexpr inline explicit 
Vector<TLength, TType>::operator Vector<TLengthOther, TTypeOther>() const
{
    Vector<TLengthOther, TTypeOther> result;

    for (size_t i = 0; i < TLengthOther; i++)
    {
        if (i < TLength)
        {
            result[i] = static_cast<TTypeOther>(m_data[i]);
        }
        else
        {
            result[i] = static_cast<TTypeOther>(0);
        }   
    }

    return result;
}


template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator+(Vector<TLength, TType> const& vec)
{
    return vec
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator-(Vector<TLength, TType> vec)
{
    return vec *= static_cast<TType>(-1);
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator+(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec += scale; 
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator+(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) + vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator+(Vector<TLength, TType> vec1, Vector<TLengthOther, TTypeOther> const& vec2)
{
    return vec1 += vec2;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator-(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec -= scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator-(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) - vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator-(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 -= vec2;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator*(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec *= scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator*(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) * vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator*(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 *= vec2;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator/(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec /= scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator/(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) / vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator/(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 /= vec2;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator%(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec %= scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator%(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) % vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator%(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 %= vec2;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator&(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec &= scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator&(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) & vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator&(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 &= vec2;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator|(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec |= scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator|(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) | vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator|(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 |= vec2;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator^(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec ^= scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator^(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) ^ vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator^(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 ^= vec2;
}


template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator<<(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec << scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator<<(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) << vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator<<(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 << vec2;
}


template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator>>(Vector<TLength, TType> vec, TTypeScalar scalar)
{
    return vec >> scalar;
}

template <size_t TLength, typename TType>
template <typename TTypeScalar>
inline constexpr
Vector<TLength, TType> operator>>(TTypeScalar scalar, Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = static_cast<TType>(scalar) >> vec[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator>>(Vector<TLength, TType> vec1, Vector<TLength, TType> const& vec2)
{
    return vec1 >> vec2;
}


template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator~(Vector<TLength, TType> const& vec)
{
    Vector<TLength, TType> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = ~vec[i];
    }
    
    return result;
}

template <size_t TLength>
inline constexpr
Vector<TLength, bool> operator!(Vector<TLength, bool> const& vec)
{
    Vector<TLength, bool> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = !vec[i];
    }
    
    return result;
}

template <size_t TLength>
inline constexpr
Vector<TLength, bool> operator&&(Vector<TLength, bool> const& vec1, Vector<TLength, bool> const& vec2)
{
    Vector<TLength, bool> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = vec1[i] && vec2[i];
    }
    
    return result;
}

template <size_t TLength>
inline constexpr
Vector<TLength, bool> operator||(Vector<TLength, bool> const& vec1, Vector<TLength, bool> const& vec2)
{
    Vector<TLength, bool> result;

    for (size_t i = 0; i < TLength; i++)
    {
        result[i] = vec1[i] || vec2[i];
    }
    
    return result;
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator==(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator!=(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

/*Length comparision*/
template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator!=(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator!=(Vector<TLength, TType> const& vec, TTypeScalar scale);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator!=(TTypeScalar scale, Vector<TLength, TType> const& vec);

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator<(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator<(Vector<TLength, TType> const& vec, TTypeScalar scale);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator<(TTypeScalar scale, Vector<TLength, TType> const& vec);

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator>(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator>(Vector<TLength, TType> const& vec, TTypeScalar scale);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator>(TTypeScalar scale, Vector<TLength, TType> const& vec);

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator<=(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator<=(Vector<TLength, TType> const& vec, TTypeScalar scale);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator<=(TTypeScalar scale, Vector<TLength, TType> const& vec);

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator>=(Vector<TLength, TType> const& vec1, Vector<TLength, TType> const& vec2);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator>=(Vector<TLength, TType> const& vec, TTypeScalar scale);

template <size_t TLength, typename TType>
template <typename TTypeScalar>
[[nodiscard]] inline constexpr
bool operator>=(TTypeScalar scale, Vector<TLength, TType> const& vec);

template <size_t TLength, typename TType>
inline constexpr
std::ostream& 	operator<<		(std::ostream& out, const Vector<TLength, TType>& vec)
{
    for (size_t i = 0; i < TLength; i++)
    {
        out << vec[i] << "  ";
    }

    return out;  
}

template <size_t TLength, typename TType>
inline constexpr
std::istream& 	operator>>		(std::istream& in, const Vector<TLength, TType>& vec)
{
    for (size_t i = 0; i < TLength; i++)
    {
        in >> vec[i] >> "   ";
    }

    return in;  
}