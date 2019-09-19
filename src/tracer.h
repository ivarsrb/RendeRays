#pragma once
#include "scene.h"
#include "render_buffer.h"
#include <util/types.h>
#include "hit.h"
#include "camera.h"

// Raytracing main rendering class
// Right-handed coordinate system is used: Y - up, X - to right, Z - into screen
// Used to render the scene from given vantage point and write it in color buffer.
class Tracer {
public:
    Tracer();
    // Accepts scene to be rendered, viewpoint of the scene and render_buffer to write color values to
    void Render(const Scene& scene, const Camera& vantage_point, RenderBuffer& render_buffer) const;
private:
    // Calculate final color of the given screen pixel by traversing the scene
    // by shooting rays from given scene camera.
    t::Vec3 Trace(const t::Vec2u16& raster_pixel, const Scene& scene, const Camera& vantage_point) const;
    // Modify a pixel color after lighting calculation is performed.
    // pixel_color - color of a pixel existing before lighting calculation.
    //               Usually this value is an object color.
    // scene - stores lighting information.
    // hit - information about current ray-object collision.
    // Returns newly calculated pixel color
    t::Vec3 CalculateLighting(const t::Vec3& pixel_color, const Scene& scene, const Hit& hit) const;
    // Adjust given pixel color by post-processing effects that are enabled and pixel's depth if necessary
    // pixel_color - color of a pixel existing after lighting calculation.
    // scene - stores post-processing information.
    // depth - information about pixel depth
    // Returns newly calculated pixel color
    t::Vec3 PostProcessing(const t::Vec3& pixel_color, const Scene& scene, const t::F32& depth) const;
};