#include "swr/obj_loader.hpp"

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

void OBJLoader::Load(const std::filesystem::path& path) {
    auto contents = readFile(path);
    if (!contents) {
        return;
    }
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return;
        // return std::unexpected("Could not open file: " + path.string());
    }

    Object loaded{};
    std::string line;
    while (std::getline(file, line)) {
        parseLine(loaded, line);
    }
}

void OBJLoader::parseLine(Object& loaded, std::string& line) {
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
        // TODO: face parser
    }
}

} // namespace swr
