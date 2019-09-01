#pragma once
#include "util/types.h"

// Light source that is defined by direction (equivilient of sunlight)
// Corresponds to diffuse light in Phong shading model
class DirectionalLight {
public:
    // Direction vector is normalized inside
    DirectionalLight(const t::Vec3& direction);
    // The direction is backward
    const t::Vec3& GetDirection() const;
private:
    // Direction of a light vector (normalized) and reversed because
    // for caluclations direction is from the object to light source
    const t::Vec3 direction_;
};

