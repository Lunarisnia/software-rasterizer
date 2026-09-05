#pragma once

#include "swr/framebuffer.hpp"
#include <memory>

namespace swr {

int version();
class Rasterizer {
  public:
    void SetColorBuffer(std::unique_ptr<Framebuffer>);

  private:
    std::unique_ptr<Framebuffer> colorBuffer_;
};

} // namespace swr
