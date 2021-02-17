#include <iostream>
#include <iomanip>

#include "Vector/Vector.hpp"
#include "Matrix/Matrix.hpp"
#include "Matrix/Vector/NewGenericVector.hpp"
#include "Angle/Angle.hpp"
#include "Random/Random.hpp"

#include "Quaternion/Quaternion.hpp"

#include "Types/SFINAEShorthand.hpp"

#include <limits> //std::numeric_limits<T>::espilon()

using namespace FoxMath;

int main() 
{
    Matrix<3, 3> mat = SquareMatrix<3>::identity();
    NewGenericVector<3> genericVector (mat.getVector(1));

    Quaternion<> q(2.f ,5.f, 6.f, 8.f);
    std::cout << genericVector << std::endl;

    for (size_t i = 0; i < 20; i++)
    {
        std::cout << Random::ranged<int>(5, 10) << std::endl;
    }

    return 0;
}