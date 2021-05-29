#include "GE/Core/Maths/ShapeRelation/SpherePlane.hpp"
#include "Vector/Vector.hpp"

using namespace FoxMath;
using namespace FoxMath;
using namespace FoxMath;


bool SpherePlane::isSphereOnOrForwardPlanCollided(const Sphere& sphere, const Plane& plane)
{
    float distanceSphereToOrigin = Vec3::dot(sphere.getCenter(), plane.getNormal());
    return distanceSphereToOrigin > -sphere.getRadius() + plane.getDistance();
}