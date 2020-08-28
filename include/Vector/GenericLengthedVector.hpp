/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-28 - 10 h 03
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

#include "Vector/GenericVector.hpp"
#include "Macro/CrossInheritanceCompatibility.hpp"


namespace FoxMath::Vector
{
    /**
     * @brief Lengthed vector save vector length. This fact optimize length computation of vector but use more memory to save this variable. Use it if you want to know frequently the vector length with vector that don't move between each length check
     * 
     * @tparam TLength 
     * @tparam TType 
     */
    template <size_t TLength, typename TType>
    class GenericLengthedVector final : public GenericVector<TLength, TType>
    {
        private:
    
        using Parent = GenericVector<TLength, TType>;

        protected:
    
        #pragma region attribut

        TType   m_length;
        bool    m_lengthIsDirty = true;

        #pragma endregion //!attribut
        
        public:
    
        #pragma region constructor/destructor
    
        constexpr inline
        GenericLengthedVector () noexcept 					                            = default;
    
        constexpr inline
        GenericLengthedVector (const GenericLengthedVector& other) noexcept		        = default;
    
        constexpr inline
        GenericLengthedVector (GenericLengthedVector&& other) noexcept				    = default;
    
        inline
        ~GenericLengthedVector () noexcept				                                = default;
    
        constexpr inline
        GenericLengthedVector& operator=(GenericLengthedVector const& other) noexcept	= default;
    
        constexpr inline
        GenericLengthedVector& operator=(GenericLengthedVector && other) noexcept		= default;

        DECLARE_CROSS_INHERITANCE_COMPATIBILTY(GenericLengthedVector, Parent, GenericVector)
    
        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        /**
         * @brief Deprecated to avoid compare distance hack (Less optimized than check directly the length). 
         * If you really want the squart length ask it explicitely with length() * length()
         * 
         */
        TType squartLength () const noexcept = delete;

        #pragma endregion //!methods

        #pragma region accessor

        /**
         * @brief return magnitude of the generic vector 
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType length () const noexcept
        {
            if (m_lengthIsDirty)
            {
                m_length = GenericVector<TLength, TType>::length();
                m_lengthIsDirty = false;
            }

            return m_length;
        }

        #pragma endregion //!accessor
    
        #pragma region mutator

        /**
         * @brief Set the Data a index
         * 
         * A similar member function, GenericVector::setDataAt, has the same behavior as this operator function,
         * except that GenericVector::setDataAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param index 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& setData(size_t index, TscalarType scalar) noexcept
        {
            assert(index < TLength);

            Parent::m_data[index] = static_cast<TType>(scalar);
            m_lengthIsDirty = true;
            return *this;
        }


        /**
         * @brief Set the Data at index
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericVector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with function GenericVector::setData, that does not check against bounds.
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param index 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& setDataAt(size_t index, TscalarType scalar) throw ()
        {
            if (index < TLength) [[likely]]
            {
                Parent::m_data[index] = static_cast<TType>(scalar);
                m_lengthIsDirty = true;
                return *this;
            }

            std::__throw_out_of_range_fmt(__N("GenericVector::at: index"
                            "(which is %zu) >= TLength "
                            "(which is %zu)"),
                                index, TLength);
        }

        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma region member access operators
        #pragma endregion //!member access operators
        #pragma region  assignment operators

        /**
         * @brief fill the vector with scalar assigned
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return implicit constexpr& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		implicit inline constexpr
		GenericLengthedVector& operator=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator=(scalar);
        }

        /**
         * @brief addition assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator+=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator+=(scalar);
        }

        /**
         * @brief addition assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator+=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator+=(other);
        }

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator-=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator-=(scalar);
        }

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator-=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator-=(other);
        }

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator*=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator*=(scalar);
        }

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator*=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator*=(other);
        }

        /**
         * @brief division assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator/=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator/=(scalar);
        }

        /**
         * @brief division assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator/=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator/=(other);
        }

        /**
         * @brief modulo assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator%=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator%=(scalar);
        }

        /**
         * @brief modulo assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator%=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator%=(other);
        }

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator&=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator&=(scalar);
        }

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator&=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator&=(other);
        }

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator|=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator|=(scalar);
        }

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator|=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator|=(other);
        }

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator^=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator^=(scalar);
        }

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator^=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator^=(other);
        }

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator<<=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator<<=(scalar);
        }

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator<<=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator<<=(other);
        }

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericLengthedVector& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericLengthedVector& operator>>=(TscalarType scalar) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator>>=(scalar);
        }

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericLengthedVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericLengthedVector& operator>>=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator>>=(other);
        }

        #pragma endregion //!region assignment operators
        #pragma region increment decrement operators

        /**
         * @brief  pre-increment operator
         * 
         * @return constexpr GenericLengthedVector& 
         */
        inline constexpr
		GenericLengthedVector& 	operator++	() noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator++();
        }

        /**
         * @brief pre-decrement operator
         * 
         * @return constexpr GenericLengthedVector& 
         */
        inline constexpr
		GenericLengthedVector& 	operator--	() noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator--();
        }
        
        /**
         * @brief post-increment  operator
         * 
         * @return constexpr GenericLengthedVector 
         */
        inline constexpr
		GenericLengthedVector 	    operator++	(int) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator++();
        }

        /**
         * @brief post-decrement operator
         * 
         * @return constexpr GenericLengthedVector 
         */
        inline constexpr
		GenericLengthedVector 	    operator--	(int) noexcept
        {
            m_lengthIsDirty = true;
            return Parent::operator--();
        }

        #pragma endregion //!increment decrement operators
        #pragma endregion //!operators
    
        #pragma region convertor
        #pragma endregion //!convertor
    
    };
} /*namespace FoxMath::Vector*/
