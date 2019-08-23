#include "scene.h"
#include <stdexcept>

// Scene invariant establishes that scene has to have at least one camera
Scene::Scene() {
}

void Scene::AddCanera(const Camera& camera) {
    cameras_.push_back(camera);
}

const std::vector<Camera>& Scene::GetCameras() const {
    return cameras_;
}

/*
const Camera& Scene::GetCamera(size_t index) const {
    return cameras_.at(index);
}

const Camera& Scene::GetFirstCameras() const {
    return cameras_.at(0);
}*/

void Scene::AddRenderable(const Sphere& renderable) {
    renderables_.push_back(renderable);
}

const std::vector<Sphere>& Scene::GetRenderables() const {
    return renderables_;
}
