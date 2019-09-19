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
    // Current pixel depth
    t::F32 nearest_hit_distance = t::kInfinity32;
    // Get a ray going from camera world position to image plane point that
    // corresponds to given pixel in raster space
    const Ray primary_ray = vantage_point.CastPrimaryRay(raster_pixel);
    for (const auto& renderable : scene.GetRenderables()) {
        // Does this ray hit the object and if 'yes' then check if this object lies in front of other object.
        if (Hit hit; renderable->Intersect(primary_ray, hit) && hit.GetDistance() < nearest_hit_distance) {
            nearest_hit_distance = hit.GetDistance();
            // Determine final pixel color by lighting
            pixel_color = renderable->GetColor();
            // Alter pixel color by performing lighting calculations
            pixel_color = CalculateLighting(pixel_color, scene, hit);
        }
    }
    // Alter pixel clor in post processing
    pixel_color = PostProcessing(pixel_color, scene, nearest_hit_distance);
    return pixel_color;
};

// Lighting is implemented using Phong shading.
// Final color of the object is calculated as:
//  final_color = ( ambient + diffuse + specular) * object_color
t::Vec3 Tracer::CalculateLighting(const t::Vec3& pixel_color, const Scene& scene, const Hit& hit) const {
    t::Vec3 ambient = scene.GetLight()->GetAmbient();
    // Diffuse color is callculated according to specific implementation of scene lighting type.
    t::Vec3 diffuse = scene.GetLight()->GetDiffuseLit(hit.GetSurfaceNormal());
    // TODO: specular calcuations should be similar to diffuse
    t::Vec3 specular = scene.GetLight()->GetSpecular();
    // Apply all colors and make sure they dont exceed 0 - 1 barrier
    return (pixel_color * util::ClampColor((ambient + diffuse + specular)));
}

// Various post processing effect one-by-one to adjust pixel color
t::Vec3 Tracer::PostProcessing(const t::Vec3& pixel_color, const Scene& scene, const t::F32& depth) const {
    t::Vec3 color = pixel_color;
    // Fog - if fog is set and depth value is not at infinity (means pixel belongs to an object)
    if (depth < t::kInfinity32 && scene.GetFog()) {
        color = util::ClampColor(scene.GetFog()->Calculate(pixel_color, depth));
    }
    return color;
}
