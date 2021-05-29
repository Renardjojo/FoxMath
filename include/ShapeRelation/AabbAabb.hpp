//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-12 - 15 h 13

#ifndef _AABB_AABB_H
#define _AABB_AABB_H

#include "ShapeRelation/Intersection.hpp"
#include "Shape3D/AABB.hpp"

namespace FoxMath
{
    class AabbAabb
    {
        public:

        #pragma region constructor/destructor

        AabbAabb ()					                = delete;
        AabbAabb (const AabbAabb& other)			= delete;
        AabbAabb (AabbAabb&& other)				    = delete;
        virtual ~AabbAabb ()				        = delete;
        AabbAabb& operator=(AabbAabb const& other)  = delete;
        AabbAabb& operator=(AabbAabb && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        static bool isBothAABBCollided(const AABB& aabb1, const AABB& aabb2, Intersection& intersection);
        static bool isBothAABBCollided(const AABB& aabb1, const AABB& aabb2);

        #pragma endregion //!static methods

        private :

        #pragma region static methods

        #pragma endregion //!static methods
    };

} /*namespace FoxMath*/

#endif //_AABB_AABB_H