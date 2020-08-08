#include <iostream>
#include "Vector.hpp"

constexpr bool test_constexpr(bool make_constexpr) {
   return make_constexpr ? true : throw 0;
}

template <bool Arg, bool = test_constexpr(Arg)>
   constexpr bool is_constexpr(int) {
      return true;
   }
template <bool Arg>
   constexpr bool is_constexpr(...) {
      return false;
   }

int main() 
{/*
    FoxMath::Vector::Vector<22, double> vec3;
    FoxMath::Vector::Vector<10, int> vec;
    FoxMath::Vector::Vector<2, double> vec2 = static_cast<FoxMath::Vector::Vector<2, double>>(vec);
    std::cout << vec << std::endl;
    vec2 += -9.8948448918184148948;
    float a = 7ul;
    std::cout << a << std::endl;
    std::cout << vec2 << std::endl;
    std::cout << vec3 << std::endl;
    
    FoxMath::Vector::Vector<10, int> vect(FoxMath::Vector::Vector<5, int>(), 22, 31);
    vec = vect.normalize();
*/

    constexpr FoxMath::Vector::Vector<3, float> constVect (3.f, 5.f, 10.f);
    constexpr FoxMath::Vector::Vector<3, float> constVect2  (5.f, 5.f);
    
    constexpr auto value = constVect.getReflection(FoxMath::Vector::Vector<3, float>(0.f, 1.f, 0.f));
    static_assert(value.length(), "is_constexpr<true>(0)");
    

    std::cout << FoxMath::Vector::Vector<3, float>::cross(value,constVect) << std::endl;
    std::cout << value.getCross(constVect2) << std::endl;
}