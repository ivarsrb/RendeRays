#include <catch2/catch.hpp>
#include <renderable/aa_box.h>
#include <ray.h>

// Test ray - axis-alligned box intersection 
using namespace renderable;
namespace {
// Distance from ray origin to hitpoint box
t::F32 distance = -1.0f;

// Rays
Ray ray_origin_to_z(t::Vec3(0.0, 0.0, 0.0), t::Vec3(0.0, 0.0, 1.0));
Ray ray_z_to_origin(t::Vec3(0.0, 0.0, 10.0), t::Vec3(0.0, 0.0, -1.0));
Ray ray_origin_to_positive_middle(t::Vec3(0.0, 0.0, 0.0), t::Vec3(1.0, 1.0, 1.0));

// AA boxes
AABox box_o_05(t::Vec3(0.0, 0.0, 0.0), 0.5f, t::kColorBlask);
AABox box_z_05(t::Vec3(0.0, 0.0, 10.0), 0.5f, t::kColorBlask);
AABox box_small_z_05(t::Vec3(0.0, 0.0, 0.5), 0.5f, t::kColorBlask);
AABox box_minus_z_05(t::Vec3(0.0, 0.0, -10.0), 0.5f, t::kColorBlask);
AABox box_x_05(t::Vec3(10.0, 0.0, 0.0), 0.5f, t::kColorBlask);
AABox box_y_05(t::Vec3(0.0, 10.0, 0.0), 0.5f, t::kColorBlask);
AABox box_small_x_05(t::Vec3(0.5, 0.0, 1.0), 0.5f, t::kColorBlask);
AABox box_in_positive_05(t::Vec3(10.0, 10.0, 10.0), 0.5f, t::kColorBlask);


// Tests
TEST_CASE("Ray-aabox interraction, ray O to z", "[box]") {
    CHECK(box_o_05.Intersect(ray_origin_to_z, distance));
    CHECK(distance == Approx(0.5));
    CHECK(box_z_05.Intersect(ray_origin_to_z, distance));
    CHECK(distance == Approx(9.5));
    CHECK(box_small_z_05.Intersect(ray_origin_to_z, distance));
    CHECK(distance == Approx(0.0));
    CHECK_FALSE(box_minus_z_05.Intersect(ray_origin_to_z, distance));
    CHECK_FALSE(box_x_05.Intersect(ray_origin_to_z, distance));
    CHECK(box_small_x_05.Intersect(ray_origin_to_z, distance));
    CHECK(distance == Approx(0.5));
}


TEST_CASE("Ray-aabox interraction, ray z to 0", "[box]") {
    CHECK(box_o_05.Intersect(ray_z_to_origin, distance));
    CHECK(distance == Approx(9.5));
    CHECK(box_z_05.Intersect(ray_z_to_origin, distance));
    CHECK(distance == Approx(0.5));
    CHECK(box_small_z_05.Intersect(ray_z_to_origin, distance));
    CHECK(distance == Approx(9.0));
    CHECK(box_minus_z_05.Intersect(ray_z_to_origin, distance));
    CHECK(distance == Approx(19.5));
    CHECK_FALSE(box_x_05.Intersect(ray_z_to_origin, distance));
    CHECK(box_small_x_05.Intersect(ray_z_to_origin, distance));
    CHECK(distance == Approx(8.5));
}

TEST_CASE("Ray-aabox interraction, ray 0 to positive middle quadtrant", "[box]") {
    CHECK(box_o_05.Intersect(ray_origin_to_positive_middle, distance));
    CHECK(distance == Approx(0.86603));
    CHECK_FALSE(box_z_05.Intersect(ray_origin_to_positive_middle, distance));
    CHECK(box_small_z_05.Intersect(ray_origin_to_positive_middle, distance));
    CHECK(distance == Approx(0.0));
    CHECK_FALSE(box_minus_z_05.Intersect(ray_origin_to_positive_middle, distance));
    CHECK_FALSE(box_x_05.Intersect(ray_origin_to_positive_middle, distance));
    CHECK(box_small_x_05.Intersect(ray_origin_to_positive_middle, distance));
    CHECK(distance == Approx(0.86603));
    CHECK(box_in_positive_05.Intersect(ray_origin_to_positive_middle, distance));
    CHECK(distance == Approx( glm::distance(ray_origin_to_positive_middle.GetOrigin(), t::Vec3(9.5, 9.5, 9.5)) ));
}
};