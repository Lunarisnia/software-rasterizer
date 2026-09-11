#include "swr/rasterizer.hpp"
#include "swr/color.hpp"
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

Rasterizer::Rasterizer(std::unique_ptr<Framebuffer> colorBuffer,
                       std::unique_ptr<Framebuffer> depthBuffer)
    : colorBuffer_(std::move(colorBuffer)), depthBuffer_(std::move(depthBuffer)) {}

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

    const float az = a.z();
    const float bz = b.z();
    const float cz = c.z();

    const int bbminx = std::clamp(std::min({ax, bx, cx}), 0, Width() - 1);
    const int bbminy = std::clamp(std::min({ay, by, cy}), 0, Height() - 1);
    const int bbmaxx = std::clamp(std::max({ax, bx, cx}), 0, Width() - 1);
    const int bbmaxy = std::clamp(std::max({ay, by, cy}), 0, Height() - 1);

    const double totalArea = math::SignedTriangleArea(ax, ay, bx, by, cx, cy);
    if (totalArea < 1.0) {
        return;
    }

    for (int y = bbminy; y <= bbmaxy; y++) {
        for (int x = bbminx; x <= bbmaxx; x++) {
            const double alpha = math::SignedTriangleArea(x, y, bx, by, cx, cy) / totalArea;
            const double beta = math::SignedTriangleArea(x, y, cx, cy, ax, ay) / totalArea;
            const double gamma = math::SignedTriangleArea(x, y, ax, ay, bx, by) / totalArea;

            // So the farther inside the bigger the numbers?
            if (alpha < 0.0 || beta < 0.0 || gamma < 0.0) {
                continue;
            }

            const float interpolated_z = az * static_cast<float>(alpha) +
                                         bz * static_cast<float>(beta) +
                                         cz * static_cast<float>(gamma);
            if (interpolated_z <= depthBuffer_->GetPixel(x, y).red) {
                continue;
            }

            const auto z = static_cast<std::uint8_t>(std::clamp(interpolated_z, 0.0F, 255.0F));
            depthBuffer_->SetPixel(x, y, Color{z, z, z, 255});
            colorBuffer_->SetPixel(x, y, color);
        }
    }
}

void Rasterizer::Clear() {
    colorBuffer_->Clear();
    depthBuffer_->Clear();
}

int Rasterizer::Width() const {
    return colorBuffer_->Width();
}

int Rasterizer::Height() const {
    return colorBuffer_->Height();
}

} // namespace swr
