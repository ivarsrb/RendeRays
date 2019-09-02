#pragma once
#include <vector>
#include <memory>
#include <optional>
#include "camera.h"
#include "renderable/i_renderable.h"
#include "light/i_caster.h"
#include "directional_light.h"

// Stores renderable data, lights and camera
class Scene {
public:
    Scene();
    void AddCanera(const Camera& camera);
    const std::vector<Camera>& GetCameras() const;
    void AddRenderable(std::unique_ptr<renderable::IRenderable> renderable);
    const std::vector<std::unique_ptr<renderable::IRenderable>>& GetRenderables() const;
    void SetLight(std::unique_ptr<light::ICaster> light);
    const std::unique_ptr<light::ICaster>& GetLight() const;
  
    // There can only be one directional light source so the previous one will be oveverwritten
    void SetDirectionalLight(const DirectionalLight& light);
    // Return optional because there may be no directional light set for the scene
    const std::optional<DirectionalLight>& GetDirectionalLight() const;


private:
    // There can be multiple predefined scene vantaga point
    std::vector<Camera> cameras_;
    // Interface pointer vector to base class if renderable objects
    std::vector<std::unique_ptr<renderable::IRenderable>> renderables_;
    // Lighting type
    std::unique_ptr<light::ICaster> light_;
    // Directional light source, if it is not set default ambient light will be used
    std::optional<DirectionalLight> directional_light;
};