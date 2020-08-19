/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-18 - 10 h 12
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

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
typename GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::InternalVector&  GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::at (size_t index) throw ()
{
    

    if (index < numberOfInternalVector()) [[likely]]
        return m_vector[index];

    std::__throw_out_of_range_fmt(__N("GenericMatrix::at: index"
				       "(which is %zu) >= numberOfInternalVector() "
				       "(which is %zu)"),
				        index, numberOfInternalVector());
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
const typename GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::InternalVector& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::at (size_t index) const throw ()
{
    if (index < numberOfInternalVector()) [[likely]]
        return m_vector[index];

    std::__throw_out_of_range_fmt(__N("GenericMatrix::at: index "
				        "(which is %zu) >= numberOfInternalVector() "
				       "(which is %zu)"),
				        index, numberOfInternalVector());
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
TType&  GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::getData (size_t index) throw ()
{
    if (index < numberOfData()) [[likely]]
        return m_data[index];

    std::__throw_out_of_range_fmt(__N("GenericMatrix::at: index"
				       "(which is %zu) >= numberOfData() "
				       "(which is %zu)"),
				        index, numberOfData());
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
const TType&    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::getData (size_t index) const throw ()
{
    if (index < numberOfData()) [[likely]]
        return m_data[index];

    std::__throw_out_of_range_fmt(__N("GenericMatrix::at: index "
				        "(which is %zu) >= numberOfData() "
				       "(which is %zu)"),
				        index, numberOfData());
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
typename GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::InternalVector&  GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator[]	(size_t index) noexcept
{
    assert(index < numberOfInternalVector());
    return m_vector[index];
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
const typename GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::InternalVector&    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator[]	(size_t index) const noexcept
{
    assert(index < numberOfInternalVector());
    return m_vector[index];
}

/*
template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data = static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
Vector::GenericVector<(TMatrixConvention == EMatrixConvention::ColumnMajor) ? TColumnSize : TRowSize, TType>&  GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator[]	(size_t index) noexcept
{
    assert(index >= 0 && index < TLength);
    return m_data[index];
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
const Vector::GenericVector<(TMatrixConvention == EMatrixConvention::ColumnMajor) ? TColumnSize : TRowSize, TType>&    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator[]	(size_t index) const noexcept
{
    assert(index >= 0 && index < TLength);
    return m_data[index];
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator+=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data += static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator+=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] += static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator-=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data -= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator-=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] -= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator*=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data *= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator*=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] *= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator/=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data /= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator/=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] /= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator%=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data %= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator%=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] %= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator&=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data &= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator&=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] &= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator|=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data |= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator|=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] |= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator^=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data ^= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator^=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] ^= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator<<=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data <<= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator<<=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] <<= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator>>=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data >>= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator>>=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] >>= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr 
GenericVector<TLength, TType>& 	GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator++	() noexcept
{
    for (TType& data : m_data)
    {
        ++data;
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericVector<TLength, TType>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator--	() noexcept
{
    for (TType& data : m_data)
    {
        --data;
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericVector<TLength, TType> GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator++	(int) noexcept
{
	GenericVector<TLength, TType> result(*this);
	++*this;
	return result;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericVector<TLength, TType> GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator--	(int) noexcept
{
	GenericVector<TLength, TType> result(*this);
	--*this;
	return result;
}
*/

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
constexpr inline 
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>() const noexcept
{
    GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> result;

    constexpr size_t minInternalVector = (GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>::numberOfInternalVector() < numberOfInternalVector()) ? 
                                          GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>::numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        //conversion type is inside vector's assignement operator
        result[i] = m_vector[i];
    }

    for (size_t i = minInternalVector; i < GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>::numberOfInternalVector(); i++)
    {
        result[i] = static_cast<TTypeOther>(0);
    }

    return result;
}

/*
template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> const& vec) noexcept
{
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> vec) noexcept
{
    return vec *= static_cast<TType>(-1);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec += static_cast<TType>(scalar); 
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator+(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) + vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs += rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec -= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator-(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) - vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> lhs, const GenericVector<TLength, TType>& rhs) noexcept
{
    return lhs -= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator*(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec *= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator*(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) * vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator*(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs *= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator/(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec /= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator/(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) / vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator/(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs /= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator%(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec %= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator%(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) % vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator%(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs %= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator&(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec &= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator&(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) & vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator&(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs &= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator|(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec |= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator|(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) | vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator|(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs |= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator^(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec ^= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator^(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) ^ vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator^(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs ^= rhs;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator<<(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec << static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator<<(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) << vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator<<(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs << rhs;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator>>(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec >> static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator>>(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = static_cast<TType>(scalar) >> vec[i];
    }
    
    return vec;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator>>(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs >> rhs;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericVector<TLength, TType> operator~(GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = ~vec[i];
    }
    
    return vec;
}

template <size_t TLength>
inline constexpr
GenericVector<TLength, bool> operator!(GenericVector<TLength, bool> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec[i] = !vec[i];
    }
    
    return vec;
}

template <size_t TLength, size_t TLengthOther>
inline constexpr
GenericVector<TLength, bool> operator&&(GenericVector<TLength, bool> lhs, GenericVector<TLengthOther, bool> const& rhs) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        lhs[i] &= rhs[i];
    }
    
    return lhs;
}

template <size_t TLength, size_t TLengthOther>
inline constexpr
GenericVector<TLength, bool> operator||(GenericVector<TLength, bool> lhs, GenericVector<TLengthOther, bool> const& rhs) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        lhs[i] |= rhs[i];
    }
    
    return lhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator==(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
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

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
bool operator==(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return Numeric::isSame<TType>(vec.squartLength(), static_cast<TType>(scalar) * static_cast<TType>(scalar)); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
bool operator==(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return Numeric::isSame<TType>(static_cast<TType>(scalar) * static_cast<TType>(scalar), vec.squartLength()); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator!=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return !(lhs == rhs);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator!=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return !(vec == static_cast<TType>(scalar));
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator!=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return !(static_cast<TType>(scalar) == vec);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator<(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squartLength() < static_cast<TType>(rhs.squartLength());
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squartLength() < static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) < vec.squartLength(); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator>(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squartLength() > static_cast<TType>(rhs.squartLength());
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squartLength() > static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) > vec.squartLength(); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator<=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squartLength() <= static_cast<TType>(rhs.squartLength());
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squartLength() <= static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) <= vec.squartLength(); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator>=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squartLength() >= static_cast<TType>(rhs.squartLength());
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squartLength() >= static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) >= vec.squartLength(); //hack to avoid sqrt
}
*/

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
std::ostream& 	operator<<		(std::ostream& out, const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& mat) noexcept
{
    if constexpr (TMatrixConvention == EMatrixConvention::RowMajor)
    {
        for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
        {
            out << mat[i] << std::endl;
        }
    }
    else
    {
        for (size_t iData = 0; iData < mat.vectorLength(); iData++)
        {
            for (size_t iVec = 0; iVec < mat.numberOfInternalVector(); iVec++)
            {
                out << mat[iVec][iData] << "  ";
            }
            out << std::endl;
        }
    }

    return out;  
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
std::istream& 	operator>>		(std::istream& in, const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& mat) noexcept
{
    if constexpr (TMatrixConvention == EMatrixConvention::RowMajor)
    {
        for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
        {
            in >> mat[i];
        }
    }
    else
    {
        for (size_t iData = 0; iData < mat.vectorLength(); iData++)
        {
            for (size_t iVec = 0; iVec < mat.numberOfInternalVector(); iVec++)
            {
                in >> mat[iVec][iData];
            }
        }
    }

    return in;  
}