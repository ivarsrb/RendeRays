#include "aa_box.h"
#include <algorithm>
#include <util/util.h>

namespace renderable {
AABox::AABox(const t::Vec3& min_bound, const t::Vec3& max_bound, const t::Vec3& color) :
    IRenderable(color) ,
    min_bound_(min_bound),
    max_bound_(max_bound){
}

AABox::AABox(const t::Vec3& center, t::F32 half_size, const t::Vec3& color) :
    IRenderable(color),
    min_bound_(center - half_size),
    max_bound_(center + half_size) {
}

bool AABox::Intersect(const Ray& ray, Hit& hit) const {
    // Each component of the vector describes the distance from origin of the
    // ray to the plane perpendicular to it's axis. If value is infinite
    // it means ray is paralel to axis plane
    t::Vec3 t_min = (min_bound_ - ray.GetOrigin()) / ray.GetDirection();
    t::Vec3 t_max = (max_bound_ - ray.GetOrigin()) / ray.GetDirection();
    // In certain border cases t value can get NaN (0 / 0), make it small positie value instead
    util::VectorNANtoNum(t_min);
    util::VectorNANtoNum(t_max);
    // Closest and farest intersections
    t::F32 tmin = std::max(std::max(std::min(t_min.x, t_max.x), std::min(t_min.y, t_max.y)), std::min(t_min.z, t_max.z));
    t::F32 tmax = std::min(std::min(std::max(t_min.x, t_max.x), std::max(t_min.y, t_max.y)), std::max(t_min.z, t_max.z));
    // Rray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0.0) {
        return false;
    }
    // Ray doesn't intersect AABB
    if (tmin > tmax) {
        return false;
    }
    // Inside the box
    if (tmin < 0.0) {
        hit.SetDistance(tmax);
        return true;
    }
    // Ray starts outside the box and hits the box
    hit.SetDistance(tmin);
    return true;
}
}; // renderable