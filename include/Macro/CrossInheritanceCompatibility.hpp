/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-27 - 10 h 37
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

/**
 * @brief Use this macro is you want a cross compatibility through inheritance.
 * i.g. if both class is the same type with a largest interface like genericMatrix with SquareMatrix.
 * To use it, simple declare near your child's class constructors this template with the corresponding paramters.
 * 
 * @param childType class requiring the compatibility
 * @param childType class requiring the compatibility
 * @param parentType Parent class with template arg
 * @param parentTypeName Parent class name only
 * 
 */
#define DECLARE_CROSS_INHERITANCE_COMPATIBILTY(childType, parentType, parentTypeName)      \
    DECLARE_CROSS_INHERITANCE_COMPATIBILITY_COPY_CONSTRUCTOR(childType, parentType)        \
    DECLARE_CROSS_INHERITANCE_COMPATIBILITY_MOVE_CONSTRUCTOR(childType, parentType)        \
    DECLARE_CROSS_INHERITANCE_COMPATIBILITY_COPY_OPERATOR(childType, parentType)           \
    DECLARE_CROSS_INHERITANCE_COMPATIBILITY_MOVE_OPERATOR(childType, parentType)           \
    DECLARE_CROSS_INHERITANCE_COMPATIBILITY_OTHER_CONSTRUCTOR(parentType, parentTypeName)  \
    DECLARE_CROSS_INHERITANCE_COMPATIBILITY_OTHER_AFFECTATION_OPERATOR(parentType)
    
/**
 * @brief Declares a compatibility copy constructor 
 * @param childType class requiring the compatibility
 * @param parentType Parent class
 */
#define DECLARE_CROSS_INHERITANCE_COMPATIBILITY_COPY_CONSTRUCTOR(childType, parentType) \
constexpr inline childType(parentType const& other) noexcept                            \
    :  parentType(other)                                                                \
{}

/**
 * @brief Declares a compatibility move constructor 
 * @param childType class requiring the compatibility
 * @param parentType Parent class
 */
#define DECLARE_CROSS_INHERITANCE_COMPATIBILITY_MOVE_CONSTRUCTOR(childType, parentType) \
    constexpr inline childType(parentType&& other) noexcept                             \
    :  parentType(std::forward<parentType>(other))                                      \
{}

/**
 * @brief Declares a compatibility copy operator
 * @param childType class requiring the compatibility
 * @param parentType Parent class
 */
#define DECLARE_CROSS_INHERITANCE_COMPATIBILITY_COPY_OPERATOR(childType, parentType) \
    constexpr inline childType& operator=(parentType const& other) noexcept \
    { parentType::operator=(other); return *this; }

/**
 * @brief Declares a compatibility move operator 
 * @param childType class requiring the compatibility
 * @param parentType Parent class
 */
#define DECLARE_CROSS_INHERITANCE_COMPATIBILITY_MOVE_OPERATOR(childType, parentType) \
    constexpr inline childType& operator=(parentType&& other) noexcept \
    { parentType::operator=(std::forward<parentType>(other)); return *this; }
/**
 * @brief Declares a compatibility with all other parent constructor
 * @param parentType Parent class with template arg
 * @param parentTypeName Parent class name only
 */
#define DECLARE_CROSS_INHERITANCE_COMPATIBILITY_OTHER_CONSTRUCTOR(parentType, parentTypeName) \
    using parentType::parentTypeName;

/**
 * @brief Declares a compatibility with all other parent affection operator
 * @param parentType Parent class
 */
#define DECLARE_CROSS_INHERITANCE_COMPATIBILITY_OTHER_AFFECTATION_OPERATOR(parentType) \
    using parentType::operator=;
