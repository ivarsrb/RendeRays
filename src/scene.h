#pragma once
#include <vector>
#include <memory>
#include "camera.h"
#include "renderable/i_renderable.h"

// Stores renderable data, lights and camera
class Scene {
public:
    Scene();
    void AddCanera(const Camera& camera);
    const std::vector<Camera>& GetCameras() const;
    void AddRenderable(std::unique_ptr<renderable::IRenderable> renderable);
    const std::vector<std::unique_ptr<renderable::IRenderable>>& GetRenderables() const;
private:
    // There can be multiple predefined scene vantaga point
    std::vector<Camera> cameras_;
    // Interface pointer vector to base class if renderable objects
    std::vector<std::unique_ptr<renderable::IRenderable>> renderables_;
};