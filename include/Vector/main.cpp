#include <iostream>
#include "Vector.hpp"

int main() 
{
    FoxMath::Vector::Vector<3, int> vec;
    vec[2] = 3;
    std::cout << vec[2] << std::endl;
}