#include "i_caster.h"
namespace light {
ICaster::ICaster(const t::Vec3 ambient, const t::Vec3 diffuse, const t::Vec3 specular) :
    ambient_(ambient),
    diffuse_(diffuse),
    specular_(specular) {
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
;
}; // light