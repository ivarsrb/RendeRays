#include "scene.h"
#include <stdexcept>
#include <util/log.h>
#include "light/ambient.h"
#include "light/directional.h"
#include "renderable/sphere.h"
#include "renderable/aa_box.h"

Scene::Scene(const std::string& file_name) {
    LoadFromJson(file_name);
}

const t::Size16& Scene::GetOutputSize() const {
    return output_size_;
}

const std::string& Scene::GetName() const {
    return name_;
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

void Scene::LoadFromJson(const std::string& file_name) {
    util::JSONLoader scene_loader(file_name);
    const auto& scene_data = scene_loader.Get();
    util::Log::Info("Loading scene data ...");
    LoadName(scene_data.at("name"));
    LoadRasterSize(scene_data.at("output_size"));
    LoadBackground(scene_data.at("background"));
    LoadCameras(scene_data.at("cameras"));
    LoadLight(scene_data.at("light"));
    LoadRenderables(scene_data.at("renderables"));
}

void Scene::LoadName(const util::JSONLoader::JsonType& json_data) {
    name_ = json_data.get<std::string>();
    size_t name_limit = 50;
    if (name_.size() > name_limit) {
        name_.resize(name_limit);
    }
    util::Log::Info("Scene name - '", name_, "'");
}

void Scene::LoadRasterSize(const util::JSONLoader::JsonType& json_data) {
    const std::vector<t::U16> size = json_data;
    output_size_ = { size.at(0), size.at(1) };
    const t::U16 raster_limit = 10000;
    if (output_size_.width == 0 || output_size_.height == 0 ||
        output_size_.width > raster_limit || output_size_.height > raster_limit) {
        throw std::runtime_error("Inapropriate raster output size!");
    }
    util::Log::Info("Output raster size - ", output_size_.width, ", ", output_size_.height);
}

void Scene::LoadBackground(const util::JSONLoader::JsonType& json_data) {
    const std::vector<t::F32> background = json_data;
    background_color_ = { background.at(0), background.at(1), background.at(2) };
    background_color_ = glm::clamp((background_color_), 0.0f, 1.0f);
    util::Log::Info("Background color - (", background_color_.r, ", ", background_color_.g, ",", background_color_.b, ")");
}

void Scene::LoadCameras(const util::JSONLoader::JsonType& json_data) {
    for (const auto& camera : json_data) {
        if (camera.at("type").get<std::string>() == "perspective") {
            const std::vector<t::F32> translation = camera.at("translation");
            const t::F32 rotation_y = camera.at("rotation_y");
            const t::F32 fov = camera.at("fov");
            AddCanera(Camera(t::Vec3(translation.at(0), translation.at(1), translation.at(2)),
                rotation_y, fov, output_size_));
            util::Log::Info("Perspective camera: position - (", translation[0], ",", translation[1], ",",
                translation[2], "), y rot. - ", rotation_y, ", fov - ", fov);
        }
    }
    if (cameras_.size() == 0) {
        throw std::runtime_error("No cameras described!");
    }
}

void Scene::LoadLight(const util::JSONLoader::JsonType& json_data) {
    if (json_data.at("type").get<std::string>() == "ambient") {
        const std::vector<t::F32> color = json_data.at("ambient");
        SetLight(std::make_unique<light::Ambient>(t::Vec3(color.at(0), color.at(1), color.at(2))));
        util::Log::Info("Ambient light - ", color[0], ", ", color[1], ", ", color[2]);
    }
    else if (json_data.at("type").get<std::string>() == "directional") {
        const std::vector<t::F32> direction = json_data.at("direction");
        const std::vector<t::F32> color_ambient = json_data.at("ambient");
        const std::vector<t::F32> color_diffuse = json_data.at("diffuse");
        SetLight(std::make_unique<light::Directional>(t::Vec3(direction.at(0), direction.at(1), direction.at(2)),
            t::Vec3(color_ambient.at(0), color_ambient.at(1), color_ambient.at(2)),
            t::Vec3(color_diffuse.at(0), color_diffuse.at(1), color_diffuse.at(2))));
        util::Log::Info("Diffuse light: direction - (", direction[0], ", ", direction[1], ", ", direction[2], "), ambbient - (",
            color_ambient[0], ", ", color_ambient[1], ", ", color_ambient[2], "), diffuse - (",
            color_diffuse[0], ", ", color_diffuse[1], ", ", color_diffuse[2], ")");
    }
    else {
        throw std::runtime_error("No light caster described!");
    }
}

void Scene::LoadRenderables(const util::JSONLoader::JsonType& json_data) {
    for (const auto& renderable : json_data) {
        if (renderable.at("type").get<std::string>() == "sphere") {
            const std::vector<t::F32> translation = renderable.at("translation");
            const t::F32 radius = renderable.at("radius");
            const std::vector<t::F32> color = renderable.at("color");
            AddRenderable(std::make_unique<renderable::Sphere>(t::Vec3(translation.at(0), translation.at(1), translation.at(2)),
                radius, t::Vec3(color.at(0), color.at(1), color.at(2))));
            util::Log::Info("Sphere: position - (", translation[0], ", ", translation[1], ", ", translation[2], "), radius - ",
                radius, ", color - (", color[0], ", ", color[1], ", ", color[2], ")");
        }
        else if (renderable.at("type").get<std::string>() == "aa_box") {
            const std::vector<t::F32> translation = renderable.at("translation");
            const t::F32 half_size = renderable.at("half_size");
            const std::vector<t::F32> color = renderable.at("color");
            AddRenderable(std::make_unique<renderable::AABox>(t::Vec3(translation.at(0), translation.at(1), translation.at(2)),
                half_size, t::Vec3(color.at(0), color.at(1), color.at(2))));
            util::Log::Info("Axis aligned box: position - (", translation[0], ", ", translation[1], ", ", translation[2], "), half size - ",
                half_size, ", color - (", color[0], ", ", color[1], ", ", color[2], ")");
        }
    }
}
