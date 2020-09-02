#include <iostream>
#include <iomanip>

#include "Matrix/Vector/NewGenericVector.hpp"
#include "Matrix/Matrix.hpp"
#include "Angle/Angle.hpp"

#include "../benchmark/include/mat.hpp"
#include "../benchmark/include/vec.hpp"

#include "Types/SFINAEShorthand.hpp"

#include <limits> //std::numeric_limits<T>::espilon()

using namespace FoxMath::Matrix;
using namespace FoxMath::Vector;
using namespace FoxMath::Angle;

int main() 
{
    Mat3<> test (  1.f, 5.f, 1.f,
                                                        5.f, 4.f, 2.f,
                                                        9.f, 8.f, 7.f);

    NewGenericVector<3> te (8.f, 7.f, 1.f);
    te *= test;

    std::cout << te << std::endl; //Wrong rst


    return 0;
}