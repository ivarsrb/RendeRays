#include "i_renderable.h"

namespace renderable {
IRenderable::IRenderable(const t::Vec3& color) :
    color_(glm::clamp((color), 0.0f, 1.0f)) {
}

const t::Vec3& IRenderable::GetColor() const {
    return color_;
}
}; // renderable
