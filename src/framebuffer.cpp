#include "swr/framebuffer.hpp"
#include <cstddef>

namespace swr {
Framebuffer::Framebuffer(int width, int height)
    : width_(width), height_(height), pixels_(static_cast<std::size_t>(width) * height) {}

int Framebuffer::Width() const {
    return width_;
}

int Framebuffer::Height() const {
    return height_;
}

void Framebuffer::SetPixel(int x, int y, Color color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }

    pixels_[static_cast<std::size_t>(y) * width_ + x] = color;
}
} // namespace swr
