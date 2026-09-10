#pragma once

#include "swr/color.hpp"
#include "swr/math/vec3.hpp"

#include <array>
#include <vector>

namespace swr {

class Mesh {
  public:
    std::vector<Color> colors;
    std::vector<math::Vec3> vertices;
    std::vector<std::array<int, 3>> vertexIndice;
};

} // namespace swr
