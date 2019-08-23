#include "tracer.h"
#include "ray.h"

Tracer::Tracer() {

}


// General high level ray tracing algorithm.
// For each pixel check all objects for camera ray intersection.
void Tracer::Render(const Scene& scene, RenderBuffer& render_buffer) const {
    // Pixel coordinates in raster space
    for (uint16_t raster_y = 0; raster_y < render_buffer.GetHeight(); ++raster_y) {
        for (uint16_t raster_x = 0; raster_x < render_buffer.GetWidth(); ++raster_x) {
            // Get a ray going from camera world position to image plane point that
            // corresponds to given pixel in raster space
            Ray primary_ray = scene.GetCameras().at(0).CastPrimaryRay(raster_x, raster_y);

            for (const auto& renderable : scene.GetRenderables()) {
                // Intersection distance from ray origin ro the place it hit some object.
                t::F32 intersection_distance = t::kInfinity32;
                // Does this ray hit the object and if 'yes' then check if this object lies in front of object.
                if (renderable.Intersect(primary_ray, intersection_distance) && intersection_distance > 0.0) {

                    render_buffer.SetColor(raster_x, raster_y, renderable.GetColor());
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
