﻿//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 14 h 13

#ifndef _CYLINDER_H
#define _CYLINDER_H

#include "Shape3D/Volume.hpp"
#include "Vector/Vector.hpp"
#include "Shape3D/Segment.hpp"
#include "Shape3D/Plane.hpp"
#include "Shape3D/InfiniteCylinder.hpp"

namespace FoxMath
{
    class Cylinder : public Volume
    {
        public:
    
        #pragma region constructor/destructor
    
        Cylinder ()                           = default;
        Cylinder(const Cylinder& other)       = default;
        Cylinder( Cylinder&& other)           = default;
        virtual ~Cylinder()                   = default;
        Cylinder& operator=(Cylinder const&)  = default;
        Cylinder& operator=(Cylinder &&)      = default;

        explicit Cylinder (const Vec3& center, const Vec3& normal, float height, float radius)
        :       Volume          {},
                segment_  {Vec3(center - normal * (height / 2.f)), Vec3(center + normal * (height / 2.f))},
                radius_   {radius}
        {}

        explicit Cylinder (const Segment& segment, float radius)
        :   Volume          {},
            segment_    {segment},
            radius_     {radius}
        {}

        explicit Cylinder (const Vec3& pt1, const Vec3& pt2, float radius)
        :   Volume          {},
            segment_    (pt1, pt2),
            radius_  {radius}
        {}
    
        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        InfiniteCylinder getInfiniteCylinder() const noexcept
        {
            return InfiniteCylinder(static_cast<Line>(segment_), radius_);
        }

        Plane LeftPlane () const noexcept
        {
            return Plane(segment_.getPt1(), (segment_.getPt1() - segment_.getPt2()).getNormalize());
        }

        Plane RightPlane () const noexcept
        {
            return Plane(segment_.getPt2(), (segment_.getPt2() - segment_.getPt1()).getNormalize());
        }

        Vec3 getCenter() const noexcept
        {
            return segment_.getCenter();
        }

        #pragma endregion //!methods
    
        #pragma region accessor

        const Segment&  getSegment  () const noexcept   { return segment_;}
        Segment&        getSegment  () noexcept         { return segment_;}
        const float&    getRadius   () const noexcept   { return radius_;}

        #pragma endregion //!accessor
    
        #pragma region mutator

        void setSegment     (const Segment& newSegment)noexcept { segment_ = newSegment;}
        void setRadius      (const float& newRadius)   noexcept { radius_ = newRadius;}

        #pragma endregion //!mutator
    
        protected:
    
        #pragma region attribut

        Segment    segment_;
        float   radius_;

        #pragma endregion //!attribut
    
        private:
    
    };

} /*namespace FoxMath*/

#endif //_CYLINDER_H