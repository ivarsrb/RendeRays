#pragma once
#include "util/types.h"

// Light source that is defined by direction (equivilient of sunlight)
// Corresponds to diffuse light in Phong shading model
class DirectionalLight {
public:
    // Direction vector is normalized inside
    DirectionalLight(const t::Vec3& direction);
    const t::Vec3& GetDirection() const;
private:
    // Direction of a light vector (normalized)
    const t::Vec3 direction_;
};

