#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "swr/rasterizer.hpp"

#include <memory>

TEST_CASE("rasterizer reports its version") {
    CHECK(swr::version() == 1);
}

TEST_CASE("rasterizer accepts a color buffer") {
    swr::Rasterizer rasterizer;
    auto color_buffer = std::make_unique<swr::Framebuffer>(320, 200);

    CHECK_NOTHROW(rasterizer.SetColorBuffer(std::move(color_buffer)));
    CHECK(color_buffer == nullptr);
}
