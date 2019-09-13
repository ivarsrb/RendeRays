#include "directional.h"
#include <algorithm>

namespace light {
Directional::Directional(const t::Vec3& direction, const t::Vec3& ambient_color, const t::Vec3& diffuse_color) :
    ICaster(ambient_color, diffuse_color, t::Vec3(0.0)),
    // Reverse the vector
    direction_(glm::normalize(direction) * t::F32(-1.0)) {
}

// Base diffuse color altered by light falling angle.
t::Vec3 Directional::GetDiffuseLit(const t::Vec3& normal) const {
    t::F32 light_intensity = std::max(glm::dot(normal, direction_), 0.0f);
    return GetDiffuse() * light_intensity;
}
}; // light