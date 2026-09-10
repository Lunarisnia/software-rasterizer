#include "swr/obj_loader.hpp"
#include "swr/color.hpp"

#include <array>
#include <expected>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>

namespace swr {

std::expected<std::string, std::string> readFile(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return std::unexpected("Could not open file: " + path.string());
    }

    return std::string(std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{});
}

std::expected<Mesh, std::string> OBJLoader::Load(const std::filesystem::path& path) {
    auto contents = readFile(path);
    if (!contents) {
        return std::unexpected("File not found: " + path.string());
    }
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return std::unexpected("Could not open file: " + path.string());
    }

    Mesh loaded{};
    std::string line;
    while (std::getline(file, line)) {
        parseLine(loaded, line);
        loaded.colors.emplace_back(colors::RandomColor());
    }

    return loaded;
}

void OBJLoader::parseLine(Mesh& loaded, std::string& line) {
    std::istringstream stream(line);
    std::string prefix;
    stream >> prefix;

    if (prefix == "v") {
        float x{};
        float y{};
        float z{};
        if (stream >> x >> y >> z) {
            loaded.vertices.emplace_back(x, y, z);
        }
    } else if (prefix == "f") {
        std::string firstSection;
        std::string secondSection;
        std::string thirdSection;
        stream >> firstSection;
        stream >> secondSection;
        stream >> thirdSection;
        loaded.vertexIndice.emplace_back(std::array<int, 3>{
            parseVertexNormalIndice(firstSection),
            parseVertexNormalIndice(secondSection),
            parseVertexNormalIndice(thirdSection),
        });
    }
}

// TODO: parse texture coord (also handle optionality)
// TODO: parse vertex normal
int OBJLoader::parseVertexNormalIndice(const std::string& section) {
    std::istringstream stream(section);

    std::string vertexStr;
    // uint textureCoord;
    // uint vertexNormal;

    std::getline(stream, vertexStr, '/');

    int vertex = std::stoi(vertexStr) - 1;

    return vertex;
}

} // namespace swr
