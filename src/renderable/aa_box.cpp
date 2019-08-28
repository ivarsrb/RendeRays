#include "aa_box.h"

namespace renderable {
AABox::AABox(const t::Vec3& min_bound, const t::Vec3& max_bound, const t::Vec3& color) :
    IRenderable(color) ,
    min_bound_(min_bound),
    max_bound_(max_bound){
}

bool AABox::Intersect(const Ray& ray, t::F32& distance) const {
    return false;
}
}; // renderable