#include "swr/rasterizer.hpp"
#include "swr/framebuffer.hpp"
#include "swr/math/triangle.hpp"
#include "swr/math/vec2.hpp"
#include "swr/math/vec3.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <memory>

namespace swr {
using swr::math::Vec2;
using swr::math::Vec3;

int version() {
    return 1;
}

Rasterizer::Rasterizer(std::unique_ptr<Framebuffer> colorBuffer)
    : colorBuffer_(std::move(colorBuffer)) {}

void Rasterizer::DrawCircle(Vec2 center, float radius, Color color) {
    for (float y = center.y() - radius; y <= center.y() + radius; y++) {
        for (float x = center.x() - radius; x <= center.x() + radius; x++) {
            // NOTE: take the distance between the center and a point then calculate the length
            float distance = Vec2{center.x() - x, center.y() - y}.length();
            if (distance <= radius) {
                colorBuffer_->SetPixel(x, y, color);
            }
        }
    }
}

// NOTE: Try convert this to a 3D triangle, I think I can introduce it
// simply by adding Z to the formula and follow the rules
// Question: Can this 2D function represent 3D depth?
void Rasterizer::DrawTriangle(Vec3 a, Vec3 b, Vec3 c, Color color) {
    const int ax = static_cast<int>(a.x());
    const int ay = static_cast<int>(a.y());
    const int bx = static_cast<int>(b.x());
    const int by = static_cast<int>(b.y());
    const int cx = static_cast<int>(c.x());
    const int cy = static_cast<int>(c.y());

    // Unused
    // const int az = static_cast<int>(a.z());
    // const int bz = static_cast<int>(b.z());
    // const int cz = static_cast<int>(c.z());

    const int bbminx = std::min({ax, bx, cx});
    const int bbminy = std::min({ay, by, cy});
    const int bbmaxx = std::max({ax, bx, cx});
    const int bbmaxy = std::max({ay, by, cy});

    const double totalArea = math::SignedTriangleArea(ax, ay, bx, by, cx, cy);
    if (totalArea == 0.0) {
        return;
    }

    for (int y = bbminy; y <= bbmaxy; y++) {
        for (int x = bbminx; x <= bbmaxx; x++) {
            const double alpha = math::SignedTriangleArea(x, y, bx, by, cx, cy) / totalArea;
            const double beta = math::SignedTriangleArea(x, y, cx, cy, ax, ay) / totalArea;
            const double gamma = math::SignedTriangleArea(x, y, ax, ay, bx, by) / totalArea;

            // So the farther inside the bigger the numbers?
            if (alpha <= 0.2f || beta <= 0.2f || gamma <= 0.2f) {
                colorBuffer_->SetPixel(x, y, color);
            }
        }
    }
}

void Rasterizer::Clear() {
    colorBuffer_->Clear();
}

} // namespace swr
