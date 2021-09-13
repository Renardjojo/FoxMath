//Project : FoxMath
//Editing by Six Jonathan
//Date : 2020-04-30 - 10 h 35

#ifndef _REFERENTIAL_H
#define _REFERENTIAL_H

#include "Vector/Vector.hpp"

namespace FoxMath
{
    template <T>
    struct Referential
    {
		Referential ()								        = default;
		Referential (const Referential& other)			    = default;
		Referential (Referential&& other)					= default;
		~Referential ()							            = default;
		Referential& operator=(Referential const& other)    = default;
		Referential& operator=(Referential && other)		= default;

        Vec3<T> origin  {Vec3<T>::zero};
        Vec3<T>	unitI   {Vec3<T>::right};      //x
        Vec3<T>	unitJ   {Vec3<T>::up};         //y
        Vec3<T>	unitK   {Vec3<T>::forward};    //z

        // Vector compared to a referential
        static Vec3<T> globalToLocalVector(const Referential&  refLocal, const Vec3<T>& vector)
        {
            //U'x = U * i
            //U'y = U * j
            //U'z = U * k
            return Vec3<T>({Vec3<T>::dot(vector, refLocal.unitI), Vec3<T>::dot(vector, refLocal.unitJ), Vec3<T>::dot(vector, refLocal.unitK)});
        }

        // Vector compared to a referential
        static Vec3<T> localToGlobalVector(const Referential&  refLocal, const Vec3<T>& vector)
        {
            //vect(U) = u'x * i'(world) + u'y * j'(world) + u'z * k'(world)
            return (refLocal.unitI * vector.x) + (refLocal.unitJ * vector.y) + (refLocal.unitK * vector.z);
        }

        // Point compared to a referential
        static Vec3<T> globalToLocalPosition(const Referential& refLocal, const Vec3<T>& point)
        {
            //O'Mw 	= OMw  - OO'w
            const Vec3<T> OlocalM = point - refLocal.origin;

            //x = O'Mw * i'w 
            //y = O'Mw * j'w
            //z = O'Mw * k'w
            return globalToLocalVector(refLocal, OlocalM);
        }

        // Point compared to a referential
        static Vec3<T> localToGlobalPosition(const Referential&  refLocal, const Vec3<T>& point)
        {
            //O'Mw  = x' * i' + y' * j' + z' * k'
            const Vec3<T> vectorOlocalM = localToGlobalVector(refLocal, point);

            //OM = OO' + O'M
            return refLocal.origin + vectorOlocalM;
        }


    };

} /*namespace FoxMath */

#endif //_REFERENTIAL_H