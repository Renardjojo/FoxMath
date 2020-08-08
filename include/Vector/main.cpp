#include <iostream>
#include "Vector.hpp"

int main() 
{
    FoxMath::Vector::Vector<3, float> vect (3.f, 5.f, 10.f);
    constexpr FoxMath::Vector::Vector<3, float> constVect (3.f, 5.f, 10.f);
    constexpr FoxMath::Vector::Vector<3, float> constVect2  (5.f, 5.f);
    
    constexpr auto value = constVect.getReflection(FoxMath::Vector::Vector<3, float>(0.f, 1.f, 0.f));
    static_assert(value.length(), "is_constexpr<true>(0)");
    

    std::cout << FoxMath::Vector::Vector<3, float>::cross(value,constVect) << std::endl;
    std::cout << value.isPerpendicularTo(constVect2) << std::endl;
    std::cout << value.length() << std::endl;
    std::cout << vect.normalize() << std::endl;
    std::cout << value.getNormalized() << std::endl;
    std::cout << vect.clampLength(10) << std::endl;
    std::cout << value.getClampedLength(10).length() << std::endl;
    std::cout << value.dot(constVect2) << std::endl;
    std::cout << vect.cross(constVect2) << std::endl;
    std::cout << value.getCross(constVect2) << std::endl;
    std::cout << vect.lerp(constVect2, 0.5f) << std::endl;
    std::cout << value.getLerp(constVect2, 0.5f) << std::endl;
    std::cout << vect.reflect(constVect2.getNormalized()) << std::endl;
    std::cout << value.getReflection(constVect2.getNormalized()) << std::endl;
    std::cout << vect.setLength(10) << std::endl;
    std::cout << value.isColinearTo(constVect2) << std::endl;
    std::cout << value.isPerpendicularTo(constVect2) << std::endl;
    std::cout << value.getParallelogramArea(constVect2) << std::endl;
    std::cout << value.getTriangleArea(constVect2) << std::endl;
    std::cout << vect.rotateAroundAxis(constVect2.getNormalized(), 3.f) << std::endl;
    std::cout << value.getRotationAroundAxis(constVect2.getNormalized(), 3.f) << std::endl;
    std::cout << value.getScalarProjectionWith(constVect2) << std::endl;
    std::cout << value.getScalarRejectionWith(constVect2) << std::endl;
    std::cout << value.getVectorProjectionWith(constVect2) << std::endl;
    std::cout << value.getVectorRejectionWith(constVect2) << std::endl;
}