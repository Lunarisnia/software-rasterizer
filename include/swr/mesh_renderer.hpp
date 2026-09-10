#pragma once

#include "swr/mesh.hpp"
#include "swr/rasterizer.hpp"

namespace swr {

class MeshRenderer {
  private:
    Rasterizer& _rasterizer;
    Mesh _mesh;
    math::Vec3 _position{};
    math::Vec3 _rotation{};

  public:
    explicit MeshRenderer(Rasterizer& rasterizer, Mesh mesh);

    void SetPosition(math::Vec3 position);
    void SetRotation(math::Vec3 rotation);
    void Render();
};

}; // namespace swr
