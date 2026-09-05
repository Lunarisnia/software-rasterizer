#include "swr/rasterizer.hpp"
#include "swr/framebuffer.hpp"
#include <memory>

namespace swr {

int version() {
    return 1;
}

void Rasterizer::SetColorBuffer(std::unique_ptr<Framebuffer> colorBuffer) {
    colorBuffer_ = std::move(colorBuffer);
}

} // namespace swr
