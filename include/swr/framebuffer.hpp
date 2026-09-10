#pragma once

#include "color.hpp"
#include <vector>
namespace swr {

class Framebuffer {
  public:
    Framebuffer(int width, int height);

    int Width() const;
    int Height() const;

    const Color* Data() const;
    int Pitch() const;

    void Clear();
    void SetPixel(int x, int y, Color color);
    Color GetPixel(int x, int y);

  private:
    int width_;
    int height_;

    std::vector<Color> pixels_;
};

} // namespace swr
