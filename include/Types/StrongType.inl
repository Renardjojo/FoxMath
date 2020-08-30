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

template <typename TBase, class TPhantom>
template <typename ...TArgs, Type::IsConstructible<TBase, TArgs...>>
constexpr StrongType<TBase, TPhantom>::StrongType(TArgs&&... in_args) noexcept(noexcept(TBase(std::forward<TArgs>(in_args)...)))
:	m_value {TBase(std::forward<TArgs>(in_args)...)}
{}

template <typename TBase, class TPhantom>
constexpr StrongType<TBase, TPhantom>::StrongType(TBase const& in_base) noexcept(noexcept(TBase(in_base)))
:	m_value {in_base}
{}

template <typename TBase, class TPhantom>
constexpr StrongType<TBase, TPhantom>::operator TBase&() noexcept
{
	return m_value;
}

template <typename TBase, class TPhantom>
constexpr StrongType<TBase, TPhantom>::operator TBase const& () const noexcept
{
	return m_value;	
}