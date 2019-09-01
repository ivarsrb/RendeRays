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

void Scene::SetDirectionalLight(const DirectionalLight& light) {
    //light.GetDirection();
    directional_light.emplace(light);
}

const std::optional<DirectionalLight>& Scene::GetDirectionalLight() const {
    return directional_light;
}
