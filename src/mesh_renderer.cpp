#include "swr/mesh_renderer.hpp"
#include "swr/color.hpp"
#include "swr/math/mat3.hpp"
#include "swr/math/vec3.hpp"
#include "swr/mesh.hpp"
#include "swr/rasterizer.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace swr {

math::Vec3 rot(math::Vec3 v) {
    constexpr float angle = M_PI + M_PI / 6;
    constexpr float xAngle = M_PI;
    // clang-format off
    math::Mat3 rotateY{{
        std::cos(angle), 0.0f, std::sin(angle),
        0, 1, 0,
        -std::sin(angle), 0, std::cos(angle)
    }};

    math::Mat3 rotateX{{
        1.0f, 0.0f, 0.0f,
        0.0f, std::cos(xAngle), -std::sin(xAngle),
        0.0f, std::sin(xAngle), std::cos(xAngle)
    }};
    // clang-format on
    return rotateY * rotateX * v;
}

math::Vec3 project(math::Vec3 vertex, math::Vec3 position, int viewport_width,
                   int viewport_height) {
    const float transformed_z = vertex.z() + position.z();
    const float projected_z = std::clamp((transformed_z + 1.0F) * 255.0F / 2.0F, 0.0F, 255.0F);
    const float projected_x =
        vertex.x() * 300.0F + static_cast<float>(viewport_width) / 2.0F + position.x();
    const float projected_y =
        vertex.y() * 300.0F + static_cast<float>(viewport_height) / 2.0F + position.y();

    return math::Vec3{
        projected_x,
        projected_y,
        projected_z,
    };
}

MeshRenderer::MeshRenderer(Rasterizer& rasterizer, Mesh mesh)
    : _rasterizer(rasterizer), _mesh(std::move(mesh)) {}

void MeshRenderer::SetPosition(math::Vec3 position) {
    _position = position;
}

void MeshRenderer::Render() {
    int i = 0;
    const int viewport_width = _rasterizer.Width();
    const int viewport_height = _rasterizer.Height();
    for (const auto& triangle : _mesh.vertexIndice) {
        math::Vec3 a =
            project(rot(_mesh.vertices[triangle[0]]), _position, viewport_width, viewport_height);
        math::Vec3 b =
            project(rot(_mesh.vertices[triangle[1]]), _position, viewport_width, viewport_height);
        math::Vec3 c =
            project(rot(_mesh.vertices[triangle[2]]), _position, viewport_width, viewport_height);

        _rasterizer.DrawTriangle(a, b, c, _mesh.colors[i]);
        i++;
    }
}

} // namespace swr
