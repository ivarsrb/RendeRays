#include <catch2/catch.hpp>
#include <renderable/sphere.h>
#include <ray.h>

// Check if ray intersects spheres and compare distance
using namespace renderable;
namespace {
// Distance from ray origin to hitpoint on sphere
Hit hit;
// Rays
Ray ray_origin_to_z(t::Vec3(0.0, 0.0, 0.0), t::Vec3(0.0, 0.0, 1.0));
Ray ray_z_to_origin(t::Vec3(0.0, 0.0, 10.0), t::Vec3(0.0, 0.0, -1.0));
// Spheres
t::F32 small_radius = 0.5;
t::F32 big_radius = 5.0;
Sphere sphere_origin_small(t::Vec3(0.0, 0.0, 0.0), small_radius, t::kColorBlask);
Sphere sphere_z_small(t::Vec3(0.0, 0.0, 5.0), small_radius, t::kColorBlask);
Sphere sphere_minus_z_small(t::Vec3(0.0, 0.0, -5.0), small_radius, t::kColorBlask);
Sphere sphere_x_small(t::Vec3(5.0, 0.0, 0.0), small_radius, t::kColorBlask);
Sphere sphere_y_small(t::Vec3(0.0, 5.0, 0.0), small_radius, t::kColorBlask);
Sphere sphere_z_big(t::Vec3(0.0, 0.0, 5.0), big_radius, t::kColorBlask);
Sphere sphere_minus_z_big(t::Vec3(0.0, 0.0, -5.0), big_radius, t::kColorBlask);
Sphere sphere_x_big(t::Vec3(5.0, 0.0, 0.0), big_radius, t::kColorBlask);
Sphere sphere_y_big(t::Vec3(0.0, 5.0, 0.0), big_radius, t::kColorBlask);
Sphere sphere_far_z_small(t::Vec3(0.0, 0.0, 15.0), small_radius, t::kColorBlask);

// Tests
TEST_CASE("Ray-sphere interraction, ray O to z", "[sphere]") {
    CHECK(sphere_origin_small.Intersect(ray_origin_to_z, hit));
    CHECK(hit.GetDistance() == Approx(0.5));
    CHECK(sphere_z_small.Intersect(ray_origin_to_z, hit));
    CHECK(hit.GetDistance() == Approx(4.5));
    CHECK_FALSE(sphere_minus_z_small.Intersect(ray_origin_to_z, hit));
    CHECK_FALSE(sphere_x_small.Intersect(ray_origin_to_z, hit));
    CHECK_FALSE(sphere_y_small.Intersect(ray_origin_to_z, hit));
    CHECK(sphere_z_big.Intersect(ray_origin_to_z, hit));
    CHECK(hit.GetDistance() == Approx(0.0));
    CHECK(sphere_minus_z_big.Intersect(ray_origin_to_z, hit));
    CHECK(hit.GetDistance() == Approx(0.0));
    CHECK(sphere_x_big.Intersect(ray_origin_to_z, hit));
    CHECK(hit.GetDistance() == Approx(0.0));
    CHECK(sphere_y_big.Intersect(ray_origin_to_z, hit));
    CHECK(hit.GetDistance() == Approx(0.0));
}

TEST_CASE("Ray-sphere interraction, ray z to 0", "[sphere]") {
    CHECK(sphere_origin_small.Intersect(ray_z_to_origin, hit));
    CHECK(hit.GetDistance() == Approx(9.5));
    CHECK(sphere_z_small.Intersect(ray_z_to_origin, hit));
    CHECK(hit.GetDistance() == Approx(4.5));
    CHECK(sphere_minus_z_small.Intersect(ray_z_to_origin, hit));
    CHECK(hit.GetDistance() == Approx(14.5));
    CHECK_FALSE(sphere_x_small.Intersect(ray_z_to_origin, hit));
    CHECK_FALSE(sphere_y_small.Intersect(ray_z_to_origin, hit));
    CHECK(sphere_z_big.Intersect(ray_z_to_origin, hit));
    CHECK(hit.GetDistance() == Approx(0.0));
    CHECK(sphere_minus_z_big.Intersect(ray_z_to_origin, hit));
    CHECK(hit.GetDistance() == Approx(10.0));
    CHECK(sphere_x_big.Intersect(ray_z_to_origin, hit));
    CHECK(hit.GetDistance() == Approx(10.0));
    CHECK(sphere_y_big.Intersect(ray_z_to_origin, hit));
    CHECK(hit.GetDistance() == Approx(10.0));
    CHECK_FALSE(sphere_far_z_small.Intersect(ray_z_to_origin, hit));
}

};