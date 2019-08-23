#pragma once
#include <vector>
#include "camera.h"
#include "sphere.h"

// Stores renderable data, lights and camera
class Scene {
public:
    Scene();
    void AddCanera(const Camera& camera);
    const std::vector<Camera>& GetCameras() const;
    //const Camera& GetCamera(size_t index) const;
    // A lot of times there will only be one camera, in that case use this function
    //const Camera& GetFirstCameras() const;
    void AddRenderable(const Sphere& renderable);
    const std::vector<Sphere>& GetRenderables() const;
private:
    // There can be multiple predefined scene vantaga point
    std::vector<Camera> cameras_;
    // Renderable objects
    std::vector<Sphere> renderables_;
};