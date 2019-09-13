#include "linear_fog.h"

namespace postprocess {
LinearFog::LinearFog(t::F32 start, t::F32 end, const t::Vec3& color) :
    IFog(color),
    start_(start),
    end_(end) {
}

// Linear equation: f = (end - distance) / (end - start)
t::Vec3 LinearFog::Calculate(const t::Vec3& pixel_color, t::F32 depth) const {
    const t::F32 fog_factor = (end_ - depth) / (end_ - start_);
    return IFog::Blend(pixel_color, fog_factor);
}
}; // postprocess