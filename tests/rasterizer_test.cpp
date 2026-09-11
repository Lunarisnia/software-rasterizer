#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "swr/rasterizer.hpp"

#include <memory>

TEST_CASE("rasterizer reports its version") {
    CHECK(swr::version() == 1);
}

TEST_CASE("rasterizer accepts a color buffer") {
    auto color_buffer = std::make_unique<swr::Framebuffer>(320, 200);
    auto depth_buffer = std::make_unique<swr::Framebuffer>(320, 200);
    swr::Rasterizer rasterizer(std::move(color_buffer), std::move(depth_buffer));

    CHECK(color_buffer == nullptr);
}

TEST_CASE("rasterizer draws a circle center pixel") {
    auto color_buffer = std::make_unique<swr::Framebuffer>(3, 3);
    auto* framebuffer = color_buffer.get();
    auto depth_buffer = std::make_unique<swr::Framebuffer>(3, 3);
    swr::Rasterizer rasterizer(std::move(color_buffer), std::move(depth_buffer));

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

TEST_CASE("rasterizer reports the color buffer dimensions") {
    auto color_buffer = std::make_unique<swr::Framebuffer>(320, 200);
    auto depth_buffer = std::make_unique<swr::Framebuffer>(320, 200);
    swr::Rasterizer rasterizer(std::move(color_buffer), std::move(depth_buffer));

    CHECK(rasterizer.Width() == 320);
    CHECK(rasterizer.Height() == 200);
}

TEST_CASE("rasterizer keeps the closest triangle at each pixel") {
    auto color_buffer = std::make_unique<swr::Framebuffer>(3, 3);
    auto* framebuffer = color_buffer.get();
    auto depth_buffer = std::make_unique<swr::Framebuffer>(3, 3);
    swr::Rasterizer rasterizer(std::move(color_buffer), std::move(depth_buffer));

    const swr::Color near_color{255, 0, 0, 255};
    const swr::Color far_color{0, 255, 0, 255};
    rasterizer.DrawTriangle({0.0F, 0.0F, 128.1F}, {2.0F, 0.0F, 128.1F},
                            {0.0F, 2.0F, 128.1F}, near_color);
    rasterizer.DrawTriangle({0.0F, 0.0F, 128.0F}, {2.0F, 0.0F, 128.0F},
                            {0.0F, 2.0F, 128.0F}, far_color);

    const auto pixel = framebuffer->GetPixel(0, 0);
    CHECK(pixel.red == near_color.red);
    CHECK(pixel.green == near_color.green);
    CHECK(pixel.blue == near_color.blue);
}

TEST_CASE("rasterizer culls back-facing triangles") {
    auto color_buffer = std::make_unique<swr::Framebuffer>(3, 3);
    auto* framebuffer = color_buffer.get();
    auto depth_buffer = std::make_unique<swr::Framebuffer>(3, 3);
    swr::Rasterizer rasterizer(std::move(color_buffer), std::move(depth_buffer));

    rasterizer.DrawTriangle({0.0F, 0.0F, 128.0F}, {0.0F, 2.0F, 128.0F},
                            {2.0F, 0.0F, 128.0F}, swr::colors::Red);

    CHECK(framebuffer->GetPixel(0, 0).alpha == 0);
}
