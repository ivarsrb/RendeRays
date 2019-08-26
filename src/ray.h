#pragma once
#include "util/types.h"

// Rays are fundamental building blocks of a ray-tracer.
// Ray class is a generic class that represents a ray and allows to retrieve extra information
class Ray {
public:
    Ray(const t::Vec3& origin, const t::Vec3& direction);
    t::Vec3 GetOrigin() const;
    t::Vec3 GetDirection() const;
    // Get point on the ray by a given distance from the origin
    t::Vec3 GetPoint(t::F32 distance) const;
private:
    // Ray is determined by it's origin and direction
    const t::Vec3 origin_;
    // Normally direction vector must be of a unit length
    const t::Vec3 direction_;
};