//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 15 h 57

#ifndef _INTERSECTION_3D_H
#define _INTERSECTION_3D_H

#include "Vector/Vector.hpp"

#include <limits>

namespace FoxMath
{
    enum class EIntersectionType
    {
        NoIntersection,
        OneIntersectiont,
        TwoIntersectiont,
        InfinyIntersection,
        UnknowIntersection
    };

    struct Intersection
    {
        EIntersectionType intersectionType = EIntersectionNoIntersection;
        Vec3 intersection1;
        Vec3 intersection2;
        Vec3 normalI1;
        Vec3 normalI2;

        void setNotIntersection ()
        {
            intersectionType = EIntersectionNoIntersection;
        }

        void setOneIntersection(const Vec3& intersectionPoint)
        {
            intersectionType = EIntersectionOneIntersectiont;
            intersection1 = intersectionPoint;
        }

        void setTwoIntersection(const Vec3& intersectionPoint1, const Vec3 intersectionPoint2)
        {
            intersectionType = EIntersectionTwoIntersectiont;
            intersection1 = intersectionPoint1;
            intersection2 = intersectionPoint2;
        }

        void setSecondIntersection(const Vec3& intersectionPoint2)
        {
            intersectionType = EIntersectionTwoIntersectiont;
            intersection2 = intersectionPoint2;
        }

        void setInifitIntersection()
        {
            intersectionType = EIntersectionInfinyIntersection;
        }

        void setUnKnowIntersection()
        {
            intersectionType = EIntersectionUnknowIntersection;
        }

        void removeFirstIntersection()
        {
            if (intersectionType == EIntersectionTwoIntersectiont)
            {
                intersectionType = EIntersectionOneIntersectiont;
                intersection1 = intersection2;
                normalI1 = normalI2;
            }
            else
            {
                intersectionType = EIntersectionNoIntersection;
            }
        }

        void removeSecondIntersection()
        {
            if (intersectionType == EIntersectionTwoIntersectiont)
            {
                intersectionType = EIntersectionOneIntersectiont;

            }
        }

        /*return true if intersection contenor is full (if there are 2 intersection)*/
        bool addIntersectionAndCheckIfSecond(const Vec3& intersection)
        {
            if (intersectionType != EIntersectionOneIntersectiont)
            {
                setOneIntersection(intersection);
                return false;
            }
            else
            {
                setSecondIntersection(intersection);
                return true;
            }
        }

        void swapIntersection()
        {
            /*swap intersection*/
            std::swap<Vec3>(intersection1, intersection2);

            /*swap normal*/
            std::swap<Vec3>(normalI1, normalI2);
        }

        void sortIntersection(const Vec3& pt1Seg)
        {
            if (intersectionType != EIntersectionTwoIntersectiont)
            {
                return;
            }

            if ((intersection1 - pt1Seg).length() > (intersection2 - pt1Seg).length())
            {
                swapIntersection();
            }
        }

        static bool computeDiscriminentAndSolveEquation(float a, float b, float c, const Vec3& segPt1, const Vec3& segPt2, Intersection& intersection);
    };
} /*namespace FoxMath*/

#endif //_INTERSECTION_3D_H