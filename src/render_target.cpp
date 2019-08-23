#include "render_target.h"
#include <fstream>
#include "log.h"

RenderTarget::RenderTarget(std::string_view filename) : filename_(filename) {
}

// This function writes one particular type of PPM file
// There is other type also
void RenderTarget::Write(uint16_t width, uint16_t height, const t::ColorBuffer& buffer) const {
    assert(size_t(width)*height == buffer.size());
    // Is NOT opened for binary-write
    std::ofstream ofs(filename_);
    ofs << "P3\n" << width << " " << height << "\n255\n";
    // NOTE: In case of binary-write ofs.write function should be used
    for (const auto& pixel : buffer) {
        ofs << MapColorToInteger(pixel.r) << " " << 
            MapColorToInteger(pixel.g) << " " << 
            MapColorToInteger(pixel.b) << "\n";
    }
    ofs.close();
    Log::Info("Color data of a size ", width, "x", height, " saved to file ", filename_);
}

void RenderTarget::Show() const {
    // File path opens the image file in default viewer
    system(filename_.c_str());
}

uint32_t RenderTarget::MapColorToInteger(t::F32 color_val) const{
    return static_cast<uint32_t>(255.99 * color_val);
}
