#include "render_target.h"
#include <fstream>
#include <sstream> 
#include "log.h"

RenderTarget::RenderTarget(std::string_view filename) : 
    filename_(filename) {
}

// This function writes one particular type of PPM file
// There is other type also
void RenderTarget::Write(const t::ColorBuffer& buffer, const t::Size16& dimensions) const {
    assert(size_t(dimensions.width)* dimensions.height == buffer.size());
    std::ofstream ofs(filename_);
    /*
    ofs << "P3\n" << dimensions.width << " " << dimensions.height << "\n255\n";
    // NOTE: In case of binary-write ofs.write function should be used
    for (const auto& pixel : buffer) {
        ofs << MapColorToInteger(pixel.r) << " " << 
            MapColorToInteger(pixel.g) << " " << 
            MapColorToInteger(pixel.b) << "\n";
    }*/
   
    
    std::string file_contents( "P3\n" + std::to_string(dimensions.width) + " " 
        + std::to_string(dimensions.height) + "\n255\n");
    for (const auto& pixel : buffer) {
        // OPTI: appending every piece to string works 2x faster than concatinating and 
        // then adding the whole line 
        file_contents.append(std::to_string(MapColorToInteger(pixel.r)));
        file_contents.append(" ");
        file_contents.append(std::to_string(MapColorToInteger(pixel.g)));
        file_contents.append(" ");
        file_contents.append(std::to_string(MapColorToInteger(pixel.b)));
        file_contents.append("\n");
    }
    ofs.write(file_contents.c_str(), file_contents.size());
  
    ofs.close();
    Log::Info("Color data of a size ", dimensions.width, "x", dimensions.height, " saved to file ", filename_);
}

void RenderTarget::Show() const {
    // File path opens the image file in default viewer
    system(filename_.c_str());
}

t::U32 RenderTarget::MapColorToInteger(t::F32 color_val) const{
    return static_cast<t::U32>(255.99 * color_val);
}
