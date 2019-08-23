#pragma once
#include "ray.h"
#include "types.h"
// Renderable object Sphere
class Sphere {
public:
    Sphere(const t::Vec3& center, t::F32 radius, const t::Vec3& color);
    // Does the passed ray intersect the renderable
    // if yes, return distance from the ray's origin to hit spiot
    bool Intersect(const Ray& ray, t::F32& distance) const;
    const t::Vec3& GeCenter() const;
    const t::Vec3& GetColor() const;
    t::F32 GetRadius() const;
private:
    // Different ways to compute intersection solution
    // Intersect() function calls most optimal of them.
    bool IntersectGeometric(const Ray& ray, t::F32& t0, t::F32& t1) const;
    bool IntersectAnalytic(const Ray& ray, t::F32& t0, t::F32& t1) const;
    bool SolveQuadratic(t::F32 a, t::F32 b, t::F32 c, t::F32& x0, t::F32& x1) const;
    const t::Vec3 center_;
    const t::F32 radius_;
    const t::Vec3 color_;
};