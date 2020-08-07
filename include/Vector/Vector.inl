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
const Vector<TLength, TType>& Vector<TLength, TType>::getNormalized		() const noexcept
{
    return Vector<TLength, TType>(*this).normalize();
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
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
Vector<TLength, TType>& Vector<TLength, TType>::operator=(TscalarType scalar) noexcept
{
    for (const TType& data : m_data)
    {
        data = scalar;
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

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator+(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec += scalar; 
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator+(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) + vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator+(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs += rhs;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator-(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec -= scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator-(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) - vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator-(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs -= rhs;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator*(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec *= scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator*(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) * vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator*(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs *= rhs;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator/(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec /= scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator/(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) / vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator/(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs /= rhs;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator%(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec %= scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator%(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) % vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator%(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs %= rhs;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator&(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec &= scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator&(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) & vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator&(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs &= rhs;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator|(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec |= scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator|(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) | vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator|(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs |= rhs;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator^(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec ^= scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator^(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) ^ vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator^(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs ^= rhs;
}


template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator<<(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec << scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator<<(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) << vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator<<(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs << rhs;
}


template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator>>(Vector<TLength, TType> vec, TType scalar) noexcept
{
    return vec >> scalar;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator>>(TType scalar, Vector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) >> vec[i];
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
Vector<TLength, TType> operator>>(Vector<TLength, TType> lhs, Vector<TLength, TType> const& rhs) noexcept
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

template <size_t TLength>
inline constexpr
Vector<TLength, bool> operator&&(Vector<TLength, bool> lhs, Vector<TLength, bool> const& rhs) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        lhs[i] &= rhs[i];
    }
    
    return lhs;
}

template <size_t TLength>
inline constexpr
Vector<TLength, bool> operator||(Vector<TLength, bool> lhs, Vector<TLength, bool> const& rhs) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        lhs[i] |= rhs[i];
    }
    
    return lhs;
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator==(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept
{
#ifdef VECTOR_OPERATOR_EGALE_COMPARE_LENGTH

    return Numeric::isSame<TType>(lhs.squartLength(), rhs.squartLength());

#else

    bool rst = true;

    for (size_t i = 0; i < TLength && rst; i++)
    {
        rst &= lhs[i] == rhs[i];
    }

    return rst;

#endif
}

template <size_t TLength, typename TType>
inline constexpr
bool operator==(Vector<TLength, TType> const& vec, TType scalar) noexcept
{
    return Numeric::isSame<TType>(vec.squartLength(), scalar);
}

template <size_t TLength, typename TType>
inline constexpr
bool operator==(TType scalar, Vector<TLength, TType> const& vec) noexcept
{
    return Numeric::isSame<TType>(scalar, vec.squartLength());
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator!=(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return !(lhs == rhs);
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator!=(Vector<TLength, TType> const& vec, TType scalar) noexcept
{
    return !(vec == scalar);
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator!=(TType scalar, Vector<TLength, TType> const& vec) noexcept
{
    return !(scalar == vec);
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator<(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs.squartLength() < rhs.squartLength();
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator<(Vector<TLength, TType> const& vec, TType scalar) noexcept
{
    return vec.squartLength() < scalar;
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator<(TType scalar, Vector<TLength, TType> const& vec) noexcept
{
    return scalar < vec.squartLength();
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator>(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs.squartLength() > rhs.squartLength();
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator>(Vector<TLength, TType> const& vec, TType scalar) noexcept
{
    return vec.squartLength() > scalar;
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator>(TType scalar, Vector<TLength, TType> const& vec) noexcept
{
    return scalar > vec.squartLength();
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator<=(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs.squartLength() <= rhs.squartLength();
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator<=(Vector<TLength, TType> const& vec, TType scalar) noexcept
{
    return vec.squartLength() <= scalar;
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator<=(TType scalar, Vector<TLength, TType> const& vec) noexcept
{
    return scalar <= vec.squartLength();
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator>=(Vector<TLength, TType> const& lhs, Vector<TLength, TType> const& rhs) noexcept
{
    return lhs.squartLength() >= rhs.squartLength();
}


template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator>=(Vector<TLength, TType> const& vec, TType scalar) noexcept
{
    return vec.squartLength() >= scalar;
}

template <size_t TLength, typename TType>
[[nodiscard]] inline constexpr
bool operator>=(TType scalar, Vector<TLength, TType> const& vec) noexcept
{
    return scalar >= vec.squartLength();
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