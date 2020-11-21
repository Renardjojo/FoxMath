#include <iostream>
#include <iomanip>

#include "Vector/Vector.hpp"
#include "Matrix/Matrix.hpp"
#include "Angle/Angle.hpp"

#include "../benchmark/include/mat.hpp"
#include "../benchmark/include/vec.hpp"

#include "Quaternion/Quaternion.hpp"

#include "Types/SFINAEShorthand.hpp"

#include <limits> //std::numeric_limits<T>::espilon()

using namespace FoxMath::Matrix;
using namespace FoxMath::Vector;
using namespace FoxMath::Angle;
using namespace FoxMath::Quaternion;

int main() 
{
    /*
    Mat3<> test (  1.f, 5.f, 1.f,
                                                        5.f, 4.f, 2.f,
                                                        9.f, 8.f, 7.f);

    NewGenericVector<3> te (9.f, 7.f, 1.f);
    te *= test;

    std::cout << te << std::endl; //Wrong rst*/

    Quaternion<> q1 (Vector3<>(0.f, 0.5f, 0.5f), 3_rad);
    Quaternion<> q2 (Vector3<>(2.f, 1.f, 0.f), 6_rad);

    std::cout << q1 << std::endl;
    std::cout << q1.getAxis() << std::endl;    
    std::cout << q1.getAngle() << std::endl;

    std::cout << q1 + q2 << std::endl;
    std::cout << q1 - q2 << std::endl;
    std::cout << q1 * q2 << std::endl;
    std::cout << q2 * q1 << std::endl;
    std::cout << q2 * 5 << std::endl;
    Quaternion<> q3 = q2 * 5.f;
    std::cout << q3.getMagnitude() << std::endl;
    std::cout << q3.isRotation() << std::endl;
    q3.normalize();
    std::cout << q3.isRotation() << std::endl;
    std::cout << q3.conjugate() << std::endl;
    q1 = Quaternion<>(1.f, 2.f, 3.f, 4.f);
    std::cout << q1 << std::endl;
    std::cout << q1.inverse() << std::endl;
    return 0;
}