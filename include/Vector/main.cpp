#include <iostream>
#include "Vector.hpp"

int main() 
{
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
    std::cout << vect << std::endl;
}