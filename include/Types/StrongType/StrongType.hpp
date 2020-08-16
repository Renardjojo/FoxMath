/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-16 - 11 h 02
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

#include "Types/SFINAEShorthand.hpp"
#include <type_traits> //std::is_nothrow_copy_constructible_v, is_nothrow_copy_assignable_v, is_nothrow_move_assignable_v...

namespace FoxMath::Type::StrongType
{
    /**
     * @brief A strong type allows the creation of strong types more easily
     * 
     * Every method is constexpr and noexcept if the base type is noexcept as well
     * 
     * To create a "complex" StrongType, simply inherit from this class and overload all the required operators.
     * Do note that every operator class like Addition or Modulo, can also be inherited to save you some time.
     * 
     * @example :
     * // This class is strongly typed and only has the addition and subtraction operators available
     * struct Meter : StrongType<float, Meter>, Addition<Meter>, Subtraction<Meter>
     * { using StrongType::StrongType };
     * 
     * @tparam TBase Base type, could be any fundamental type
     * @tparam TUniquePhantom Phantom type, this should be unique for each type
     * 
     * @see https://foonathan.net/blog/2016/10/19/strong-typedefs.html
     * @see https://arne-mertz.de/2016/11/stronger-types/
     * @see https://github.com/Renondedju/PotatoMaths/blob/dev/PotatoMaths/PotatoMaths/Source/Include/Types/NamedType.hpp
     */
    template <typename TBase, class TPhantom>
    class StrongType
    {
        private:

        protected:

        #pragma region attribut
        #pragma endregion //!attribut

        #pragma region static attribut
        #pragma endregion //! static attribut

        #pragma region methods

        TBase m_value;

        #pragma endregion //!methods

        public:

        #pragma region constructor/destructor

        StrongType ()					                    = default;
        StrongType (const StrongType& other)			    = default;
        StrongType (StrongType&& other)				        = default;
        ~StrongType ()				                        = default;
        StrongType& operator=(StrongType const& other)		= default;
        StrongType& operator=(StrongType && other)			= default;


		/**
		 * @brief Constructs the content of the StrongType using the following constructor: TStrongType(TArgs...)
		 * @tparam TArgs Arguments type
		 * @param in_args arguments
		 */
		template <typename ...TArgs, Type::IsConstructible<TBase, TArgs...> = true>
		constexpr StrongType(TArgs&&... in_args) noexcept(noexcept(TBase(std::forward<TArgs>(in_args)...)));

		/**
		 * @brief Base init constructor
		 * @param in_base base value
		 */
		explicit constexpr StrongType(TBase const& in_base) noexcept(noexcept(TBase(in_base)));

		/**
		 * @brief Explicit const expression copy operator.
		 * This operator is noexcept if the corresponding base type operator is noexcept itself
		 * 
		 * @param in_copy Value to copy from
		 */
		explicit constexpr StrongType(StrongType const&	in_copy) noexcept(std::is_nothrow_copy_constructible_v<TBase>);
	
		/**
		 * @brief Explicit const expression move operator.
		 * This operator is noexcept if the corresponding base type operator is noexcept itself
		 * 
		 * @param in_move Value to move from
		 */
		explicit constexpr StrongType(StrongType&&		in_move) noexcept(std::is_nothrow_move_constructible_v<TBase>);

		// Default constructor / destructor
		constexpr StrongType () noexcept(std::is_nothrow_constructible_v<TBase>);

        #pragma endregion //!constructor/destructor

        #pragma region methods
        #pragma endregion //!methods

        #pragma region accessor
        #pragma endregion //!accessor

        #pragma region mutator
        #pragma endregion //!mutator

        #pragma region operator
        #pragma endregion //!operator

        #pragma region convertor

		explicit constexpr operator TBase&       ()		  noexcept;
		explicit constexpr operator TBase const& () const noexcept;

		constexpr StrongType& operator=(StrongType const&	in_copy) noexcept(std::is_nothrow_copy_assignable_v<TBase>);
		constexpr StrongType& operator=(StrongType&&		in_move) noexcept(std::is_nothrow_move_assignable_v<TBase>);

        #pragma endregion //!convertor

    };

    template <typename TTag, typename TBase>
    TBase UnderlyingTypeImpl(StrongType<TTag, TBase>);

    template <typename T>
    using UnderlyingType = decltype(UnderlyingTypeImpl(std::declval<T>());

    #include "StrongType.inl"

} /*namespace FoxMath::Type::StrongType*/
