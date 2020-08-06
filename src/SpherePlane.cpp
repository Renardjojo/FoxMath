#include "GE/Core/Maths/ShapeRelation/SpherePlane.hpp"
#include "GE/Core/Maths/vec.hpp"

using namespace Engine::Core::Maths::ShapeRelation;
using namespace Engine::Core::Maths::Shape3D;
using namespace Engine::Core::Maths;


bool SpherePlane::isSphereOnOrForwardPlanCollided(const Shape3D::Sphere& sphere, const Shape3D::Plane& plane)
{
    float distanceSphereToOrigin = Vec3::dot(sphere.getCenter(), plane.getNormal());
    return distanceSphereToOrigin > -sphere.getRadius() + plane.getDistance();
}