#include "ray.h"

Ray::Ray(const t::Vec3& origin, const t::Vec3& direction) :
    origin_(origin),
    direction_(glm::normalize(direction)) {
}

t::Vec3 Ray::GetOrigin() const {
    return origin_;
}

t::Vec3 Ray::GetDirection() const {
    return direction_;
}

// Point is calculated by - p(t) = O + t*D
t::Vec3 Ray::GetPoint(t::F32 distance) const {
    // Direction is normalized, otherwise unexpected results may happen
    return origin_ + distance * direction_;
}
