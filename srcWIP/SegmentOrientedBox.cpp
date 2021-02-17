#include "GE/Core/Maths/ShapeRelation/SegmentOrientedBox.hpp"

#include "Vector/Vector.hpp"
#include "Shape3D/AABB.hpp"
#include "GE/Core/Maths/ShapeRelation/SegmentAABB.hpp"
#include "Referential/Referential.hpp"

using namespace FoxMath;
using namespace FoxMath;
using namespace FoxMath;

bool SegmentOrientedBox::isSegmentOrientedBoxCollided(const Segment& seg, const OrientedBox& orientedBox, Intersection& intersection)
{
    /*Transform the segment from global referential to the local referential of the oriented box*/
    Segment localSegment {  Referential::globalToLocalPosition(orientedBox.getReferential(), seg.getPt1()),
                            Referential::globalToLocalPosition(orientedBox.getReferential(), seg.getPt2())};
                            

    AABB orientedBoxAxisAligned {Referential::globalToLocalPosition(orientedBox.getReferential(), orientedBox.getReferential().origin), orientedBox.getExtI(), orientedBox.getExtJ(), orientedBox.getExtK()};

    if(SegmentAABB::isSegmentAABBCollided(localSegment, orientedBoxAxisAligned, intersection))
    {
        intersection.intersection1 = Referential::localToGlobalPosition(orientedBox.getReferential(), intersection.intersection1);
        
        if (intersection.intersectionType == EIntersectionTwoIntersectiont)
            intersection.intersection2 = Referential::localToGlobalPosition(orientedBox.getReferential(), intersection.intersection2);

        intersection.normalI1 = Referential::localToGlobalVector(orientedBox.getReferential(), intersection.normalI1);

        if (intersection.intersectionType == EIntersectionTwoIntersectiont)
        {
            intersection.normalI2 = Referential::localToGlobalVector(orientedBox.getReferential(), intersection.normalI2);
        }

        return true;
    }

    return intersection.intersectionType != EIntersectionNoIntersection;
}