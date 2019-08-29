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

bool AABox::Intersect(const Ray& ray, t::F32& distance) const {
   /*
    t::Vec3 dirfrac = 1.0f / ray.GetDirection();

    float t1 = (min_bound_.x - ray.GetOrigin().x) / ray.GetDirection().x;
    float t2 = (max_bound_.x - ray.GetOrigin().x) / ray.GetDirection().x;
    float t3 = (min_bound_.y - ray.GetOrigin().y) / ray.GetDirection().y;
    float t4 = (max_bound_.y - ray.GetOrigin().y) / ray.GetDirection().y;
    float t5 = (min_bound_.z - ray.GetOrigin().z) / ray.GetDirection().z;
    float t6 = (max_bound_.z - ray.GetOrigin().z) / ray.GetDirection().z;

    float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));
    */

    // Distance from origin where ray crosses a line along X-axis
    // Minimal
    t::F32 t_min_x = (min_bound_.x - ray.GetOrigin().x) / ray.GetDirection().x;
    // In certain border cases t value can get NaN (0 / 0), make it small positie value instead
    t_min_x = util::NANtoNum(t_min_x);
    // Maximal
    t::F32 t_max_x = (max_bound_.x - ray.GetOrigin().x) / ray.GetDirection().x;
    t_max_x = util::NANtoNum(t_max_x);
    // .. along Y - axis
    // Minimal
    t::F32 t_min_y = (min_bound_.y - ray.GetOrigin().y) / ray.GetDirection().y;
    t_min_y = util::NANtoNum(t_min_y);
    // Maximal
    t::F32 t_max_y = (max_bound_.y - ray.GetOrigin().y) / ray.GetDirection().y;
    t_max_y = util::NANtoNum(t_max_y);
    // ... along Z - axis
    // Minimal
    t::F32 t_min_z = (min_bound_.z - ray.GetOrigin().z) / ray.GetDirection().z;
    t_min_z = util::NANtoNum(t_min_z);
    // Maximal
    t::F32 t_max_z = (max_bound_.z - ray.GetOrigin().z) / ray.GetDirection().z;
    t_max_z = util::NANtoNum(t_max_z);
    
    // Closest and farest intersections
    t::F32 tmin = std::max(std::max(std::min(t_min_x, t_max_x), std::min(t_min_y, t_max_y)), std::min(t_min_z, t_max_z));
    t::F32 tmax = std::min(std::min(std::max(t_min_x, t_max_x), std::max(t_min_y, t_max_y)), std::max(t_min_z, t_max_z));

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
        distance = tmax;
        return true;
    }
    // Ray starts outside the box and hits the box
    distance = tmin;
    return true;
    /*
    // Wether ray crosses a line along X-axis
    // Minimal
    t::F32 t_min_x = (min_bound_.x - ray.GetOrigin().x) / ray.GetDirection().x;
    // Maximal
    t::F32 t_max_x = (max_bound_.x - ray.GetOrigin().x) / ray.GetDirection().x;
    // Y - axis
    // Minimal
    t::F32 t_min_y = (min_bound_.y - ray.GetOrigin().y) / ray.GetDirection().y;
    // Maximal
    t::F32 t_max_y = (max_bound_.y - ray.GetOrigin().y) / ray.GetDirection().y;
    // Z - axis
    // Minimal
    t::F32 t_min_z = (min_bound_.z - ray.GetOrigin().z) / ray.GetDirection().z;
    // Maximal
    t::F32 t_max_z = (max_bound_.z - ray.GetOrigin().z) / ray.GetDirection().z;

    // If both (min and max) t values of the same axis are negative, it means
    // the box is not hit at all - is behind the ray or paralel to the side
    if ((t_min_x < 0.0 && t_max_x < 0.0) || 
        (t_min_y < 0.0 && t_max_y < 0.0) ||
        (t_min_z < 0.0 && t_max_z < 0.0)) {
        return false;
    }



    return false;

    */
}
}; // renderable