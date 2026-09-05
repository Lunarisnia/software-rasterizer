#include <doctest/doctest.h>

#include "swr/framebuffer.hpp"

TEST_CASE("framebuffer stores its dimensions") {
    const swr::Framebuffer framebuffer(320, 200);

    CHECK(framebuffer.Width() == 320);
    CHECK(framebuffer.Height() == 200);
}

TEST_CASE("framebuffer accepts pixels inside its bounds") {
    swr::Framebuffer framebuffer(2, 2);

    CHECK_NOTHROW(framebuffer.SetPixel(0, 0, {}));
    CHECK_NOTHROW(framebuffer.SetPixel(1, 1, {}));
}

TEST_CASE("framebuffer ignores pixels outside its bounds") {
    swr::Framebuffer framebuffer(2, 2);

    CHECK_NOTHROW(framebuffer.SetPixel(-1, 0, {}));
    CHECK_NOTHROW(framebuffer.SetPixel(0, -1, {}));
    CHECK_NOTHROW(framebuffer.SetPixel(2, 0, {}));
    CHECK_NOTHROW(framebuffer.SetPixel(0, 2, {}));
}
