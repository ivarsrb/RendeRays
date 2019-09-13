#include "i_caster.h"
#include <util/util.h>

namespace light {
ICaster::ICaster(const t::Vec3 ambient, const t::Vec3 diffuse, const t::Vec3 specular) :
    ambient_(util::ClampColor(ambient)),
    diffuse_(util::ClampColor(diffuse)),
    specular_(util::ClampColor(specular)) {
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