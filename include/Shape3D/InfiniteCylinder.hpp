﻿//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 12 h 18

#ifndef _INFINITE_CYLINDER_H
#define _INFINITE_CYLINDER_H

#include "Shape3D/Volume.hpp"
#include "Vector/Vector.hpp"
#include "Shape3D/Line.hpp"

namespace FoxMath
{
    class InfiniteCylinder : public Volume
    {
        public:
    
        #pragma region constructor/destructor
    
        InfiniteCylinder ()                                   = default;
        InfiniteCylinder(const InfiniteCylinder& other)       = default;
        InfiniteCylinder( InfiniteCylinder&& other)           = default;
        virtual ~InfiniteCylinder()                           = default;
        InfiniteCylinder& operator=(InfiniteCylinder const&)  = default;
        InfiniteCylinder& operator=(InfiniteCylinder &&)      = default;

        explicit InfiniteCylinder (const Line& line, float radius)
        :   Volume          {},
            line_    {line},
            radius_  {radius}
        {}

        explicit InfiniteCylinder (const Vec3& pt, const Vec3& normal, float radius)
        :   Volume          {},
            line_    (pt, normal),
            radius_  {radius}
        {}
    
        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        bool isPointInside(const Vec3& pt) 
        {
            return Vec3::cross(line_.getNormal(), pt - line_.getOrigin()).length() <= radius_;
        }

        #pragma endregion //!methods
    
        #pragma region accessor

        const Line&     getLine     () const noexcept   { return line_;}
        Line&           getLine     () noexcept         { return line_;}
        const float&    getRadius   () const noexcept   { return radius_;}

        #pragma endregion //!accessor
    
        #pragma region mutator

        void setLine     (const Line& newLine)      noexcept { line_ = newLine;}
        void setRadius   (const float& newRadius)   noexcept { radius_ = newRadius;}

        #pragma endregion //!mutator
    
        protected:
    
        #pragma region attribut

        Line    line_;
        float   radius_;

        #pragma endregion //!attribut
    
        private:
    
    };

} /*namespace FoxMath*/

#endif //_INFINITE_CYLINDER_H