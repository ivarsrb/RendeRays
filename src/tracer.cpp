#include "tracer.h"
#include "ray.h"


Tracer::Tracer()
{
}

// General high level ray tracing algorithm.
// For each pixel check all objects for camera ray intersection.
void Tracer::Render(const Scene& scene, RenderBuffer& render_buffer) const {
    // Pixel coordinates in raster space
    t::Vec2u16 raster_pixel;
    for (raster_pixel.y = 0; raster_pixel.y < render_buffer.GetHeight(); ++raster_pixel.y) {
        for (raster_pixel.x = 0; raster_pixel.x < render_buffer.GetWidth(); ++raster_pixel.x) {
            // Get a ray going from camera world position to image plane point that
            // corresponds to given pixel in raster space
            Ray primary_ray = scene.GetCameras().at(0).CastPrimaryRay(raster_pixel);

            for (const auto& renderable : scene.GetRenderables()) {
                // Intersection distance from ray origin ro the place it hit some object.
                t::F32 intersection_distance = t::kInfinity32;
                // Does this ray hit the object and if 'yes' then check if this object lies in front of object.
                if (renderable.Intersect(primary_ray, intersection_distance) && intersection_distance > 0.0) {
                    render_buffer.SetColor(raster_pixel, renderable.GetColor());
                }
            }
            /*
            // Closest intersection, set to INFINITY to start with 
            float tnear = INFINITY; 
            for (int k = 0; k < numObjects; ++k) {
                float t = INFINITY; // intersection to the current object if any 
                if objects[k]->intersect(pimaryRay, tnear) && t < tnear) {
                tnear = t;
                framebuffer = objects[k].color;
            }
            */
        }
    }
}
