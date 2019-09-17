#include "exponential_fog.h"
#include <algorithm>

namespace postprocess {
ExponentialFog::ExponentialFog(t::F32 density, const t::Vec3& color) :
    IFog(color), 
    density_(std::clamp(density, 0.0f, 1.0f)) {
}

// Exponential equation: f = 1 / e ^ (distance * density)
t::Vec3 ExponentialFog::Calculate(const t::Vec3& pixel_color, t::F32 depth) const {
    const t::F32 fog_factor = 1.0f / exp(depth * density_);
    return IFog::Blend(pixel_color, fog_factor);
}
};