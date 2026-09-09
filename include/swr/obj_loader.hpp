#pragma once

#include "swr/math/vec3.hpp"
#include <filesystem>
#include <vector>

namespace swr {

class Object {
  public:
    std::vector<math::Vec3> vertices;
};

class OBJLoader {
  public:
    static void Load(const std::filesystem::path& path);

  private:
    static void parseLine(Object& loaded, std::string& line);
};

} // namespace swr
