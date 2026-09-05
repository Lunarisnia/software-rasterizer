#pragma once

#include "swr/color.hpp"
#include "swr/framebuffer.hpp"
#include "swr/math/vec2.hpp"
#include <memory>

namespace swr {

int version();
class Rasterizer {
  public:
    void SetColorBuffer(std::unique_ptr<Framebuffer>);

    void DrawCircle(swr::math::Vec2 center, float radius, Color color);

    void Clear();

  private:
    std::unique_ptr<Framebuffer> colorBuffer_;
};

} // namespace swr
