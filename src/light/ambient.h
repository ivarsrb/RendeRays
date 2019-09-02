#pragma once
#include "i_caster.h"
#include <util/types.h>

// Ambient light does not come from any direction.
// It lits the objects equally from all sides.
namespace light {
class Ambient : public ICaster {
public:
    // Ambeint color is passed
    // To get natural object color pass white (1.0,1.0,1.0)
    Ambient(const t::Vec3& color);
};
}; // light
