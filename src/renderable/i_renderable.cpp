#include "i_renderable.h"

namespace renderable {
IRenderable::IRenderable(const t::Vec3& color) :
    color_(color) {
}

const t::Vec3& IRenderable::GetColor() const {
    return color_;
}
}; // renderable
