#include "i_caster.h"
namespace light {
ICaster::ICaster(const t::Vec3 ambient, const t::Vec3 diffuse, const t::Vec3 specular) :
    ambient_(glm::clamp((ambient), 0.0f, 1.0f)),
    diffuse_(glm::clamp((diffuse), 0.0f, 1.0f)),
    specular_(glm::clamp((specular), 0.0f, 1.0f)) {
}
const t::Vec3& ICaster::GetAmbient() const {
    return ambient_;
}

const t::Vec3& ICaster::GetDiffuse() const {
    return diffuse_;
}

const t::Vec3& ICaster::GetSpecular() const {
    return specular_;
}

t::Vec3 ICaster::GetDiffuseLit(const t::Vec3& normal) const {
    return diffuse_;
}
;
}; // light