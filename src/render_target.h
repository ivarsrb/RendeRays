#pragma once
#include <string>
#include "types.h"

// Class to which render of the scene is presented to for saving it in a file etc
// Stores as PPM file
class RenderTarget {
public:
    // filename - full path to desired output file
    RenderTarget(std::string_view filename);
    // Write to passed buffer to file of a given dimensions
    void Write(const t::ColorBuffer& buffer, const t::Size16& dimensions) const;
    // Make recorded file to pop up for convenience
    void Show() const;
private:
    // Helper function to map values  '0.0-0.01' to '0-255'
    t::U32 MapColorToInteger(t::F32 color_val) const;
    const std::string filename_;
};