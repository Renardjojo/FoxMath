//Project : Engine
//Editing by Six Jonathan
//Date : 2020-06-08 - 09 h 04

#ifndef _VOLUME_H
#define _VOLUME_H

#include "GE/Core/Maths/vec.hpp"
#include "GE/Core/Maths/MathTools.hpp"

namespace Engine::Core::Maths::Shape3D
{
    class Volume
    {
        public:

        #pragma region constructor/destructor

        Volume ()					                = default;
        Volume (const Volume& other)			    = default;
        Volume (Volume&& other)				        = default;
        virtual ~Volume ()				            = default;
        Volume& operator=(Volume const& other)		= default;
        Volume& operator=(Volume && other)			= default;

        //float getArea () = 0;

        private:

    };

} /*namespace Engine::Core::Maths:Shape3D*/

#endif //_VOLUME_H