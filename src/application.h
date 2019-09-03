#pragma once
#include "scene.h"
#include "tracer.h"
#include "render_buffer.h"

// Class that brings all unrelated parts together to form a ray tracer
class Application {
public:
    Application(int argc, char* argv[]);
    void Run();
private:
    // Renderable data is stored in scene
    Scene scene_;
    // Ray tracing engine that accepts scene and renders it
    const Tracer tracer_;
    // Final render of a raytracer is stored in  the renderbuffer
    RenderBuffer render_buffer_;
};