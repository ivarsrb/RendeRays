#include "ambient.h"

namespace light {
Ambient::Ambient(const t::Vec3& color) :
    ICaster(color, t::Vec3(0.0), t::Vec3(0.0)) {
}
}; // light
