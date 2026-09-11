#pragma once

#include "swr/color.hpp"
#include "swr/framebuffer.hpp"
#include "swr/math/vec2.hpp"
#include "swr/math/vec3.hpp"
#include <memory>
#include <vector>

namespace swr {

int version();
class Rasterizer {
  public:
    explicit Rasterizer(std::unique_ptr<Framebuffer> colorBuffer,
                        std::unique_ptr<Framebuffer> depthBuffer);

    void DrawCircle(math::Vec2 center, float radius, Color color);
    void DrawTriangle(math::Vec3 a, math::Vec3 b, math::Vec3 c, Color color);

    int Width() const;
    int Height() const;

    void Clear();

  private:
    std::unique_ptr<Framebuffer> colorBuffer_;
    std::unique_ptr<Framebuffer> depthBuffer_;
};

} // namespace swr
