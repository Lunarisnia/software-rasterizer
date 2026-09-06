#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "swr/rasterizer.hpp"

#include <memory>

TEST_CASE("rasterizer reports its version") {
    CHECK(swr::version() == 1);
}

TEST_CASE("rasterizer accepts a color buffer") {
    auto color_buffer = std::make_unique<swr::Framebuffer>(320, 200);
    swr::Rasterizer rasterizer(std::move(color_buffer));

    CHECK(color_buffer == nullptr);
}

TEST_CASE("rasterizer draws a circle center pixel") {
    auto color_buffer = std::make_unique<swr::Framebuffer>(3, 3);
    auto* framebuffer = color_buffer.get();
    swr::Rasterizer rasterizer(std::move(color_buffer));

    const swr::Color color{
        .red = 255,
        .green = 0,
        .blue = 0,
        .alpha = 255,
    };
    rasterizer.DrawCircle({1.0F, 1.0F}, 0.0F, color);

    CHECK(framebuffer->Data()[4].red == color.red);
    CHECK(framebuffer->Data()[4].green == color.green);
    CHECK(framebuffer->Data()[4].blue == color.blue);
    CHECK(framebuffer->Data()[4].alpha == color.alpha);
}
