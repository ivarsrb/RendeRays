#pragma once
#include "util//types.h"
#include "i_renderable.h"

// Axis-aliligned box
// Axis alligned means that vectors conncting adjecent box vertices
// are either paralel or orthogonal to axis of world coordinate system.      
namespace renderable {
class AABox : public IRenderable {
public:
    // Constructor that describes a box by it's senter and half-size 
    AABox(const t::Vec3& center, t::F32 half_size, const t::Vec3& color);
    // Does the passed ray intersect the renderable
    // if yes, return distance from the ray's origin to hit spiot
    // If no hit occurs, distance is not modified.
    virtual bool Intersect(const Ray& ray, Hit& hit) const override;
private:
    // Get surface normal at given surface point
// It's not necessary to normalize the result
    t::Vec3 GetNormal(const t::Vec3& point_on_surface) const;
    // Center of the cube
    const t::Vec3 center_;
    // Size from center to outer edge (analogue to sphere radius)
    const t::F32 half_size_;
    // Additionally box is described by two bounds - minimal and maximal
    // Minimal bound have numericaly smallest values
    // Maximal bounds have numerically largest values.
    const t::Vec3 min_bound_;
    const t::Vec3 max_bound_;
};
}; // renderable


