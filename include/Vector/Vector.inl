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

template <size_t TLength, typename TType>
template<typename... T, Type::IsSame<Type::Pack<TType, T...>, Type::Pack<T..., TType>> = true>
constexpr inline 
Vector<TLength, TType>::Vector (T... args) noexcept
{
    static_assert(sizeof...(T) <= TLength, "Too many initializer for Vector");
    m_data = std::array<TType, TLength>{args...};
}

template <size_t TLength, typename TType>
template<size_t TLengthOther, typename... TScalarArgs, 
Type::IsSame<Type::Pack<TType, TScalarArgs...>, Type::Pack<TScalarArgs..., TType>> = true,
Type::IsLessThanOrEqualTo<sizeof...(TScalarArgs) + TLengthOther, TLength> = true,
Type::IsLessThan<TLengthOther, TLength> = true>
inline constexpr
Vector<TLength, TType>::Vector (const Vector<TLengthOther, TType>& other, TScalarArgs... args) noexcept
{
    /*Add vector*/
    for (size_t i = 0; i < TLengthOther; i++)
    {
        m_data[i] = other[i];
    }

    /*Add args*/
    auto arrayTemp = std::array<TType, sizeof...(TScalarArgs)>{args...};
    size_t indexArrayTemp = 0;

    for (size_t i = 0; i < sizeof...(TScalarArgs); i++)
    {
        m_data[TLengthOther + i] = arrayTemp[indexArrayTemp];
        indexArrayTemp++;
    }

    /*Init over value by zero*/
    constexpr size_t currentIndex = TLengthOther + sizeof...(TScalarArgs);
    constexpr size_t rest = TLength - currentIndex;
    std::memset(&m_data[currentIndex], 0, sizeof(TType) * rest);
}

template <size_t TLength, typename TType>
inline constexpr 
void Vector<TLength, TType>::fill(const TType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data = scalar;
    }
}

template <size_t TLength, typename TType>
inline constexpr
TType Vector<TLength, TType>::squartLength () const noexcept
{
    TType sqrtLength {static_cast<TType>(0)};

    //x * x + y * y + z * z + [...]
    for (const TType& data : m_data)
    {
        sqrtLength += data * data;
    }

	return sqrtLength;
}

