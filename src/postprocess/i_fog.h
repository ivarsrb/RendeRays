#pragma once
#include <util/types.h>

// Interface for object post processing - fog.
// Fog is a color loss over a distance to fog color - 
//  i.e. all object colors become white with distance.
namespace postprocess {
class IFog {
public:
    IFog(const t::Vec3 color);
    virtual ~IFog() = default;
    virtual t::Vec3 Calculate(const t::Vec3& pixel_color, t::F32 depth) const = 0;
protected:
    // Take pixel color and fog factor and blend with fog color according to equation
    // to get final fogged pixel color.
    t::Vec3 Blend(const t::Vec3& pixel_color, t::F32 fog_factor) const;
    // Color of the fog
    const t::Vec3 color_;
};
}; //postprocess