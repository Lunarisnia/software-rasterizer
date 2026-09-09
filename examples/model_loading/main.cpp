#include "swr/obj_loader.hpp"

#include <filesystem>

int main() {
    swr::OBJLoader::Load(
        std::filesystem::path{"obj/african_head/african_head.obj"});
}
