#pragma once
#include "scene.h"
#include "render_buffer.h"

// Raytracing main rendering class
// Right-handed coordinate system is used: Y - up, X - to right, Z - into screen
class Tracer {
public:
    Tracer();
    // Accepts scene to be rendered and render_buffer to write color values to
    void Render(const Scene& scene, RenderBuffer& render_buffer) const;
private:

};