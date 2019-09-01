#include "aa_box.h"
#include <algorithm>
#include <util/util.h>

#include <glm/gtx/component_wise.hpp>


namespace renderable {
AABox::AABox(const t::Vec3& center, t::F32 half_size, const t::Vec3& color) :
    IRenderable(color),
    center_(center),
    half_size_(half_size),
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
    const t::F32 tmin = std::max(std::max(std::min(t_min.x, t_max.x), std::min(t_min.y, t_max.y)), 
        std::min(t_min.z, t_max.z));
    const t::F32 tmax = std::min(std::min(std::max(t_min.x, t_max.x), std::max(t_min.y, t_max.y)), 
        std::max(t_min.z, t_max.z));
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
        //hit.SetSurfaceNormal(ray.GetPoint(tmax) - center_);
        return true;
    }
    // Ray starts outside the box and hits the box
    hit.SetDistance(tmin);

    //////////////////////////////////////////
    /*
    t::Vec3 normal = glm::floor(ray.GetPoint(tmin) -  center_);
    hit.SetSurfaceNormal(normal);*/
    
    // * Get normal vector
    t::Vec3 direction = ray.GetPoint(tmin) - center_;
    // * Get the biggest absolute value from normal vector
    t::Vec3 direction_abs = glm::abs(direction);
    auto max_val = glm::compMax(direction_abs);
    // * Make this value 1, make all other values 0
    t::Vec3 normal_vector;
    if (max_val > direction_abs.x) {
        normal_vector.x = 0.0;
    }
    else {
        normal_vector.x = 1.0;
    }
    if (max_val > direction_abs.y) {
        normal_vector.y = 0.0;
    }
    else {
        normal_vector.y = 1.0;
    }

    if (max_val > direction_abs.z) {
        normal_vector.z = 0.0;
    }
    else {
        normal_vector.z = 1.0;
    }
    // * Keep the sign of the biggest modular value
    normal_vector *= glm::sign(direction);
    hit.SetSurfaceNormal(normal_vector);
    
    return true;
}
}; // renderable