#include "util.h"

namespace util {
void VectorNANtoNum(t::Vec3& vec) {
    vec.x = util::NANtoNum(vec.x);
    vec.y = util::NANtoNum(vec.y);
    vec.z = util::NANtoNum(vec.z);
}

std::string StripIlligallChars(const std::string& text) {
    std::string stripped_string = text;
    const std::string illigal_chars = "\\/:?\"<>| ";
    for (auto it = stripped_string.begin(); it < stripped_string.end(); ++it) {
        bool found = (illigal_chars.find(*it) != std::string::npos);
        if (found) {
            *it = '_';
        }
    }
    return stripped_string;
}

t::Vec3 ClampColor(const t::Vec3& color) {
    return glm::clamp(color, 0.0f, 1.0f);
}
}; // util