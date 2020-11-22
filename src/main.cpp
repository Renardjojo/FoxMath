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
    std::cout << q1.getInverse() << std::endl;
    Vector3<double> vec {58., 1., -9.};
    Vector3<double> vec2 {58., 1., -9.};
    Vector3<double> axis {0., 0.5, 0.5};
    std::cout << q1 * vec << std::endl;
    axis.normalize();

    Quaternion<double>::RotateVector(vec, axis, 3_rad);
    Quaternion<double>::RotateVector2(vec2, axis, 3_rad);
    std::cout << vec << std::endl;
    std::cout << vec2 << std::endl;
    std::cout << "-5.34911, 6.51895, 9.48105" << std::endl;


    Quaternion<double> q4(Vector3<double>{0., 0.5, 0.5}, 3_rad);
    std::cout << q4 << std::endl;
    std::cout << q4.getRotationMatrix() << std::endl;
    return 0;
}