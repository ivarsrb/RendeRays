#include "hit.h"

Hit::Hit() : 
    distance_(t::kInfinity32),
    normal_(0.0, 0.0, 0.0) { 
}

void Hit::SetDistance(t::F32 distance) {
    distance_ = distance;
}

void Hit::SetSurfaceNormal(const t::Vec3& normal) {
    normal_ = glm::normalize(normal);
}

t::F32 Hit::GetDistance() const {
    return distance_;
}

const t::Vec3& Hit::GetSurfaceNormal() const {
    return normal_;
}
