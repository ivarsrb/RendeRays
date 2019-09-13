#include "tracer.h"
#include "ray.h"
#include "util/util.h"

Tracer::Tracer() {
}

// General high level ray tracing algorithm.
// For each pixel trace the ray that goes through it and return final color value
void Tracer::Render(const Scene& scene, const Camera& vantage_point, RenderBuffer& render_buffer) const {
    // Pixel coordinates in raster space
    t::Vec2u16 raster_pixel;
    for (raster_pixel.y = 0; raster_pixel.y < render_buffer.GetHeight(); ++raster_pixel.y) {
        for (raster_pixel.x = 0; raster_pixel.x < render_buffer.GetWidth(); ++raster_pixel.x) {
            const t::Vec3 pixel_color = Trace(raster_pixel, scene, vantage_point);
            render_buffer.SetColor(raster_pixel, pixel_color);
        }
    }
}

// Calculate ray for given raster pixel
// And if it hits the object that is closer than other, 
// calculate lighting for it and return.
t::Vec3 Tracer::Trace(const t::Vec2u16& raster_pixel, const Scene& scene, const Camera& vantage_point) const {
    t::Vec3 pixel_color = scene.GetBackgroundColor();
    t::F32 nearest_hit_distance = t::kInfinity32;
    // Get a ray going from camera world position to image plane point that
    // corresponds to given pixel in raster space
    const Ray primary_ray = vantage_point.CastPrimaryRay(raster_pixel);
    for (const auto& renderable : scene.GetRenderables()) {
        // Does this ray hit the object and if 'yes' then check if this object lies in front of other object.
        if (Hit hit; renderable.get()->Intersect(primary_ray, hit) && hit.GetDistance() < nearest_hit_distance) {
            nearest_hit_distance = hit.GetDistance();
            // Determine final pixel color by lighting
            pixel_color = renderable.get()->GetColor();
            // Alter pixel color by performing lighting calculations
            CalculateLighting(pixel_color, scene, hit);
            // Post processing
            
            //pixel_color = pixel_color + hit.GetDistance();

        }
    }
    return pixel_color;
};


// Lighting is implemented using Phong shading.
// Final color of the object is calculated as:
//  final_color = ( ambient + diffuse + specular) * object_color
void Tracer::CalculateLighting(t::Vec3& pixel_color, const Scene& scene, const Hit& hit) const {
    t::Vec3 ambient = scene.GetLight()->GetAmbient();
    // Diffuse color is callculated according to specific implementation of scene lighting type.
    t::Vec3 diffuse = scene.GetLight()->GetDiffuseLit(hit.GetSurfaceNormal());
    // TODO: specular calcuations should be similar to diffuse
    t::Vec3 specular = scene.GetLight()->GetSpecular();
    // Apply all colors and make sure they dont exceed 0 - 1 barrier
    pixel_color *= util::ClampColor((ambient + diffuse + specular));
}
