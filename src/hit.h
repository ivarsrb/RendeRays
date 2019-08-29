#pragma once
#include "util/types.h"

// Stores information that is aquired during ray object intersection
class Hit {
public:
    Hit();
    // Set distance from ray origin to hitpoint
    void SetDistance(t::F32 distance);
    // Surface normal at the hit point
    // Normal is normalized inside
    void SetSurfaceNormal(const t::Vec3& normal);
    t::F32 GetDistance() const;
    const t::Vec3& GetSurfaceNormal() const;
private:
    // Distance from ray origin to point the ray hit the object.
    // Infinity by default
    t::F32 distance_;
    // Surface normal at the point the ray hit the object
    t::Vec3 normal_;
};