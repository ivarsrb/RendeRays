#pragma once
#include "i_fog.h"
#include <util/types.h>

// Fog post-processing effect.
// Exponential based on distance.
// Fog factor is calculated as follows:
// f = 1 / e ^ (distance * density)
namespace postprocess {
class ExponentialFog : public IFog {
public:
    ExponentialFog(t::F32 density, const t::Vec3& color);
    virtual t::Vec3 Calculate(const t::Vec3& pixel_color, t::F32 depth) const override;
private:
    // Density is an arbitrary fog density that can range from 0.0 to 1.0.
    const t::F32 density_;
};
}; // postprocess