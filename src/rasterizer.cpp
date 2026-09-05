#include "swr/rasterizer.hpp"
#include "fmt/base.h"
#include "swr/framebuffer.hpp"
#include "swr/math/vec2.hpp"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <memory>

namespace swr {
using swr::math::Vec2;

int version() {
    return 1;
}

void Rasterizer::SetColorBuffer(std::unique_ptr<Framebuffer> colorBuffer) {
    colorBuffer_ = std::move(colorBuffer);
}

void Rasterizer::DrawCircle(Vec2 center, float radius, Color color) {
    if (!colorBuffer_) {
        return;
    }

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

void Rasterizer::Clear() {
    if (!colorBuffer_) {
        return;
    }

    colorBuffer_->Clear();
}

} // namespace swr
