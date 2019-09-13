#include "i_fog.h"
#include <util/util.h>

namespace postprocess {
IFog::IFog(const t::Vec3 color) :
    color_(util::ClampColor(color)) {
}

// Blend equation: C = f * Ci + (1 - f) * Cf
t::Vec3 IFog::Blend(const t::Vec3& pixel_color, t::F32 fog_factor) const {
    return pixel_color * fog_factor + (1.0f - fog_factor) * color_;
}
};