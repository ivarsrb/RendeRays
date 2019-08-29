#include "tracer.h"
#include "ray.h"
#include "hit.h"

Tracer::Tracer() {
}

// General high level ray tracing algorithm.
// For each pixel check all objects for camera ray intersection.
void Tracer::Render(const Scene& scene, RenderBuffer& render_buffer) const {
    // Pixel coordinates in raster space
    t::Vec2u16 raster_pixel;
    for (raster_pixel.y = 0; raster_pixel.y < render_buffer.GetHeight(); ++raster_pixel.y) {
        for (raster_pixel.x = 0; raster_pixel.x < render_buffer.GetWidth(); ++raster_pixel.x) {
            t::F32 nearest_hit_distance = t::kInfinity32;
            // Get a ray going from camera world position to image plane point that
            // corresponds to given pixel in raster space
            Ray primary_ray = scene.GetCameras().at(0).CastPrimaryRay(raster_pixel);
            for (const auto& renderable : scene.GetRenderables()) {
                // Does this ray hit the object and if 'yes' then check if this object lies in front of object.
                if (Hit hit; renderable.get()->Intersect(primary_ray, hit) && hit.GetDistance() < nearest_hit_distance) {
                    nearest_hit_distance = hit.GetDistance();
                    render_buffer.SetColor(raster_pixel, renderable.get()->GetColor());
                }
            }
        }
    }
}
