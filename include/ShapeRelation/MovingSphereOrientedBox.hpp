//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 16 h 05

#ifndef _MOVING_SPHERE_ORIENTED_BOX_H
#define _MOVING_SPHERE_ORIENTED_BOX_H

#include "Vector/Vector.hpp"
#include "ShapeRelation/Intersection.hpp"
#include "Shape3D/Segment.hpp"
#include "GE/Core/Maths/Shape3D/Capsule.hpp"
#include "GE/Core/Maths/Shape3D/Quad.hpp"
#include "GE/Core/Maths/Shape3D/OrientedBox.hpp"

namespace FoxMath
{
    class MovingSphereOrientedBox
    {
        public:

        #pragma region constructor/destructor

        MovingSphereOrientedBox ()					                                = delete;
        MovingSphereOrientedBox (const MovingSphereOrientedBox& other)			    = delete;
        MovingSphereOrientedBox (MovingSphereOrientedBox&& other)				    = delete;
        virtual ~MovingSphereOrientedBox ()				                            = delete;
        MovingSphereOrientedBox& operator=(MovingSphereOrientedBox const& other)    = delete;
        MovingSphereOrientedBox& operator=(MovingSphereOrientedBox && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        /*get the first collision point between moving sphere and static box*/
        static bool isMovingSphereOrientedBoxCollided(const Sphere& sphere, const OrientedBox& box, const Vec3& sphereVelocity, Intersection& intersection);

        #pragma endregion //!static methods

        private :

        #pragma region static methods

        static OrientedBox getMinkowskiSumOBB (const OrientedBox& box, float sphereRadius);

        static void applyVeronoiRegionCorrection(const OrientedBox& box, Intersection& intersection, const Segment& seg, float sphereRadius);

        static bool applyVeronoiRegionCorrectionWithOutCode(const OrientedBox& box, Intersection& intersection, const Segment& seg, float sphereRadius, int topOutCode, int rightOutCode, int forwardOutCode, bool checkFirstIntersection);

        static bool applyCapsuleCorrection(const Segment& seg, const Capsule& _capsule, Intersection& intersection, bool checkFirstIntersection);

        /*Sub component of minkowski sum*/
        static Capsule getTopLeftVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getTopRightVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getTopForwardVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getTopBackwardVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getBottomLeftVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getBottomRightVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getBottomForwardVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getBottomBackwardVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getLeftForwardVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getLeftBackwardVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getRightForwardVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Capsule getRightBackwardVeronoiCapsule(const OrientedBox& box, float sphereRadius);

        static Quad getTopVeronoiFace (const OrientedBox& box, float sphereRadius);

        static Quad getBottomVeronoiFace(const OrientedBox& box, float sphereRadius);

        static Quad getRightVeronoiFace(const OrientedBox& box, float sphereRadius);

        static Quad getLeftVeronoiFace(const OrientedBox& box, float sphereRadius);

        static Quad getFowardVeronoiFace(const OrientedBox& box, float sphereRadius);

        static Quad getBackwardVeronoiFace(const OrientedBox& box, float sphereRadius);

        #pragma endregion //!static methods

        #pragma region static attribut

        //OutCode for detect the position of a point with the capsule
        static const int BOTTOM_LEFT_BACKWARD  = 0;    // 0000
        static const int TOP_LEFT_BACKWARD     = 1;    // 0001
        static const int BOTTOM_RIGHT_BACKWARD = 2;    // 0010
        static const int TOP_RIGHT_BACKWARD    = 3;    // 0011
        static const int BOTTOM_LEFT_FORWARD   = 4;    // 0100
        static const int TOP_LEFT_FORWARD      = 5;    // 0101
        static const int BOTTOM_RIGHT_FORWARD  = 6;    // 0110
        static const int TOP_RIGHT_FORWARD     = 7;    // 0111
        static const int INSIDE                = 8;    // 1000
    
        static const int ON_TOP_MASK           = 0;    // 0001
        static const int ON_RIGHT_MASK         = 1;    // 0010
        static const int ON_FORWARD_MASK       = 2;    // 0100

        #pragma endregion //!static attribut
    };

} /*namespace FoxMath*/

#endif //_MOVING_SPHERE_ORIENTED_BOX_H