#pragma once
#include <string>
#include "types.h"

// Various utility functions
namespace util {
// Checks if value is NaN and return minimal nonzro positive value
template <typename T>
T NANtoNum(T value) {
    return std::isnan(value) ? std::numeric_limits<T>::min() : value;
}
// Check all vector components for NaN
void VectorNANtoNum(t::Vec3& vec);
// Strip given string from illigal characters.
// Meant for file names sfety.
std::string StripIlligallChars(const std::string& text);
// Clamp color to normal 0.0 - 1.0 range
t::Vec3 ClampColor(const t::Vec3& color);
}; // util