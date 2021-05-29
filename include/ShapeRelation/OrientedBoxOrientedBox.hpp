//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-12 - 15 h 15

#ifndef _ORIENTED_BOX_ORIENTED_BOX_H
#define _ORIENTED_BOX_ORIENTED_BOX_H

#include "ShapeRelation/Intersection.hpp"
#include "GE/Core/Maths/Shape3D/OrientedBox.hpp"

namespace FoxMath
{
    class OrientedBoxOrientedBox
    {
        public:

        #pragma region constructor/destructor

        OrientedBoxOrientedBox ()					                            = delete;
        OrientedBoxOrientedBox (const OrientedBoxOrientedBox& other)			= delete;
        OrientedBoxOrientedBox (OrientedBoxOrientedBox&& other)				    = delete;
        virtual ~OrientedBoxOrientedBox ()				                        = delete;
        OrientedBoxOrientedBox& operator=(OrientedBoxOrientedBox const& other)  = delete;
        OrientedBoxOrientedBox& operator=(OrientedBoxOrientedBox && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        static bool isBothOrientedBoxCollided(const OrientedBox& box1, const OrientedBox& box2);

        #pragma endregion //!static methods

        private :

        #pragma region static methods

        #pragma endregion //!static methods
    };

} /*namespace FoxMath*/

#endif //_ORIENTED_BOX_ORIENTED_BOX_H