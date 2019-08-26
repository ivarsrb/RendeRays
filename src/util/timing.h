#pragma once
#include <chrono>
#include "types.h"

// Timing for performance measurment
/*
Usage:
Timing clock;
optional:  clock.SetTime1();
Operation();
clock.SetTime2(true);
*/
namespace util {
class Timing {
public:
    // Forst time point is taken with construction
    Timing();
    // Call right before measurable code
    void SetTime1();
    // Call right after measurable code
    void SetTime2(bool show_time);
    void Print() const;
private:
    // Reset all data to 0
    void Reset();
    t::U64 GetDuration() const;
    std::chrono::steady_clock::time_point time_point_1_;
    std::chrono::steady_clock::time_point time_point_2_;
    t::U64 duration_;
};
}; // util