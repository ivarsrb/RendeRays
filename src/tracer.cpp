#include "tracer.h"
#include <algorithm>
#include "ray.h"
#include <glm/common.hpp>
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
            const Ray primary_ray = scene.GetCameras().at(0).CastPrimaryRay(raster_pixel);
            for (const auto& renderable : scene.GetRenderables()) {
                // Does this ray hit the object and if 'yes' then check if this object lies in front of object.
                if (Hit hit; renderable.get()->Intersect(primary_ray, hit) && hit.GetDistance() < nearest_hit_distance) {
                    nearest_hit_distance = hit.GetDistance();
                    // Determine final pixel color by lighting
                    t::Vec3 pixel_color = renderable.get()->GetColor();
                    CalculateLighting(pixel_color, scene, hit);
                    render_buffer.SetColor(raster_pixel, pixel_color);
                }
            }
        }
    }
}

// Lighting is implemented using Phong shading.
// Final color of the object is calculated as:
//  final_color = ( ambient + diffuse + specular) * object_color
void Tracer::CalculateLighting(t::Vec3& pixel_color, const Scene& scene, const Hit& hit) const {
    t::Vec3 ambient = scene.GetLight().get()->GetAmbient();
    t::Vec3 diffuse = scene.GetLight().get()->GetDiffuse();
    t::Vec3 specular = scene.GetLight().get()->GetSpecular();



    // Apply all colors and make sure they dont exceed 0 - 1 barrier
    pixel_color *= glm::clamp((ambient + diffuse + specular), 0.0f, 1.0f);
    /*
    if (scene.GetDirectionalLight().has_value()) {
        t::F32 light_intensity = std::max(glm::dot(hit.GetSurfaceNormal(),
            scene.GetDirectionalLight().value().GetDirection()), 0.0f);
        pixel_color *= light_intensity;
    }
    */


}
