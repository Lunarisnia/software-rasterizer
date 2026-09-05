#pragma once

#include "color.hpp"
#include <vector>
namespace swr {

class Framebuffer {
    public:
        Framebuffer(int width, int height);

        int Width() const;
        int Height() const;

        void SetPixel(int x, int y, Color color);

    private:
        int width_;
        int height_;

        std::vector<Color> pixels_;
};

}
