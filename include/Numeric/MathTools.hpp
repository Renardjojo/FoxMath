//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-04-30 - 10 h 35

#ifndef _MATHS_TOOLS_H
#define _MATHS_TOOLS_H

#include "Vector/Vector.hpp"

namespace FoxMath
{
    /*isBetween(5, 0, 10) runtime*/
    template<class T = float>
    T isBetween(T number, T low, T up)
    {
        return number >= low && number <= up;
    }

    /*isBetween<0, 10>(5) compile time*/
    template<typename T = float, T Min, T Max>
    auto isBetween(T value) -> std::enable_if_t<Min <= Max, bool>
    {
        return value >= Min && value <= Max;
    }

    template <typename T>
    inline T unrolledIf(bool condition, T valIfTrue, T valIfFalse)
    {
        return condition * valIfTrue + !condition * valIfFalse;
    }
}

#endif //!_MATHS_TOOLS_H
