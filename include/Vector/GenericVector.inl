template <size_t TLength, typename TType>
template<typename... T, IsAllSame<TType, T...> = true,
IsLessThanOrEqualTo<sizeof...(T), TLength> = true>
constexpr inline 
GenericVector<TLength, TType>::GenericVector (T... args) noexcept
{
    m_data = std::array<TType, TLength>{args...};
}

template <size_t TLength, typename TType>
template<size_t TLengthOther, typename... TScalarArgs, 
IsAllSame<TType, TScalarArgs...> = true,
IsLessThanOrEqualTo<sizeof...(TScalarArgs) + TLengthOther, TLength> = true,
IsLessThan<TLengthOther, TLength> = true>
inline constexpr
GenericVector<TLength, TType>::GenericVector (const GenericVector<TLengthOther, TType>& other, TScalarArgs... args) noexcept
{
    /*Add generic vector*/
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

#if __cplusplus >= 201709L
    if (std::is_constant_evaluated())
    {
#endif
        for (size_t i = 0; i < rest; i++)
        {
            m_data[currentIndex + i] = static_cast<TType>(0);
        }
#if __cplusplus >= 201709L 
    }
    else //memset optimization is not constexpr
    {
        std::memset(&m_data[currentIndex], 0, sizeof(TType) * rest);
    }
#endif
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr 
GenericVector<TLength, TType>& GenericVector<TLength, TType>::fill(const TscalarType scalar) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        m_data[i] = static_cast<TType>(scalar);
    }

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
TType GenericVector<TLength, TType>::squareLength () const noexcept
{
    TType sqrtLength {static_cast<TType>(0)};

    //x * x + y * y + z * z + [...]
    for (const TType& data : m_data)
    {
        sqrtLength += data * data;
    }

	return sqrtLength;
}

