#pragma once

#include "swr/mesh.hpp"
#include <expected>
#include <filesystem>

namespace swr {

class OBJLoader {
  public:
    static std::expected<Mesh, std::string> Load(const std::filesystem::path& path);

  private:
    static void parseLine(Mesh& loaded, std::string& line);
    static int parseVertexNormalIndice(const std::string& section);
};

} // namespace swr
