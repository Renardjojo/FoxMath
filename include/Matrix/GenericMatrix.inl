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
constexpr inline
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::GenericMatrix () noexcept
    : m_data{}
{}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename... T, Type::IsSame<Type::Pack<TType, T...>, Type::Pack<T..., TType>> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::GenericMatrix (T... args) noexcept
{
    m_data = std::array<TType, numberOfData ()>{args...};
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename... T>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::GenericMatrix (T... args) noexcept
{
    m_vector = std::array<InternalVector, numberOfInternalVector ()>{args...};
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr  
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::fill (const TscalarType scalar) noexcept
{
    m_data.fill(static_cast<TType>(scalar));
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>&		GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::transpose		() noexcept
{
    assert(isSquare());

    size_t shift = 1;

    for (size_t i = 0; i < TColumnSize - 1; i++)
    {
        for (size_t j = shift; j < TRowSize; j++)
        {
            std::swap(m_vector[i][j], m_vector[j][i]);
        }
        shift++;
    }
    
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <EMatrixConvention TMatrixConventionOther = TMatrixConvention>
inline constexpr  
GenericMatrix<TColumnSize, TRowSize, TType, TMatrixConventionOther>		GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::getTransposed	() const noexcept
{
    GenericMatrix<TColumnSize, TRowSize, TType, TMatrixConventionOther> rst;

    if constexpr (TMatrixConvention == TMatrixConventionOther)
    {
        for (size_t i = 0; i < numberOfInternalVector(); i++)
        {
            for (size_t j = 0; j < vectorLength(); j++)
            {
                rst[j][i] = m_vector[i][j];
            }
        }
    }
    else
    {
#if __cplusplus >= 201709L
        if (std::is_constant_evaluated())
        {
#endif
            for (size_t i = 0; i < numberOfData(); i++)
            {
                rst.getData(i) = m_data[i];
            }
#if __cplusplus >= 201709L 
        }
        else //memcopy optimization is not constexpr
        {
            std::memcpy(&rst[0], &m_data[0], sizeof(TType) * numberOfData());
        }
#endif
    }

    return rst;
}

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


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator=(TscalarType scalar) noexcept
{
    return fill(static_cast<TType>(scalar));
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator+=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data += static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator+=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] += other[i];
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator-=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data -= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator-=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] -= other[i];
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator*=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data *= static_cast<TType>(scalar);
    }
    return *this;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther,  Type::IsEqualTo<TColumnSize, TRowSizeOther> = true, Type::IsEqualTo<TColumnSize, TColumnSizeOther> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator*=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t squareCommonSize = TRowSizeOther; //Same as TColumnSize

    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mRst;
    mRst.fill(0);

    for ( size_t rowI = 0; rowI < TRowSize  ; rowI++ )
    {
        for ( size_t columnI = 0; columnI < TColumnSize; columnI++ )
        {
            for ( size_t index = 0; index < squareCommonSize; index++)
            {
                mRst[columnI][rowI] += ((*this)[index][rowI] * static_cast<TType>(other[columnI][index]));
            }
        }
    }

    (*this) = std::move(mRst);
    
    return *this;
}



template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator/=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data /= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator/=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] /= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator%=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data %= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator%=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] %= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator&=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data &= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator&=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] &= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator|=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data |= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator|=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] |= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator^=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data ^= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator^=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] ^= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator<<=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data <<= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator<<=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] <<= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator>>=(TscalarType scalar) noexcept
{
    for (TType& data : m_data)
    {
        data >>= static_cast<TType>(scalar);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator>>=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention>& other) noexcept
{
    constexpr size_t minInternalVector = (other.numberOfInternalVector() < numberOfInternalVector()) ? other.numberOfInternalVector() : numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        m_vector[i] >>= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr 
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& 	GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator++	() noexcept
{
    for (TType& data : m_data)
    {
        ++data;
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator--	() noexcept
{
    for (TType& data : m_data)
    {
        --data;
    }
    return *this;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator++	(int) noexcept
{
	GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> result(*this);
	++(*this);
	return result;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator--	(int) noexcept
{
	GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> result(*this);
	--(*this);
	return result;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
constexpr inline 
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>::operator GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>() const noexcept
{
    GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> result;

    constexpr size_t minInternalVector = (GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>::numberOfInternalVector() < numberOfInternalVector()) ? 
                                          GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>::numberOfInternalVector() : numberOfInternalVector();

    if constexpr (TMatrixConvention != TMatrixConventionOther)
    {
        GenericMatrix<TColumnSize, TRowSize, TType, TMatrixConventionOther> transposedVector = getTransposed<TMatrixConventionOther>();

        for (size_t i = 0; i < minInternalVector; i++)
        {
            //conversion type is inside vector's assignement operator
            result[i] = transposedVector[i];
        }
    }
    else
    {
        for (size_t i = 0; i < minInternalVector; i++)
        {
            //conversion type is inside vector's assignement operator
            result[i] = m_vector[i];
        }
    }

    return result;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept
{
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    return mat *= static_cast<TType>(-1);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat += static_cast<TType>(scalar); 
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) + mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs += rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat -= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) - mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& rhs) noexcept
{
    return lhs -= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator*(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat *= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator*(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) * mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator*(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs *= rhs;
}

template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
            size_t TRowSizeOther, size_t TColumnSizeOther,
            Type::IsEqualTo<TColumnSize, TRowSizeOther> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSizeOther, TType, TMatrixConvention> operator*(const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& lhs, const GenericMatrix<TRowSizeOther, TColumnSizeOther, TType, TMatrixConvention>& rhs) noexcept
{
    constexpr size_t squareCommonSize = TRowSizeOther; //Same as TColumnSize

    GenericMatrix<TRowSize, TColumnSizeOther, TType, TMatrixConvention> mRst;
    mRst.fill(0);

    for ( size_t rowI = 0; rowI < TRowSize  ; rowI++ )
    {
        for ( size_t columnI = 0; columnI < TColumnSizeOther; columnI++ )
        {
            for ( size_t index = 0; index < squareCommonSize; index++)
            {
                mRst[columnI][rowI] += lhs[index][rowI] * rhs[columnI][index];
            }
        }
    }

    return mRst;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat /= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) / mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs /= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat %= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) % mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs %= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat &= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) & mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs &= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat |= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) | mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs |= rhs;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat ^= static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) ^ mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs ^= rhs;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat << static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) << mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs << rhs;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat, TTypeScalar scalar) noexcept
{
    return mat >> static_cast<TType>(scalar);
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = static_cast<TType>(scalar) >> mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return lhs >> rhs;
}


template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator~(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = ~mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, EMatrixConvention TMatrixConvention>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> operator!(GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> mat) noexcept
{
    for (size_t i = 0; i < mat.numberOfInternalVector(); i++)
    {
        mat[i] = !mat[i];
    }
    
    return mat;
}

template <size_t TRowSize, size_t TColumnSize, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> operator&&(GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, bool, TMatrixConvention> const& rhs) noexcept
{
    constexpr size_t minInternalVector = (rhs.numberOfInternalVector() < lhs.numberOfInternalVector()) ? 
                                          rhs.numberOfInternalVector() : lhs.numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        lhs[i] &= rhs[i];
    }
    
    return lhs;
}

template <size_t TRowSize, size_t TColumnSize, EMatrixConvention TMatrixConvention, size_t TRowSizeOther, size_t TColumnSizeOther>
inline constexpr
GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> operator||(GenericMatrix<TRowSize, TColumnSize, bool, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, bool, TMatrixConvention> const& rhs) noexcept
{
    constexpr size_t minInternalVector = (rhs.numberOfInternalVector() < lhs.numberOfInternalVector()) ? 
                                          rhs.numberOfInternalVector() : lhs.numberOfInternalVector();

    for (size_t i = 0; i < minInternalVector; i++)
    {
        lhs[i] |= rhs[i];
    }
    
    return lhs;
}

template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
            size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
bool operator==(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    constexpr size_t minInternalVector = (rhs.numberOfInternalVector() < lhs.numberOfInternalVector()) ? 
                                          rhs.numberOfInternalVector() : lhs.numberOfInternalVector();

    bool rst = true;

    for (size_t i = 0; i < minInternalVector && rst; i++)
    {
        rst &= lhs[i] == static_cast<TType>(rhs[i]);
    }

    return rst;
}

template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
            size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther>
inline constexpr
bool operator!=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConvention> const& rhs) noexcept
{
    return !(lhs == rhs);
}

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