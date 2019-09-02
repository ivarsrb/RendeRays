#pragma once


#include "i_caster.h"
#include <util/types.h>

// Directional light comes from one direction.
// Sunlight on the Earth can be seen as directional light
namespace light {
class Directional : public ICaster {
public:
    // direction is a direction of light rays. This vector is
    // normalized and reversed inside.
    // Ambient color is like global illumination of a scene. It is used to light
    // up dark corners of obbjects slightly. Usually is dark grey.
    // Diffuse color is the color of light itself. Usually is white.
    Directional(const t::Vec3& direction, const t::Vec3& ambient_color, const t::Vec3& diffuse_color);
    // Return diffuce color depending on the angle light hits the point with the normal.
    virtual t::Vec3 GetDiffuseLit(const t::Vec3& normal) const override;
private:
    // Reverse direction of light rays
    const t::Vec3 direction_;
};
}; // light