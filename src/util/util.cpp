#include "util.h"

namespace util {
void VectorNANtoNum(t::Vec3& vec) {
    vec.x = util::NANtoNum(vec.x);
    vec.y = util::NANtoNum(vec.y);
    vec.z = util::NANtoNum(vec.z);
};
}; // util