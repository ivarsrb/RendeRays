#include "scene.h"

Scene::Scene(const t::Vec3& background_color) : 
    background_color_(background_color) {
}

const t::Vec3& Scene::GetBackgroundColor() const {
    return background_color_;
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
