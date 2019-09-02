#pragma once
#include <string>
#include "util/types.h"

// Class to which render of the scene is presented to for saving it in a file
// Stores as PPM file
class RenderTarget {
public:
    // Data that is passed are used to build final output file name
    // scene_name - name of the scene being rendered
    // render_id - number of current render of the given scene
    RenderTarget(const std::string& scene_name, t::U16 render_id);
    // Write to passed buffer to file of a given dimensions
    void Write(const t::ColorBuffer& buffer, const t::Size16& dimensions) const;
    // Make recorded file to pop up for convenience
    void Show() const;
private:
    // Create file name to be used as render target from given parameters.
    std::string BuildFileName(const std::string& scene_name, t::U16 render_id) const;
    // Helper function to map values  '0.0-0.01' to '0-255'
    t::U32 MapColorToInteger(t::F32 color_val) const;
    const std::string filename_;
};