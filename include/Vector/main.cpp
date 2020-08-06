#include <iostream>
#include "Vector.hpp"

int main() 
{
    FoxMath::Vector::Vector<22, double> vec3;
    FoxMath::Vector::Vector<10, int> vec (15, 8, 1);
    FoxMath::Vector::Vector<2, float> vec2 = static_cast<FoxMath::Vector::Vector<2, float>>(vec);
    std::cout << vec << std::endl;
    vec2 -= 2.f;

    std::cout << vec2 << std::endl;
    std::cout << vec3 << std::endl;
    std::cout << (vec == vec3) << std::endl;
}