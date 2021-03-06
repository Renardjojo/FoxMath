﻿//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 16 h 05

#ifndef _SEGMENT_PLANE_H
#define _SEGMENT_PLANE_H

#include "ShapeRelation/Intersection.hpp"
#include "Shape3D/Segment.hpp"
#include "Shape3D/Plane.hpp"

namespace FoxMath
{
    class SegmentPlane
    {
        public:

        #pragma region constructor/destructor

        SegmentPlane ()					                    = delete;
        SegmentPlane (const SegmentPlane& other)			= delete;
        SegmentPlane (SegmentPlane&& other)				    = delete;
        virtual ~SegmentPlane ()				            = delete;
        SegmentPlane& operator=(SegmentPlane const& other)  = delete;
        SegmentPlane& operator=(SegmentPlane && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        static bool isSegmentPlaneCollided(const Segment& seg, const Plane& plane, Intersection& intersection);

        #pragma endregion //!static methods

        private :

        #pragma region static methods
        #pragma endregion //!static methods
    };

} /*namespace FoxMath*/

#endif //_SEGMENT_PLANE_H