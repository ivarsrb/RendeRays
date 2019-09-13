#pragma once
#include "i_fog.h"
#include <util/types.h>

// Fog post-processing effect.
// Linear based on distance.
// Fog factor is calculated as follows:
// f = (end - distance) / (end - start)
namespace postprocess {
class LinearFog  : public IFog {
public:
    LinearFog(t::F32 start, t::F32 end, const t::Vec3& color);
    virtual t::Vec3 Calculate(const t::Vec3& pixel_color, t::F32 depth) const override;
private:
    // Distance from camera at which the effect start to take place
    const t::F32 start_;
    // Maximum distance for the efect
    const t::F32 end_;

};
}; // postprocess