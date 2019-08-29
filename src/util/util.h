#pragma once
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
}; // util