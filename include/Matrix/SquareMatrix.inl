/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-24 - 14 h 53
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

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
TType		SquareMatrix<TSize, TType, TMatrixConvention>::getMinor		(size_t i, size_t j) const noexcept
{
    const size_t newSizesubMatrix = TSize - 1;
	SquareMatrix<newSizesubMatrix, TType, TMatrixConvention> subMatrix;
	//fill submatrix
	bool coefLineFound = false;
	bool coefRowFound = false;

	for (size_t iSubMatrix = 0; iSubMatrix < newSizesubMatrix; iSubMatrix++)
	{
		if (iSubMatrix == i)
			coefLineFound = true;

		for (size_t jSubMatrix = 0; jSubMatrix < newSizesubMatrix; jSubMatrix++)
		{
			if (jSubMatrix == j)
				coefRowFound = true;

			subMatrix.getData(iSubMatrix * newSizesubMatrix + jSubMatrix) = Parent::m_data[(iSubMatrix + coefLineFound) * TSize + jSubMatrix + coefRowFound];
		}
		coefRowFound = false;
	}

	return subMatrix.getDeterminant();
}

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
TType		SquareMatrix<TSize, TType, TMatrixConvention>::getCofactor		(size_t i, size_t j) const noexcept
{
	return std::pow(-1, i + j) * getMinor(i, j);
}

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
SquareMatrix<TSize, TType, TMatrixConvention>	SquareMatrix<TSize, TType, TMatrixConvention>::getCoMatrix		() const noexcept
{
	SquareMatrix<TSize, TType, TMatrixConvention> coMatrix;

    for ( size_t i = 0; i < TSize; i++ )
	{
        for ( size_t j = 0; j < TSize; j++ )
		{
			coMatrix.getData(i * TSize + j) = getCofactor(i, j);
		}
	}
	
	return coMatrix;
}

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
void		SquareMatrix<TSize, TType, TMatrixConvention>::tranformCoMatToAdjointMat		() noexcept
{
	transpose();
}


template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
SquareMatrix<TSize, TType, TMatrixConvention>& SquareMatrix<TSize, TType, TMatrixConvention>::generateIdentity () noexcept
{
    for ( size_t i = 0; i < TSize; i++ )
    {
        for ( size_t j = 0; j < TSize; j++ )
        {
            Parent::m_data[i * TSize + j] = ((i == j) ? static_cast<TType>(1) : static_cast<TType>(0));
        }
    }

    return *this;
}


template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
SquareMatrix<TSize, TType, TMatrixConvention>&		SquareMatrix<TSize, TType, TMatrixConvention>::transpose		() noexcept
{
    size_t shift = 1;

    for (size_t i = 0; i < TSize - 1; i++)
    {
        for (size_t j = shift; j < TSize; j++)
        {
#if __cplusplus >= 201709L //TODO: constexpr swap
            std::swap(Parent::m_data[i * TSize + j], Parent::m_data[j * TSize + i]);
#else
            if constexpr (std::is_floating_point_v<TType>)
            {
                TType temp = Parent::m_data[i * TSize + j];
                Parent::m_data[i * TSize + j] = Parent::m_data[j * TSize + i];
                Parent::m_data[j * TSize + i] = temp;
            }
            else
            {
                Parent::m_data[i * TSize + j] ^= Parent::m_data[j * TSize + i];
                Parent::m_data[j * TSize + i] ^= Parent::m_data[i * TSize + j];
                Parent::m_data[i * TSize + j] ^= Parent::m_data[j * TSize + i];
            }
#endif
        }
        shift++;
    }

    
    return *this;
}

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
bool		SquareMatrix<TSize, TType, TMatrixConvention>::isOrtho		() const noexcept
{
	const SquareMatrix<TSize, TType, TMatrixConvention> mT (Parent::getTransposed());

	return mT * (*this) == identity();
}

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
TType		SquareMatrix<TSize, TType, TMatrixConvention>::getDeterminant		() const noexcept
{
    if constexpr (TSize * TSize == 1) //Check if matrix 1*1
    {
        return Parent::getData(0);
    }
    else
    {
        TType result = static_cast<TType>(0);
        
        for (size_t i = 0; i < TSize; i++)
        {
            //found signe
            signed int signe = pow(-1, 0 + i);

            //found coef
            TType coef = signe * Parent::m_data[i * TSize];
        
            //create submatrix
            const size_t subMatrixSize = TSize - 1;
            SquareMatrix<subMatrixSize, TType, TMatrixConvention> subMatrix;

            //fill submatrix
            bool coefLineFound = false;

            for (size_t iSubMatrix = 0; iSubMatrix < subMatrixSize; iSubMatrix++)
            {
                if (iSubMatrix == i)
                    coefLineFound = true;

                for (size_t jSubMatrix = 0; jSubMatrix < subMatrixSize; jSubMatrix++)
                { 
                    subMatrix.getData(iSubMatrix * subMatrixSize + jSubMatrix) = Parent::m_data[(iSubMatrix + coefLineFound) * TSize + jSubMatrix + 1];
                }
            }

            //found determinant
            TType determinant = subMatrix.getDeterminant();

            //found result
            result += coef * determinant;
        }
        
        return result;
    }
}

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr  
SquareMatrix<TSize, TType, TMatrixConvention>		SquareMatrix<TSize, TType, TMatrixConvention>::getReverse		() const noexcept
{
	assert ((*this) != static_cast<TType>(0));

	if (isOrtho() == true)
	{
		return Parent::getTransposed();
	}

	const TType determinant = getDeterminant();
	
	if (Numeric::isSameAsZero<TType>(determinant)) //in two step for more perform
		return SquareMatrix<TSize, TType, TMatrixConvention>::zero();

	SquareMatrix<TSize, TType, TMatrixConvention> reversedMatrix = getCoMatrix();

	reversedMatrix.tranformCoMatToAdjointMat();

	reversedMatrix /= determinant;

	return reversedMatrix;
}

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
inline constexpr 
SquareMatrix<TSize, TType, TMatrixConvention>&		SquareMatrix<TSize, TType, TMatrixConvention>::reverse		() noexcept
{
	assert ((*this) != static_cast<TType>(0));

	if (isOrtho() == true)
	{
        transpose();
		return *this;
	}

	const TType determinant = getDeterminant();
	
	if (Numeric::isSameAsZero<TType>(determinant)) //in two step for more perform
    {
        Parent::fill(static_cast<TType>(0));
		return *this;
    }

	(*this) = getCoMatrix();
	tranformCoMatToAdjointMat();
	(*this) /= determinant;

    return *this;
}

template <size_t TSize, typename TType, EMatrixConvention TMatrixConvention>
template <size_t TSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
constexpr inline
SquareMatrix<TSize, TType, TMatrixConvention>::operator SquareMatrix<TSizeOther, TTypeOther, TMatrixConventionOther>() const noexcept
{
    GenericMatrix<TSizeOther, TSizeOther, TTypeOther, TMatrixConventionOther> rstConv = (*this);
    return rstConv;
}