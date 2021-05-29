//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 17 h 20

#ifndef _SEGMENT_INFINITE_CYLINDER_H
#define _SEGMENT_INFINITE_CYLINDER_H

#include "ShapeRelation/Intersection.hpp"
#include "Shape3D/Segment.hpp"
#include "Shape3D/InfiniteCylinder.hpp"

namespace FoxMath
{
    class SegmentInfiniteCylinder
    {
        public:

        #pragma region constructor/destructor

        SegmentInfiniteCylinder ()					                                = delete;
        SegmentInfiniteCylinder (const SegmentInfiniteCylinder& other)			    = delete;
        SegmentInfiniteCylinder (SegmentInfiniteCylinder&& other)				    = delete;
        virtual ~SegmentInfiniteCylinder ()				                            = delete;
        SegmentInfiniteCylinder& operator=(SegmentInfiniteCylinder const& other)    = delete;
        SegmentInfiniteCylinder& operator=(SegmentInfiniteCylinder && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        static bool isSegmentInfiniteCylinderCollided(const Segment& seg, const InfiniteCylinder& infCylinder, Intersection& intersection);

        #pragma endregion //!static methods

        private :

        #pragma region static methods

        #pragma endregion //!static methods
    };

} /*namespace FoxMath*/

#endif //_SEGMENT_INFINITE_CYLINDER_H