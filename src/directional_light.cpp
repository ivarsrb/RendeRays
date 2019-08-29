#include "directional_light.h"

DirectionalLight::DirectionalLight(const t::Vec3& direction) : 
    direction_(glm::normalize(direction)) {
}

const t::Vec3& DirectionalLight::GetDirection() const {
    return direction_;
}
