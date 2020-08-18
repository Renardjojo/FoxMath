#include <iostream>
#include "Vector/GenericVector.hpp"
#include "Vector/Vector2.hpp"
#include "Vector/Vector3.hpp"
#include "Vector/Vector4.hpp"
#include "Angle/Angle.hpp"

using namespace FoxMath::Vector;
using namespace FoxMath::Angle;

int main() 
{
    /*Generic vector sandbox*/
    {
        std::cout << std::endl << std::endl << "Generic vector sandbox" << std::endl;
        Vector<3, float> vect (3.f, 5.f, 10.f);
        constexpr Vector<3, float> constVect (3.f, 5.f, 10.f);
        constexpr Vector<3, float> constVect2  (5.f, 5.f);
        
        constexpr auto value = constVect.getReflection(Vector<3, float>(0.f, 1.f, 0.f));
        static_assert(constVect.length(), "is_constexpr<true>(0)");
        
        std::cout << value.at(4) << std::endl;
        std::cout << value[2] << std::endl;
        std::cout << Vector<3, float>::cross(value,constVect) << std::endl;
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
        std::cout << vect.homogenize() << std::endl;
        std::cout << value.getHomogenized() << std::endl;
        std::cout << value.isColinearTo(constVect2) << std::endl;
        std::cout << value.isPerpendicularTo(constVect2) << std::endl;
        std::cout << value.getParallelogramArea(constVect2) << std::endl;
        std::cout << value.getTriangleArea(constVect2) << std::endl;
        std::cout << vect.rotateAroundAxis(constVect2.getNormalized(), 3_rad) << std::endl;
        std::cout << value.getRotationAroundAxis(constVect2.getNormalized(), 3_deg) << std::endl;
        std::cout << value.getScalarProjectionWith(constVect2) << std::endl;
        std::cout << value.getScalarRejectionWith(constVect2) << std::endl;
        std::cout << value.getVectorProjectionWith(constVect2) << std::endl;
        std::cout << value.getVectorRejectionWith(constVect2) << std::endl;
    }

    /*Compatibility sandbox*/
    {
        std::cout << std::endl << std::endl << "Compatibility sandbox" << std::endl;
        Vec2f  vec2f (1.f, 2.f);
        Vec3f  vec3f(vec2f, 3.f);
        Vec4f  vec4f (vec3f, 4.f);
        
        Vector<2, float>  baseVec2f (1.f, 2.f);
        Vector<3, float>  baseVec3f (baseVec2f, 3.f);
        Vector<4, float>  baseVec4f (baseVec3f, 4.f);

        /*constuctor*/
        {
            std::cout << std::endl << std::endl << "constuctor" << std::endl;
            Vector<2, float>  baseVec2ff (vec2f);
            Vector<3, float>  baseVec3ff (vec3f);
            Vector<4, float>  baseVec4ff (vec4f);

            Vec2f  vec2ff (baseVec2f);
            Vec3f  vec3ff (baseVec3f);
            Vec4f  vec4ff (baseVec4f);

            Vector<3, float>  baseVec3fff (vec2f);
            Vector<4, float>  baseVec4fff (vec3f);

            Vec3f  vec3fff (baseVec2f);
            Vec4f  vec4fff (baseVec3f);

            Vector<2, float>  baseVec2ffff (vec3f);
            Vector<3, float>  baseVec3ffff (vec4f);

            Vec2f  vec2ffff (baseVec3f);
            Vec3f  vec3ffff (baseVec4f);
        }  
    
        /*Static_cast*/
        {
            std::cout << std::endl << std::endl << "Static_cast" << std::endl;
            Vector<2, float>  baseVec2ff (static_cast<Vector<2, float>>(vec2f));
            Vector<3, float>  baseVec3ff (static_cast<Vector<3, float>>(vec3f));
            Vector<4, float>  baseVec4ff (static_cast<Vector<4, float>>(vec4f));

            Vec2f  vec2ff (static_cast<Vec2f>(baseVec2f));
            Vec3f  vec3ff (static_cast<Vec3f>(baseVec3f));
            Vec4f  vec4ff (static_cast<Vec4f>(baseVec4f));

            Vector<3, float>  baseVec3fff (static_cast<Vector<3, float>>(vec2f));
            Vector<4, float>  baseVec4fff (static_cast<Vector<4, float>>(vec3f));

            Vec3f  vec3fff (static_cast<Vec3f>(baseVec2f));
            Vec4f  vec4fff (static_cast<Vec4f>(baseVec3f));

            Vector<2, float>  baseVec2ffff (static_cast<Vector<2, float>>(vec3f));
            Vector<3, float>  baseVec3ffff (static_cast<Vector<3, float>>(vec4f));

            Vec2f  vec2ffff (static_cast<Vec2f>(baseVec3f));
            Vec3f  vec3ffff (static_cast<Vec3f>(baseVec4f));
        }  

        /*operator =*/
        {
            std::cout << std::endl << std::endl << "operator =" << std::endl;
            Vector<2, float>  baseVec2ff = vec2f;
            Vector<3, float>  baseVec3ff = vec3f;
            Vector<4, float>  baseVec4ff = vec4f;

            Vec2f  vec2ff = baseVec2f;
            Vec3f  vec3ff = baseVec3f;
            Vec4f  vec4ff = baseVec4f;

            Vector<3, float>  baseVec3fff = vec2f;
            Vector<4, float>  baseVec4fff = vec3f;

            Vec3f  vec3fff = baseVec2f;
            Vec4f  vec4fff = baseVec3f;

            Vector<2, float>  baseVec2ffff = vec3f;
            Vector<3, float>  baseVec3ffff = vec4f;

            Vec2f  vec2ffff = baseVec3f;
            Vec3f  vec3ffff = baseVec4f;
        }

        std::cout << vec2f << std::endl;
        std::cout << vec3f << std::endl;
        std::cout << vec4f << std::endl;

        std::cout << baseVec2f << std::endl;
        std::cout << baseVec3f << std::endl;
        std::cout << baseVec4f << std::endl;
    }


    /*Specifique Vector2 methode sandbox*/
    {
        std::cout << std::endl << std::endl << "Specifique Vector2 methode sandbox" << std::endl;

        Vec2i vec(0, 1);
        Vec2i vecU(1, 0);

        int a = static_cast<int>(3_deg);
        std::cout << a << std::endl;

        std::cout << vec.getRotationAroundAxis(vecU, 3_deg) << std::endl;
    }

    /*Angle sandbox*/
    {
        std::cout << std::endl << std::endl << "Angle sandbox" << std::endl;

        int a = 5;
        Angle<EAngleType::Degree, float> angle = 3_deg;
        std::cout << angle << std::endl;
        
        angle += 3.14_rad;
        std::cout << angle << std::endl;
        
        angle -= 3_rad;
        std::cout << angle << std::endl;
        
        angle += 50.6_deg;
        std::cout << angle << std::endl;
        
        angle += Angle<EAngleType::Radian, float>(a);
        std::cout << angle << std::endl;
    }
}