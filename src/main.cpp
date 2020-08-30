#include <iostream>
#include <iomanip>

#include "Vector/Vector.hpp"
#include "Matrix/Matrix.hpp"
#include "Angle/Angle.hpp"

#include "Types/SFINAEShorthand.hpp"

using namespace FoxMath::Matrix;
using namespace FoxMath::Vector;
using namespace FoxMath::Angle;

int main() 
{
    /*Generic vector sandbox*/
    {
        std::cout << std::endl << std::endl << "Generic vector sandbox" << std::endl;
        Vector<3, float> vect (3.f, 5.f, 10.f);
        Vector<4, int> vectCopy = vect;
        constexpr Vector<3, float> constVect (3.f, 5.f, 10.f);
        constexpr Vector<3, float> constVect2  (5.f, 5.f);
        
        constexpr auto value = constVect.getReflection(Vector<3, float>(0.f, 1.f, 0.f));
        static_assert(constVect.length(), "is_constexpr<true>(0)");

        //constexpr Vector<0, float> constVect3 (); Don't work, vector canno't be equal to zero

        //std::cout << value.at(4) << std::endl; Do not compile
        std::cout << value.at(2) << std::endl;
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

            Vec2f  vec2ff;
            vec2ff = baseVec2f;
            vec2ff = 0.f;

            Vec3f  vec3ff;
            vec3ff = baseVec3f;
            vec3ff = 0.f;

            Vec4f  vec4ff;
            vec4ff = baseVec4f;
            vec4ff = 0.f;

            Vector<3, float>  baseVec3fff;
            baseVec3fff = vec2f;

            Vector<4, float>  baseVec4fff;
            baseVec4fff = vec3f;

            Vec3f  vec3fff;
            vec3fff = baseVec2f;

            Vec4f  vec4fff;
            vec4fff = baseVec3f;

            Vector<2, float>  baseVec2ffff;
            baseVec2ffff = vec3f;

            Vector<3, float>  baseVec3ffff;
            baseVec3ffff = vec4f;


            Vec2f  vec2ffff;
            vec2ffff = baseVec3f;

            Vec3f  vec3ffff;
            vec3ffff = baseVec4f;

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

        std::cout << vec.getRotationAroundAxis(vecU, 3_deg) << std::endl;
    }

    /*Angle sandbox*/
    {
        std::cout << std::endl << std::endl << "Angle sandbox" << std::endl;

        float a = 6.28;
        Angle<EAngleType::Degree, float> angle = 3_deg;
        std::cout << angle << std::endl;
        
        angle += 3.14_rad;
        std::cout << angle << std::endl;
        
        angle -= 3_rad;
        std::cout << angle << std::endl;
        
        angle += 50.6_deg;
        std::cout << angle << std::endl;
        
        Angle<EAngleType::Radian, float> rad (angle);
        std::cout << rad << std::endl;

        Angle<EAngleType::Radian, float> rad2 (a);
        std::cout << rad2 << std::endl;

        angle += rad2;
        std::cout << angle << std::endl;
    }

    /*Matrix sandbox*/
    {
        std::cout << std::endl << std::endl << "Matrix sandbox" << std::endl;

        std::cout << std::endl << std::endl << "Create Row major matrix" << std::endl;
        Matrix<4, 2, float, EMatrixConvention::RowMajor> matRowMajor(   1.f, 2.f,
                                                                        3.f, 4.f,
                                                                        5.f, 6.f,
                                                                        7.f, 8.f);

        std::cout << std::endl << matrixConventionToString(matRowMajor.getMatrixConvention()) << std::endl << std::setprecision(2) << std::fixed << matRowMajor;

        std::cout << std::endl << std::endl << "Display transposed matrix in row and column convention" << std::endl;
        std::cout << std::endl << matRowMajor.getTransposed();
        std::cout << std::endl << matRowMajor.getTransposed<EMatrixConvention::ColumnMajor>();

        std::cout << std::endl << std::endl << "Convert Matrix" << std::endl;
        Matrix<6, 6, int, EMatrixConvention::ColumnMajor> matColumnMajor = matRowMajor;
        std::cout << matrixConventionToString(matColumnMajor.getMatrixConvention()) << std::endl << std::setprecision(2)  << std::fixed  << matColumnMajor;

        std::cout << std::endl << std::endl << "Try to transpose itself matrix" << std::endl;
        reinterpret_cast<SquareMatrix<6, int, EMatrixConvention::ColumnMajor>*>(&matColumnMajor)->transpose();
        std::cout << matrixConventionToString(matColumnMajor.getMatrixConvention()) << std::endl << std::setprecision(2)  << std::fixed  << matColumnMajor;
        //matRowMajor.transpose(); Do not work, because matrix is not square

        std::cout << std::endl << std::endl << "Try to transpose itself matrix" << std::endl;
        Matrix<6, 2, float, EMatrixConvention::ColumnMajor> matColumnMajorSqrt = matColumnMajor;
        Matrix<2, 3, float, EMatrixConvention::ColumnMajor> matColumnMajorSqrt2 = matColumnMajor;

        std::cout << matColumnMajorSqrt * matColumnMajorSqrt2;
        std::cout << matrixConventionToString(matColumnMajorSqrt.getMatrixConvention()) << std::endl << std::setprecision(2)  << std::fixed  << matColumnMajorSqrt;

        std::cout << std::endl << std::endl << "Try use *= operator" << std::endl;
        Matrix<3, 3, float, EMatrixConvention::RowMajor> matRowMajorSqrt = matColumnMajor;
        matRowMajorSqrt *= matRowMajorSqrt;
        matRowMajorSqrt[2][1] = 10.f;
        std::cout << matrixConventionToString(matRowMajorSqrt.getMatrixConvention()) << std::endl << std::setprecision(2)  << std::fixed  << matRowMajorSqrt;
        
        std::cout << std::endl << std::endl << "create consexpr reverse matrix" << std::endl;
        constexpr SquareMatrix<3, double, EMatrixConvention::ColumnMajor> matConstColumnMajorSqrt ( 2., 1., 3., 
                                                                                                    4., 2., -1.,
                                                                                                    2., -1., 1.);
        
        constexpr SquareMatrix<3, double, EMatrixConvention::RowMajor> matConstRowMajorSqrt (matConstColumnMajorSqrt);

        std::cout << std::endl << std::endl << matConstColumnMajorSqrt << std::endl;
        std::cout << std::endl << std::endl << matConstRowMajorSqrt << std::endl;

        constexpr SquareMatrix<3, double, EMatrixConvention::ColumnMajor> matConstColumnMajorInverse = matConstColumnMajorSqrt.getReverse();
        constexpr SquareMatrix<3, double, EMatrixConvention::ColumnMajor> matConstRowMajorInverse = matConstRowMajorSqrt.getReverse();
        std::cout << std::endl << std::endl << matConstColumnMajorInverse << std::endl;
        std::cout << std::endl << std::endl << matConstRowMajorInverse << std::endl;

        std::cout << SquareMatrix<3, double, EMatrixConvention::ColumnMajor>::createTranslationMatrix(Vec3f(1.f, 2.f, 3.f)) << std::endl;
        std::cout << SquareMatrix<3, double, EMatrixConvention::ColumnMajor>::createScaleMatrix(Vec3f(1.f, 2.f, 3.f)) << std::endl;
        std::cout << SquareMatrix<3, double, EMatrixConvention::ColumnMajor>::createRotationArroundAxisMatrix(Vec3f(0.f, 1.f, 0.f), 90_deg) << std::endl;

        std::cout << Matrix4<float, EMatrixConvention::ColumnMajor>::createLookAtView(Vec3f(0.f, 1.f, 0.f), Vec3f(8.f, 8.f, 5.f), Vec3f(0.f, 1.f, 0.f)) << std::endl;
        
    }

    /*Compatibility sandbox*/
    {
        std::cout << std::endl << std::endl << "Compatibility sandbox" << std::endl;
        Vec2f  vec2f (1.f, 2.f);
        Vec3f  vec3f(vec2f, 3.f);
        Vec4f  vec4f (vec3f, 4.f);
        
        Vector<2, float>  baseVec2f (1.f, 2.f);;
        Vector<3, float>  baseVec3f (baseVec2f, 3.f);
        Vector<4, float>  baseVec4f (baseVec3f, 4.f);
        
        /*constuctor*/
        {
            std::cout << std::endl << std::endl << "constuctor" << std::endl;
            GenericMatrix<2, 2, float>   baseMat3f (vec3f, vec3f);

            SquareMatrix <3, float>      sqrMat3f (vec3f, vec3f);

            GenericMatrix<4, 4, float>   baseMat3ff (vec2f, baseVec3f, vec4f);
            SquareMatrix <4, float>      sqrMat3ff (vec2f, baseVec3f, vec4f);

            GenericMatrix<2, 2, float>   baseMat3fff (sqrMat3f);
            SquareMatrix <3, float>      sqrMat3fff (baseMat3f);

            GenericMatrix<2, 2, float>   baseMat3fffff (baseMat3f);
            SquareMatrix <3, float>      sqrMat3fffff (sqrMat3f);

            GenericMatrix<4, 4, float>   baseMat3ffffff (vec2f, baseVec3f);
            SquareMatrix <4, float>      sqrMat3ffffff (vec2f, baseVec3f);
        }  

        /*operator =*/
        {
            std::cout << std::endl << std::endl << "operator =" << std::endl;

            GenericMatrix<2, 2, float>   baseMat3fff;
            SquareMatrix <3, float>      sqrMat3fff;

            GenericMatrix<2, 2, float>   baseMat3fffff;
            baseMat3fffff = baseMat3fff;

            SquareMatrix <3, float>      sqrMat3fffff;
            sqrMat3fffff = sqrMat3fff;
        }
     }
}