//TODO: method not constexpr if it use std::sqrt. Replace it by my own function
template <size_t TLength, typename TType>
inline constexpr
TType GenericVector<TLength, TType>::length () const noexcept
{
    return std::sqrt(squareLength());
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>& 	    GenericVector<TLength, TType>::homogenize	        () noexcept
{
	if (m_data[TLength - 1] != static_cast<TType>(0)) [[likely]]
	    (*this) /= m_data[TLength - 1];

    return (*this);
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> 	    GenericVector<TLength, TType>::getHomogenized	        () const noexcept
{
    GenericVector<TLength, TType> rst (*this);
    rst.homogenize();
    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::normalize	    () noexcept
{
    const TType lengthRst = length();

    if (lengthRst) [[likely]]
    {
        for (size_t i = 0; i < TLength; i++)
            m_data[i] /= lengthRst;
    }

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> GenericVector<TLength, TType>::getNormalized		() const noexcept
{
    GenericVector<TLength, TType> rst (*this);
    rst.normalize();
    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>&         GenericVector<TLength, TType>::clampLength         (TType maxLength) noexcept
{
	TType magnitude {length()};

    if (magnitude > maxLength) [[likely]]
    {
        const TType coef = maxLength / magnitude;
        *this *= coef;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>         GenericVector<TLength, TType>::getClampedLength         (TType maxLength) const noexcept
{
    GenericVector<TLength, TType> rst (*this);
    rst.clampLength(maxLength);
    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
TType           GenericVector<TLength, TType>::dot		            (const GenericVector& other) const noexcept
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
GenericVector<TLength, TType>&         GenericVector<TLength, TType>::cross	            (const GenericVector& other) noexcept
{
    GenericVector<TLength, TType> copyTemp {*this};

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
GenericVector<TLength, TType>         GenericVector<TLength, TType>::getCross	            (const GenericVector& other) const noexcept
{
    GenericVector<TLength, TType> rst;

    for (size_t i = 0; i < TLength; i++)
    {
        switch (i)
        {
        case 0:
            rst.setData(i, m_data[i + 1] * other[TLength - 1] - other[i + 1] * m_data[TLength - 1]);
            break;
        
        case TLength - 1:
            rst.setData(i, m_data[0] * other[i - 1] - other[0] * m_data[i - 1]);
            break;

        default:
            rst.setData(i, m_data[i + 1] * other[i - 1] - other[i + 1] * m_data[i - 1]);
            break;
        }
    }

    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::lerp		        (const GenericVector& other, TType t) noexcept
{
    GenericVector<TLength, TType> rst;

    for (size_t i = 0; i < TLength; i++)
    {
#if __cplusplus >= 201709L //Constexpr std::lerp
        m_data[i] = std::lerp(m_data[i], other[i], t);
#else
        m_data[i] = m_data[i] + t * (other[i] - m_data[i]);
#endif

    }

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> GenericVector<TLength, TType>::getLerp		        (const GenericVector& other, TType t) const noexcept
{
    GenericVector<TLength, TType> rst;

    for (size_t i = 0; i < TLength; i++)
    {
#if __cplusplus == 201709L //Constexpr std::lerp
        rst.setData(i, std::lerp(m_data[i], other[i], t));
#else
        rst.setData(i, m_data[i] + t * (other[i] - m_data[i]));
#endif
    }

    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::reflect		        (const GenericVector& normalNormalized) noexcept
{
#ifndef DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR
    assert(normalNormalized == static_cast<TType>(1) && "You must use unit generic vector. If you want disable assert for unit generic vector guard, please define DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR");
#endif

    *this = static_cast<TType>(2) * normalNormalized.dot(*this) * normalNormalized - (*this);
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> GenericVector<TLength, TType>::getReflection		 (const GenericVector& normalNormalized) const noexcept
{
#ifndef DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR
    assert(normalNormalized == static_cast<TType>(1) && "You must use unit generic vector. If you want disable assert for unit generic vector guard, please define DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR");
#endif

    GenericVector<TLength, TType> rst;
    rst = static_cast<TType>(2) * normalNormalized.dot(*this) * normalNormalized - (*this);
    return rst;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::setLength		     (TType newLength) noexcept
{
    const TType coef = newLength / length();
    *this *= coef;

    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
bool GenericVector<TLength, TType>::isColinearTo	(const GenericVector<TLength, TType>& other) const noexcept
{
	return isSameAsZero(getCross(other).squareLength()); //hack to avoid sqrt
}

template <size_t TLength, typename TType>
inline constexpr
bool GenericVector<TLength, TType>::isPerpendicularTo	(const GenericVector<TLength, TType>& other) const noexcept
{
	return isSameAsZero(dot(other)); //hack to avoid sqrt
}

template <size_t TLength, typename TType>
inline constexpr
TType GenericVector<TLength, TType>::getParallelogramArea		(const GenericVector<TLength, TType>& other) const noexcept
{
	return getCross(other).length();
}

template <size_t TLength, typename TType>
inline constexpr
TType GenericVector<TLength, TType>::getTriangleArea		(const GenericVector<TLength, TType>& other) const noexcept
{
	return getParallelogramArea(other) / static_cast<TType>(2);
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::rotateAroundAxis (const GenericVector<TLength, TType>& unitAxis, const Angle<EAngleType::Radian, TType>& angle) noexcept
{
	(*this) = getRotationAroundAxis(unitAxis, angle);
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> GenericVector<TLength, TType>::getRotationAroundAxis (const GenericVector<TLength, TType>& unitAxis, const Angle<EAngleType::Radian, TType>& angle) const noexcept
{
#ifndef DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR
    assert(unitAxis == static_cast<TType>(1) && "You must use unit generic vector. If you want disable assert for unit generic vector guard, please define DONT_USE_DEBUG_ASSERT_FOR_UNIT_VETOR");
#endif

	TType cosA = std::cos(static_cast<TType>(angle));

	//rodrigues rotation formula
	return (*this) * cosA + unitAxis.getCross(*this) * std::sin(static_cast<TType>(angle)) + unitAxis * unitAxis.dot(*this) * (static_cast<TType>(1) - cosA);
}

template <size_t TLength, typename TType>
inline constexpr
TType GenericVector<TLength, TType>::getScalarProjectionWith(const GenericVector& other) const noexcept
{
    return dot(*this, other.getNormalized());
}

template <size_t TLength, typename TType>
inline constexpr
TType GenericVector<TLength, TType>::getScalarRejectionWith(const GenericVector& other) const noexcept
{
    return cross(*this, other.getNormalized()).length();
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> GenericVector<TLength, TType>::getVectorProjectionWith(const GenericVector<TLength, TType>& other) const noexcept
{
    GenericVector normalizedOther = other.getNormalized();
    return dot(*this, normalizedOther) * normalizedOther;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> GenericVector<TLength, TType>::getVectorRejectionWith(const GenericVector<TLength, TType>& other) const noexcept
{
    return (*this) - getVectorProjectionWith(other);
}

[[noreturn]] inline 
void outOfRangeThrow()
{
    throw std::out_of_range("At() : index > vector length");
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::setDataAt(size_t index, TscalarType scalar) throw ()
{
    if (index < TLength) [[likely]]
    {
        m_data[index] = static_cast<TType>(scalar);
        return *this;
    }

    std::__throw_out_of_range_fmt(__N("Genericat: index"
                    "(which is %zu) >= TLength "
                    "(which is %zu)"),
                        index, TLength);
}

template <size_t TLength, typename TType>
inline constexpr
const TType    GenericVector<TLength, TType>::at (size_t index) const throw ()
{
    if (index < TLength) [[likely]]
        return m_data[index];

    std::__throw_out_of_range_fmt(__N("Genericat: index "
				        "(which is %zu) >= TLength "
				       "(which is %zu)"),
				        index, TLength);
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator=(TscalarType scalar) noexcept
{
    return fill(static_cast<TType>(scalar));
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::setData(size_t index, TscalarType scalar) noexcept
{
    assert(index < TLength);

    m_data[index] = static_cast<TType>(scalar);
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
const TType    GenericVector<TLength, TType>::operator[]	(size_t index) const noexcept
{
    assert(index < TLength);
    return m_data[index];
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator+=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator+=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] += static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator-=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator-=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] -= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator*=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator*=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] *= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator/=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator/=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] /= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator%=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator%=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] %= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator&=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator&=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] &= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator|=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator|=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] |= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator^=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator^=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] ^= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator<<=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator<<=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
{
    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        m_data[i] <<= static_cast<TType>(other[i]);
    }
    return *this;
}

template <size_t TLength, typename TType>
template<typename TscalarType, IsArithmetic<TscalarType> = true>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator>>=(TscalarType scalar) noexcept
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
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator>>=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
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
GenericVector<TLength, TType>& 	GenericVector<TLength, TType>::operator++	() noexcept
{
    for (TType& data : m_data)
    {
        ++data;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType>& GenericVector<TLength, TType>::operator--	() noexcept
{
    for (TType& data : m_data)
    {
        --data;
    }
    return *this;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> GenericVector<TLength, TType>::operator++	(int) noexcept
{
	GenericVector<TLength, TType> result(*this);
	++*this;
	return result;
}


template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> GenericVector<TLength, TType>::operator--	(int) noexcept
{
	GenericVector<TLength, TType> result(*this);
	--*this;
	return result;
}

template <size_t TLength, typename TType>
template <size_t TLengthOther, typename TTypeOther>
constexpr inline 
GenericVector<TLength, TType>::operator GenericVector<TLengthOther, TTypeOther>() const noexcept
{
    GenericVector<TLengthOther, TTypeOther> result;

    constexpr size_t minLenght = (TLengthOther < TLength) ? TLengthOther : TLength;

    for (size_t i = 0; i < minLenght; i++)
    {
        result.setData(i, static_cast<TTypeOther>(m_data[i]));
    }

#if __cplusplus >= 201709L
    if (std::is_constant_evaluated())
    {
#endif
        for (size_t i = minLenght; i < TLengthOther; i++)
        {
            result.setData(i, static_cast<TTypeOther>(0));
        }
#if __cplusplus >= 201709L 
    }
    else //memset optimization is not constexpr
    {
        std::memset(&result[minLenght], 0, sizeof(TTypeOther) * TLengthOther - minLenght);
    }
#endif

    return result;
}


template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> const& vec) noexcept
{
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> vec) noexcept
{
    return vec *= static_cast<TType>(-1);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec += static_cast<TType>(scalar); 
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator+(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) + vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs += rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec -= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator-(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) - vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> lhs, const GenericVector<TLength, TType>& rhs) noexcept
{
    return lhs -= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator*(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec *= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator*(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) * vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator*(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs *= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator/(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec /= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator/(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) / vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator/(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs /= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator%(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec %= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator%(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) % vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator%(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs %= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator&(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec &= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator&(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) & vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator&(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs &= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator|(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec |= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator|(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) | vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator|(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs |= rhs;
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator^(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec ^= static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator^(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) ^ vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator^(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs ^= rhs;
}


template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator<<(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec << static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator<<(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) << vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator<<(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs << rhs;
}


template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator>>(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept
{
    return vec >> static_cast<TType>(scalar);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
GenericVector<TLength, TType> operator>>(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, static_cast<TType>(scalar) >> vec[i]);
    }
    
    return vec;
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
inline constexpr
GenericVector<TLength, TType> operator>>(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs >> rhs;
}


template <size_t TLength, typename TType>
inline constexpr
GenericVector<TLength, TType> operator~(GenericVector<TLength, TType> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, ~vec[i]);
    }
    
    return vec;
}

template <size_t TLength>
inline constexpr
GenericVector<TLength, bool> operator!(GenericVector<TLength, bool> vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        vec.setData(i, !vec[i]);
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

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator==(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
#ifdef VECTOR_OPERATOR_EGALE_COMPARE_LENGTH

    return isSame<TType>(lhs.squareLength(), static_cast<TType>(rhs.squareLength()));

#else

    bool rst = true;

    for (size_t i = 0; i < TLength && rst; i++)
    {
        rst &= lhs.setData(i, static_cast<TType>(rhs[i]));
    }

    return rst;

#endif
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
bool operator==(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return isSame<TType>(vec.squareLength(), static_cast<TType>(scalar) * static_cast<TType>(scalar)); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
inline constexpr
bool operator==(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return isSame<TType>(static_cast<TType>(scalar) * static_cast<TType>(scalar), vec.squareLength()); //hack to avoid sqrt
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator!=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return !(lhs == rhs);
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator!=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return !(vec == static_cast<TType>(scalar));
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator!=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return !(static_cast<TType>(scalar) == vec);
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator<(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squareLength() < static_cast<TType>(rhs.squareLength());
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squareLength() < static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) < vec.squareLength(); //hack to avoid sqrt
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator>(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squareLength() > static_cast<TType>(rhs.squareLength());
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squareLength() > static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) > vec.squareLength(); //hack to avoid sqrt
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator<=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squareLength() <= static_cast<TType>(rhs.squareLength());
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squareLength() <= static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator<=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) <= vec.squareLength(); //hack to avoid sqrt
}

template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
[[nodiscard]] inline constexpr
bool operator>=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept
{
    return lhs.squareLength() >= static_cast<TType>(rhs.squareLength());
}


template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept
{
    return vec.squareLength() >= static_cast<TType>(scalar) * static_cast<TType>(scalar); //hack to avoid sqrt
}

template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
[[nodiscard]] inline constexpr
bool operator>=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept
{
    return static_cast<TType>(scalar) * static_cast<TType>(scalar) >= vec.squareLength(); //hack to avoid sqrt
}


template <size_t TLength, typename TType>
inline constexpr
std::ostream& 	operator<<		(std::ostream& out, const GenericVector<TLength, TType>& vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        out << vec[i] << "  ";
    }

    return out;  
}

template <size_t TLength, typename TType>
inline constexpr
std::istream& 	operator>>		(std::istream& in, const GenericVector<TLength, TType>& vec) noexcept
{
    for (size_t i = 0; i < TLength; i++)
    {
        in >> vec[i];
    }

    return in;  
}