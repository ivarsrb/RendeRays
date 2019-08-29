#pragma once
#include <vector>
#include <limits>
#include <glm/glm.hpp>

// Common types aliasing and definition
namespace t {
using F32 = float;
using F64 = double;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;
using I16 = int16_t;
using I32 = int32_t;
// GLM linear math types aliasing
using Vec2 = glm::tvec2<F32>;
using Vec3 = glm::tvec3<F32>;
using Vec4 = glm::tvec4<F32>;
using Vec2u16 = glm::tvec2<U16>;
using Mat3 = glm::tmat3x3<F32>;
using Mat4 = glm::tmat4x4<F32>;
// Type related constants
// Special values 'positive infinity'
// NOTE: constexpr are always inline, so no redefinitions
constexpr F32 kInfinity32 = std::numeric_limits<F32>::infinity();
constexpr F64 kInfinity64 = std::numeric_limits<F64>::infinity();
// Structure to store size dimensions
struct Size16 {
    U16 width;
    U16 height;
};
struct Size32 {
    U32 width;
    U32 height;
};
// Buffer type for color valued
using ColorBuffer = std::vector<Vec3>;
// Common colors
constexpr Vec3 kColorBlask = Vec3(0.0);
constexpr Vec3 kColorBWhite = Vec3(1.0);
constexpr Vec3 kColorGray = Vec3(0.5, 0.5, 0.5);
constexpr Vec3 kColorRed = Vec3(1.0, 0.0, 0.0);
constexpr Vec3 kColorBlue = Vec3(0.0, 0.0, 1.0);
constexpr Vec3 kColorGreen = Vec3(0.0, 1.0, 0.0);
// Type compile-time checks
static_assert(sizeof(F32) == 4);
static_assert(sizeof(F64) == 8);
// Weather compiler implements IEEE 754  floating point standard
static_assert(std::numeric_limits<double>::is_iec559);
};