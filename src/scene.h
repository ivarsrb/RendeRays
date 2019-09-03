#pragma once
#include <string>
#include <vector>
#include <memory>
#include "camera.h"
#include "renderable/i_renderable.h"
#include "light/i_caster.h"

// Stores renderable data, lights and camera
class Scene {
public:
    Scene(const std::string& file_name);
    const t::Size16& GetOutputSize() const;
    const std::string& GetName() const;
    const t::Vec3& GetBackgroundColor() const;
    void AddCanera(const Camera& camera);
    const std::vector<Camera>& GetCameras() const;
    void AddRenderable(std::unique_ptr<renderable::IRenderable> renderable);
    const std::vector<std::unique_ptr<renderable::IRenderable>>& GetRenderables() const;
    void SetLight(std::unique_ptr<light::ICaster> light);
    const std::unique_ptr<light::ICaster>& GetLight() const;
private:
    // Load the scene contents from given json file
    void LoadFromJson(const std::string& file_name);
    // Output size in raster pixels
    t::Size16 output_size_;
    // Name of the scene
    std::string name_;
    // Image background color
    t::Vec3 background_color_;
    // There can be multiple predefined scene vantaga points
    std::vector<Camera> cameras_;
    // Interface pointer vector to base class if renderable objects
    std::vector<std::unique_ptr<renderable::IRenderable>> renderables_;
    // Lighting type
    std::unique_ptr<light::ICaster> light_;
};