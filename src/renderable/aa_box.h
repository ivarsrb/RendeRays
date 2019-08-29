#pragma once
#include "util//types.h"
#include "i_renderable.h"

// Axis-aliligned box
// Axis alligned means that vectors conncting adjecent box vertices
// are either paralel or orthogonal to axis of wolrd coordinate system.      
namespace renderable {
class AABox : public IRenderable {
public:
    // Axis-alligned bounding box is described by two points - 
    // minimal and maximal cube points or bounds.
    AABox(const t::Vec3& min_bound, const t::Vec3& max_bound, const t::Vec3& color);
    // Does the passed ray intersect the renderable
    // if yes, return distance from the ray's origin to hit spiot
    // If no hit occurs, distance is not modified.
    virtual bool Intersect(const Ray& ray, t::F32& distance) const override;
private:
    // Box is described by two bounds - minimal and maximal
    // Minimal bound have numericaly smallest values
    // Maximal bounds have numerically largest values.
    const t::Vec3 min_bound_;
    const t::Vec3 max_bound_;
};
}; // renderable


