#include "swr/mesh_renderer.hpp"
#include "swr/color.hpp"
#include "swr/math/vec3.hpp"
#include "swr/mesh.hpp"
#include "swr/rasterizer.hpp"

#include <cmath>
#include <utility>

namespace swr {

namespace {

// NOTE: I wonder if this math truly belongs here?
math::Vec3 TransformVertex(math::Vec3 vertex, math::Vec3 position, math::Vec3 rotation,
                           int viewport_width, int viewport_height) {
    const float cos_x = std::cos(rotation.x());
    const float sin_x = std::sin(rotation.x());
    const float y = vertex.y() * cos_x - vertex.z() * sin_x;
    const float z = vertex.y() * sin_x + vertex.z() * cos_x;
    vertex = math::Vec3{vertex.x(), y, z};

    const float cos_y = std::cos(rotation.y());
    const float sin_y = std::sin(rotation.y());
    const float x = vertex.x() * cos_y + vertex.z() * sin_y;
    const float rotated_z = -vertex.x() * sin_y + vertex.z() * cos_y;
    vertex = math::Vec3{x, vertex.y(), rotated_z};

    const float cos_z = std::cos(rotation.z());
    const float sin_z = std::sin(rotation.z());
    const float rotated_x = vertex.x() * cos_z - vertex.y() * sin_z;
    const float rotated_y = vertex.x() * sin_z + vertex.y() * cos_z;

    return math::Vec3{
        rotated_x * 300.0F + static_cast<float>(viewport_width) / 2.0F + position.x(),
        -rotated_y * 300.0F + static_cast<float>(viewport_height) / 2.0F + position.y(),
        rotated_z + position.z(),
    };
}

} // namespace

MeshRenderer::MeshRenderer(Rasterizer& rasterizer, Mesh mesh)
    : _rasterizer(rasterizer), _mesh(std::move(mesh)) {}

void MeshRenderer::SetPosition(math::Vec3 position) {
    _position = position;
}

void MeshRenderer::SetRotation(math::Vec3 rotation) {
    _rotation = rotation;
}

void MeshRenderer::Render() {
    int i = 0;
    const int viewport_width = _rasterizer.Width();
    const int viewport_height = _rasterizer.Height();
    for (const auto& triangle : _mesh.vertexIndice) {
        math::Vec3 a = TransformVertex(_mesh.vertices[triangle[0]], _position, _rotation,
                                       viewport_width, viewport_height);
        math::Vec3 b = TransformVertex(_mesh.vertices[triangle[1]], _position, _rotation,
                                       viewport_width, viewport_height);
        math::Vec3 c = TransformVertex(_mesh.vertices[triangle[2]], _position, _rotation,
                                       viewport_width, viewport_height);

        _rasterizer.DrawTriangle(a, b, c, _mesh.colors[i]);
        i++;
    }
}

} // namespace swr
