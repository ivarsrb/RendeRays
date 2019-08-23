#include "camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(const t::Vec3& position, t::F32 rot_y_degrees, t::F32 fov_degrees, 
    uint16_t raster_image_width, uint16_t raster_image_height) :
    camera_rays_(CalculateCameraRays(raster_image_width, raster_image_height)),
    raster_image_width_(raster_image_width),
    field_of_view_(glm::radians(fov_degrees)),
    world_position_(position),
    world_from_camera_(BuildWorldMatrix(position, rot_y_degrees)) {
}

// Get camre ray in world coordinates that goes from
// camera world position to point in image plane that is in front of camera
Ray Camera::CastPrimaryRay(uint16_t raster_x, uint16_t raster_y) const {
    // Transform the ray from camera space to world space to fit position and
    // orientation of a camera in the world
    Ray camera_ray = camera_rays_.at(raster_x + static_cast<size_t>(raster_y)*raster_image_width_);
    t::Vec3 world_direction = world_from_camera_ * t::Vec4(camera_ray.GetDirection(), 0.0);
    return Ray(world_position_, world_direction);
}

t::Mat4 Camera::BuildWorldMatrix(const t::Vec3& position, t::F32 rot_y_degrees) const {
    // Translate
    t::Mat4 world_matrix = glm::translate(t::Mat4(1.0), position);
    // Rotate about Y axis
    world_matrix = glm::rotate(world_matrix, glm::radians(rot_y_degrees), t::Vec3(0.0, 1.0, 0.0));
    return world_matrix;
}

// Calculate caemra rays in camera space, that is, origin of camera is at [0,0,0]
// Image plane is located in front of origin at fixed 1.0 distance. 
// For ease of use it is alway 1.0 because by changing it
// the field of view does NOT change. This would be different 
// if image plane would be located behind the back of projection center
// (camera origin) like in real pinhole camera, because changing it would alter
// field of view. In real camera this distance is called Focal length,
// but in this case it would not be right to call it like that because it
// does not affect focus or FOV. 
// This distance is for the initial ray calculation, 
// real FOV is taken into acount after that to adjust coordinates.
std::vector<Ray> Camera::CalculateCameraRays(uint16_t raster_image_width, uint16_t raster_image_height) const {
    std::vector<Ray> camera_rays;
    // Row by row starting at top left
    for (uint16_t raster_y = 0; raster_y < raster_image_height; ++raster_y) {
        for (uint16_t raster_x = 0; raster_x < raster_image_width; ++raster_x) {
            // 1.
            // Transform raster coordinates into NDC (normalized device coordinates)
            // which maps [0-screen height/width] to [0.0-1.0].
            t::F32 pixel_NDC_x = (raster_x + 0.5f) / raster_image_width;
            t::F32 pixel_NDC_y = (raster_y + 0.5f) / raster_image_height;
            // 2.
            // Transform NDC coordinates into Screen space coordinates
            // which is a coordinate in the image plane of the camera.
            // Point's coordinates in screen space vary between 
            // [-aspect ratio, aspect ratio] along the x-axis, and [-1, 1] along the y-axis.
            // Pixel origin is top-left corner.
            t::F32 raster_image_aspect_ratio = raster_image_width / static_cast<t::F32>(raster_image_height);
            t::F32 pixel_screen_x = (2.0f * pixel_NDC_x - 1.0f) * raster_image_aspect_ratio;
            t::F32 pixel_screen_y = 1.0f - 2.0f * pixel_NDC_y;
            // 3.
            // Previous step behaves as if FOV if 90 degrees, but we need to set our own FOV angle
            t::F32 tangent = tanf(field_of_view_ / 2.0f);
            pixel_screen_x *= tangent;
            pixel_screen_y *= tangent;
            // 4. 
            // Pixel coordinates in screen space
            // By default camera is facing negative z axis.
            t::Vec3 pixel_in_camera_space(pixel_screen_x, pixel_screen_y, -1.0);
            // Ray in camera space - from origin to pixel in camera space
            t::Vec3 origin(0.0, 0.0, 0.0);
            // The final camera space ray gets added 
            camera_rays.emplace_back(origin, pixel_in_camera_space);
        }
    }

    return camera_rays;
}

