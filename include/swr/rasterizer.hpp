#pragma once

#include "swr/color.hpp"
#include "swr/framebuffer.hpp"
#include "swr/math/vec2.hpp"
#include "swr/math/vec3.hpp"
#include <memory>

namespace swr {

int version();
class Rasterizer {
  public:
    explicit Rasterizer(std::unique_ptr<Framebuffer> colorBuffer);

    void DrawCircle(math::Vec2 center, float radius, Color color);
    void DrawTriangle(math::Vec3 a, math::Vec3 b, math::Vec3 c, Color color);

    void Clear();

  private:
    std::unique_ptr<Framebuffer> colorBuffer_;
};

} // namespace swr
