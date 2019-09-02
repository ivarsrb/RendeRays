#pragma once
#include "scene.h"
#include "render_buffer.h"
#include <util/types.h>
#include "hit.h"

// Raytracing main rendering class
// Right-handed coordinate system is used: Y - up, X - to right, Z - into screen
class Tracer {
public:
    Tracer();
    // Accepts scene to be rendered and render_buffer to write color values to
    void Render(const Scene& scene, RenderBuffer& render_buffer) const;
private:
    // Calculate final color of the given screen pixel by traversing the scene
    // by shooting rays from given scene camera.
    t::Vec3 Trace(const t::Vec2u16& raster_pixel, const Scene& scene) const;
    // Modify a pixel color after lighting calculation is performed.
    // pixel_color - color of a pixel existing before lighting calculation.
    //               Calculations will alter this value.
    //               Usually this value is an object color.
    // scene - stores lighting information.
    // hit - information about current ray-object collision.
    void CalculateLighting(t::Vec3& pixel_color, const Scene& scene, const Hit& hit) const;
};