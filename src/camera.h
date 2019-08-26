#pragma once
#include <vector>
#include "util/types.h"
#include "ray.h"

// A vantage point of the scene together with attributes that describe how
// scene is going to appear in the final render
// Pinhole camera model is implemented.
// In real-world pinhole camera film is located behind the pinhole but in virtual
// camera model the film or image plane is located infront, so that rays could be 
// cast through it.
// Right hand coordinate system is used and camera by default is alligned to -z axis.
class Camera {
public:
    // Camera position in world space
    // Camera rotation about y axis in degrees
    // Horizontal field of viw in degrees
    // Raster image dimensions in pixels
    Camera(const t::Vec3& position, t::F32 rot_y_degrees, t::F32 fov_degrees, const t::Size16& raster_image);
    // Define and return a ray going from center of projection (camera position)
    // to given pixel coordinate in raster space (after it is transformed to world space)
    Ray CastPrimaryRay(const t::Vec2u16 &raster_pixel) const;
private:
    // Create camera to world translation and rotation matrix
    t::Mat4 BuildWorldMatrix(const t::Vec3& position, t::F32 rot_y_degrees) const;
    // Pre-calculate camera rays when camera is at origin and pointing at -z
    std::vector<Ray> CalculateCameraRays(const t::Size16& raster_image) const;
    // Extrinsic parameters
    // Position of the camera in world space
    // Camera rays are generated from this position
    const t::Vec3 world_position_;
    // Determines how much of the scene we can view.
    // This in an angle that can be obeserved as we look down on x-z plane.
    // Expressed in radians.
    const t::F32 field_of_view_;
    // Precalculated collection of camera space rays row by row starting at top left.
    // Ray starts at center of coordinates space [0,0,0] and goes through
    // screen space point that corresponds to raster space index in vector
    const std::vector<Ray> camera_rays_;
    // Intrnsic parameters
    // Image dims in pixels (used for ray vector index calculation)
    const t::Size16 raster_image_;
    // Transformation matrix that determines camera space to world 
    // space transofmrations for ray calcuations.
    const t::Mat4 world_from_camera_;
};