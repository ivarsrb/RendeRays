#include "timing.h"
#include "log.h"

Timing::Timing() {
    Reset();
    SetTime1();
}

// Marko first time point
void Timing::SetTime1() {
    Reset();
    time_point_1_ = std::chrono::steady_clock::now();
}

// Mark the second time point and show the difference if passed true
void Timing::SetTime2(bool show_time) {
    time_point_2_ = std::chrono::steady_clock::now();
    // Save in case printing is done later
    duration_ = GetDuration();
    if (show_time) {
        Print();
    }
}

void Timing::Reset() {
    time_point_1_ = {};
    time_point_2_ = {};
    duration_ = 0;
}

t::U64 Timing::GetDuration() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(time_point_2_ - time_point_1_).count();
}

void Timing::Print() const{
    Log::Info(duration_, " ms");
}