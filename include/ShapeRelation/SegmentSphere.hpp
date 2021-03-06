﻿//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 16 h 13

#ifndef _SEGMENT_SPHERE_H
#define _SEGMENT_SPHERE_H

#include "ShapeRelation/Intersection.hpp"
#include "Shape3D/Segment.hpp"
#include "Shape3D/Sphere.hpp"

namespace FoxMath
{
    class SegmentSphere
    {
        public:

        #pragma region constructor/destructor

        SegmentSphere ()					                    = delete;
        SegmentSphere (const SegmentSphere& other)			    = delete;
        SegmentSphere (SegmentSphere&& other)				    = delete;
        virtual ~SegmentSphere ()				                = delete;
        SegmentSphere& operator=(SegmentSphere const& other)    = delete;
        SegmentSphere& operator=(SegmentSphere && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        static bool isSegmentSphereCollided(const Segment& seg, const Sphere& sphere, Intersection& intersection);

        #pragma endregion //!static methods

        private :

        #pragma region static methods
        #pragma endregion //!static methods
    };

} /*namespace FoxMath*/

#endif //_SEGMENT_SPHERE_H