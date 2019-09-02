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

void Scene::AddRenderable(std::unique_ptr<renderable::IRenderable> renderable) {
    renderables_.push_back(std::move(renderable));
}

const std::vector<std::unique_ptr<renderable::IRenderable>>& Scene::GetRenderables() const {
    return renderables_;
}

void Scene::SetLight(std::unique_ptr<light::ICaster> light) {
    light_ = std::move(light);
}

const std::unique_ptr<light::ICaster>& Scene::GetLight() const {
    return light_;
}
