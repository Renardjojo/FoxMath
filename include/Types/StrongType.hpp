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

namespace FoxMath
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
     * { using StrongStrongType };
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

        TBase m_value;

        #pragma endregion //!attribut

        public:

        #pragma region constructor/destructor

        constexpr inline StrongType ()	 noexcept(std::is_nothrow_constructible_v<TBase>) = default;
        /**
         * @brief This operator is noexcept if the corresponding base type operator is noexcept itself
         * 
         */

        constexpr inline StrongType (const StrongType& other) noexcept(std::is_nothrow_copy_constructible_v<TBase>) = default;

        /**
         * @brief This operator is noexcept if the corresponding base type operator is noexcept itself
         * 
         */
        constexpr inline StrongType (StrongType&& other) noexcept(std::is_nothrow_move_constructible_v<TBase>) = default;

        inline ~StrongType ()	noexcept = default;

        /**
         * @brief This operator is noexcept if the corresponding base type operator is noexcept itself
         * 
         */
        constexpr inline StrongType& operator=(StrongType const& other)	noexcept(std::is_nothrow_copy_assignable_v<TBase>) = default;
        
        /**
         * @brief This operator is noexcept if the corresponding base type operator is noexcept itself
         * 
         */
        constexpr inline StrongType& operator=(StrongType && other)		noexcept(std::is_nothrow_move_assignable_v<TBase>) = default;


		/**
		 * @brief Constructs the content of the StrongType using the following constructor: TStrongType(TArgs...)
		 * @tparam TArgs Arguments type
		 * @param in_args arguments
		 */
		template <typename ...TArgs, IsConstructible<TBase, TArgs...> = true>
		explicit constexpr StrongType(TArgs&&... in_args) noexcept(noexcept(TBase(std::forward<TArgs>(in_args)...)));

		/**
		 * @brief Base init constructor
		 * @param in_base base value
		 */
		explicit constexpr StrongType(TBase const& in_base) noexcept(noexcept(TBase(in_base)));

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

		constexpr explicit inline 
        operator TBase&       ()	    noexcept;
		
        constexpr explicit inline 
        operator TBase const& () const  noexcept;

        #pragma endregion //!convertor

    };

	/**
	 * @brief Implementation of the UnderlyingType method
	 * @tparam TBase Base type of the NamedType
	 * @tparam TUniquePhantom Phantom type of the NamedType
	 * @return Base type of the NamedType
	 */
	template <typename TBase, typename TUniquePhantom>
	constexpr TBase UnderlyingTypeImpl(StrongType<TBase, TUniquePhantom>);

	/**
	 * @brief UnderlyingType helper method, this is used internally to get the underlying type of complex NamedType types
	 * 
	 * This has to be used instead of NamedUnderlyingType since complex NamedTypes inherits from the NamedType class.
	 * This methods avoids the issue of ill-formed types.
	 * 
	 * @see This wonderful article, where everything is nicely explained : https://foonathan.net/blog/2016/10/19/strong-typedefs.html
	 * @tparam TStrongType Base type of the NamedType
	 */
	template <typename TStrongType>
	using UnderlyingType = decltype(UnderlyingTypeImpl(std::declval<TStrongType>()));

    #include "StrongType.inl"

} /*namespace FoxMath*/