template <size_t TLength, typename TType>
inline constexpr
TType Vector<TLength, TType>::length () const noexcept
{
    return std::sqrt(squartLength());
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::normalize	    () noexcept
{
    const TType lengthRst = length();

    if (lengthRst)
    {
        for (size_t i = 0; i < TLength; i++)
            m_data[i] /= lengthRst;
    }

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::getNormalized		() const noexcept
{
    return Vector<TLength, TType>(*this).normalize();
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>&         Vector<TLength, TType>::clampLength         (TType maxLength) noexcept
{
	TType magnitude {length()};

    if (magnitude && magnitude > maxLength)
    {
		*this /= magnitude;
		*this *= maxLength;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>         Vector<TLength, TType>::getClampedLength         (TType maxLength) const noexcept
{
    return Vector<TLength, TType>(*this).clampLength(maxLength);
}

template <size_t TLength, typename TType>
inline constexpr
TType           Vector<TLength, TType>::dot		            (const Vector& other) const noexcept
{
    TType rst {static_cast<TType>(0)};

    for (size_t i = 0; i < TLength; i++)
    {
        rst += m_data[i] * other[i];
    }
    
    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>&         Vector<TLength, TType>::cross	            (const Vector& other) noexcept
{
    Vector<TLength, TType> copyTemp {*this};

    for (size_t i = 0; i < TLength; i++)
    {
        switch (i)
        {
        case 0:
            m_data[i] = copyTemp[i + 1] * other[TLength - 1] - other[i + 1] * copyTemp[TLength - 1];
            break;
        
        case TLength - 1:
            m_data[i] = copyTemp[0] * other[i - 1] - other[0] * copyTemp[i - 1];
            break;

        default:
            m_data[i] = copyTemp[i + 1] * other[i - 1] - other[i + 1] * copyTemp[i - 1];
            break;
        }
    }

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>         Vector<TLength, TType>::getCross	            (const Vector& other) const noexcept
{
    Vector<TLength, TType> rst;

    for (size_t i = 0; i < TLength; i++)
    {
        switch (i)
        {
        case 0:
            rst[i] = m_data[i + 1] * other[TLength - 1] - other[i + 1] * m_data[TLength - 1];
            break;
        
        case TLength - 1:
            rst[i] = m_data[0] * other[i - 1] - other[0] * m_data[i - 1];
            break;

        default:
            rst[i] = m_data[i + 1] * other[i - 1] - other[i + 1] * m_data[i - 1];
            break;
        }
    }

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::lerp		        (const Vector& other, TType t) noexcept
{
    Vector<TLength, TType> rst;

    for (size_t i = 0; i < TLength; i++)
    {
#if __cplusplus == 201709L //Constexpr std::lerp
        m_data[i] = std::lerp(m_data[i], other[i], t);
#else
        m_data[i] = m_data[i] + t * (other[i] - m_data[i]);
#endif

    }

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::getLerp		        (const Vector& other, TType t) const noexcept
{
    Vector<TLength, TType> rst;

    for (size_t i = 0; i < TLength; i++)
    {
#if __cplusplus == 201709L //Constexpr std::lerp
        rst[i] = std::lerp(m_data[i], other[i], t);
#else
        rst[i] = m_data[i] + t * (other[i] - m_data[i]);
#endif
    }

    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::reflect		        (const Vector& normalNormalized) noexcept
{
#ifndef DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR
    assert(normalNormalized == static_cast<TType>(1) && "You must use unit vector. If you wan't disable assert for unit vector guard. Please define DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR");
#endif

    *this = static_cast<TType>(2) * normalNormalized.dot(*this) * normalNormalized - (*this);
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::getReflection		 (const Vector& normalNormalized) const noexcept
{
#ifndef DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR
    assert(normalNormalized == static_cast<TType>(1) && "You must use unit vector. If you wan't disable assert for unit vector guard. Please define DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR");
#endif

    Vector<TLength, TType> rst;
    rst = static_cast<TType>(2) * normalNormalized.dot(*this) * normalNormalized - (*this);
    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::setLength		     (TType newLength) noexcept
{
	TType magnitude {length()};

    if (magnitude)
    {
		*this /= magnitude;
		*this *= newLength;
    }

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
bool Vector<TLength, TType>::isColinearTo	(const Vector<TLength, TType>& other) const noexcept
{
	return Numeric::isSameAsZero(getCross(other).squartLength()); //hack to avoid sqrt
}

template <size_t TLength, typename TType>
inline constexpr
bool Vector<TLength, TType>::isPerpendicularTo	(const Vector<TLength, TType>& other) const noexcept
{
	return Numeric::isSameAsZero(dot(other)); //hack to avoid sqrt
}

template <size_t TLength, typename TType>
inline constexpr
TType Vector<TLength, TType>::getParallelogramArea		(const Vector<TLength, TType>& other) const noexcept
{
	return getCross(other).length();
}

template <size_t TLength, typename TType>
inline constexpr
TType Vector<TLength, TType>::getTriangleArea		(const Vector<TLength, TType>& other) const noexcept
{
	return getParallelogramArea(other) / static_cast<TType>(2);
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::rotateAroundAxis (const Vector<TLength, TType>& unitAxis, TType angleRad) noexcept
{
#ifndef DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR
    assert(unitAxis == static_cast<TType>(1) && "You must use unit vector. If you wan't disable assert for unit vector guard. Please define DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR");
#endif

	(*this) = getRotationAroundAxis(unitAxis, angleRad);
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::getRotationAroundAxis (const Vector<TLength, TType>& unitAxis, TType angleRad) const noexcept
{
#ifndef DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR
    assert(unitAxis == static_cast<TType>(1) && "You must use unit vector. If you wan't disable assert for unit vector guard. Please define DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR");
#endif

	TType cosA = std::cos(angleRad);

	//rodrigues rotation formula
	return (*this) * cosA + unitAxis.getCross(*this) * std::sin(angleRad) + unitAxis * unitAxis.dot(*this) * (static_cast<TType>(1) - cosA);
}

template <size_t TLength, typename TType>
inline constexpr
TType Vector<TLength, TType>::getScalarProjectionWith(const Vector& other) const noexcept
{
    return dot(*this, other.getNormalized());
}

template <size_t TLength, typename TType>
inline constexpr
TType Vector<TLength, TType>::getScalarRejectionWith(const Vector& other) const noexcept
{
    return cross(*this, other.getNormalized()).length();
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::getVectorProjectionWith(const Vector<TLength, TType>& other) const noexcept
{
    Vector normalizedOther = other.getNormalized();
    return dot(*this, normalizedOther) * normalizedOther;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::getVectorRejectionWith(const Vector<TLength, TType>& other) const noexcept
{
    return (*this) - getVectorProjectionWith(other);
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] = static_cast<TType>(other[i]);
    }

    if (minLenght < TLength)
    {
        for (size_t i = minLenght; i < TLength; i++)
        {
            m_data[i] = static_cast<TType>(0);
        }
    }

    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data = static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
TType&  Vector<TLength, TType>::operator[]	(size_t index) noexcept
{
    assert(index >= 0 && index < TLength);
    return m_data[index];
}

template <size_t TLength, typename TType>
inline constexpr
const TType&    Vector<TLength, TType>::operator[]	(size_t index) const noexcept
{
    assert(index >= 0 && index < TLength);
    return m_data[index];
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator+=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data += static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator+=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] += static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator-=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data -= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator-=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] -= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator*=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data *= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator*=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] *= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator/=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data /= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator/=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] /= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator%=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data %= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator%=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] %= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator&=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data &= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator&=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] &= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator|=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data |= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator|=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] |= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator^=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data ^= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator^=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] ^= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator<<=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data <<= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator<<=(const Vector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] <<= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator>>=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data >>= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator>>=(const Vector<TLengthOther, TTypeOther>& other) noexcept
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
Vector<TLength, TType>& 	Vector<TLength, TType>::operator++	() noexcept
{
    for (TType& data : m_data)
    {
        ++data;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator--	() noexcept
{
    for (TType& data : m_data)
    {
        --data;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::operator++	(int) noexcept
{
	Vector<TLength, TType> result(*this);
	++*this;
	return result;
}


template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> Vector<TLength, TType>::operator--	(int) noexcept
{
	Vector<TLength, TType> result(*this);
	--*this;
	return result;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
constexpr inline 
Vector<TLength, TType>::operator Vector<TLengthOther, TTypeOther>() const noexcept
{
    Vector<TLengthOther, TTypeOther> result;

    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        result[i] = static_cast<TTypeOther>(m_data[i]);
    }

    return result;
}


template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator+(Vector<TLength, TType> const& vec) noexcept
{
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator-(Vector<TLength, TType> vec) noexcept
{
    return vec *= static_cast<TType>(-1);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator+(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec += static_cast<TType>(scalar); 
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator+(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) + vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator+(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs += rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator-(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec -= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator-(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) - vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator-(Vector<TLength, TType> lhs, const Vector<TLength, TType>& rhs) noexcept
{
    return lhs -= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator*(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec *= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator*(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) * vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator*(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs *= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator/(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec /= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator/(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) / vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator/(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs /= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator%(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec %= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator%(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) % vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator%(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs %= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator&(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec &= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator&(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) & vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator&(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs &= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator|(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec |= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator|(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) | vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator|(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs |= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator^(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec ^= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator^(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) ^ vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator^(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs ^= rhs;
}


template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator<<(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec << static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator<<(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) << vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator<<(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs << rhs;
}


template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator>>(Vector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec >> static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
Vector<TLength, TType> operator>>(TTypeScalar scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) >> vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
Vector<TLength, TType> operator>>(Vector<TLength, TType> lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs >> rhs;
}


template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator~(Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = ~vec[i];
    }
    
    return vec;
}

template <size_t TLength>
inline constexpr
Vector<TLength, bool> operator!(Vector<TLength, bool> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = !vec[i];
    }
    
    return vec;
}

template <size_t TLength, size_t TLengthOther>
inline constexpr
Vector<TLength, bool> operator&&(Vector<TLength, bool> lhs, Vector<TLengthOther, bool> const& rhs) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        lhs[i] &= rhs[i];
    }
    
    return lhs;
}

template <size_t TLength, size_t TLengthOther>
inline constexpr
Vector<TLength, bool> operator||(Vector<TLength, bool> lhs, Vector<TLengthOther, bool> const& rhs) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        lhs[i] |= rhs[i];
    }
    
    return lhs;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator==(Vector<TLength, TType> const& lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
#ifdef VECTOR_OPERATOR_EGALE_COMPARE_LENGTH

    return Numeric::isSame<TType>(lhs.squartLength(), static_cast<TType>(rhs.squartLength()));

#else

    bool rst = true;

    for (size_t i = 0; i < TLength && rst; i++)
    {
        rst &= lhs[i] == static_cast<TType>(rhs[i]);
    }

    return rst;

#endif
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
bool operator==(Vector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return Numeric::isSame<TType>(vec.squartLength(), static_cast<TType>(scalar) * static_cast<TType>(scalar)); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
bool operator==(TTypeScalar scalar, Vector<TLength, TType> const& vec) noexcept
{
    return Numeric::isSame<TType>(static_cast<TType>(scalar) * static_cast<TType>(scalar), vec.squartLength()); //hack to avoid sqrt
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator!=(Vector<TLength, TType> const& lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return !(lhs == rhs);
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator!=(Vector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return !(vec == static_cast<TType>(scalar));
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator!=(TTypeScalar scalar, Vector<TLength, TType> const& vec) noexcept
{
    return !(static_cast<TType>(scalar) == vec);
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator<(Vector<TLength, TType> const& lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squartLength() < static_cast<TType>(rhs.squartLength());
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<(Vector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squartLength() < static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<(TTypeScalar scalar, Vector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) < vec.squartLength(); //hack to avoid sqrt
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator>(Vector<TLength, TType> const& lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squartLength() > static_cast<TType>(rhs.squartLength());
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>(Vector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squartLength() > static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>(TTypeScalar scalar, Vector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) > vec.squartLength(); //hack to avoid sqrt
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator<=(Vector<TLength, TType> const& lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squartLength() <= static_cast<TType>(rhs.squartLength());
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<=(Vector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squartLength() <= static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<=(TTypeScalar scalar, Vector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) <= vec.squartLength(); //hack to avoid sqrt
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator>=(Vector<TLength, TType> const& lhs, Vector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squartLength() >= static_cast<TType>(rhs.squartLength());
}


template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>=(Vector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squartLength() >= static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>=(TTypeScalar scalar, Vector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) >= vec.squartLength(); //hack to avoid sqrt
}


template <size_t TLength, typename TType>
inline constexpr
std::ostream& 	operator<<		(std::ostream& out, const Vector<TLength, TType>& vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        out << vec[i] << "  ";
    }

    return out;  
}

template <size_t TLength, typename TType>
inline constexpr
std::istream& 	operator>>		(std::istream& in, const Vector<TLength, TType>& vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        in >> vec[i] >> "   ";
    }

    return in;  
}