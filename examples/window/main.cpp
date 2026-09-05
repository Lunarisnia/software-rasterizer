#include "fmt/base.h"
#include "swr/rasterizer.hpp"
#include "swr/window.hpp"

#include <fmt/format.h>

#include <chrono>
#include <thread>

int main() {
    fmt::println("=== Running: {} ===", swr::version());

    auto sdl = swr::SdlContext::create();
    if (!sdl) {
        fmt::println(stderr, "SDL initialization failed: {}", sdl.error());
        return 1;
    }

    auto window = swr::Window::create(800, 600, "Software Rasterizer");
    if (!window) {
        fmt::println(stderr, "Window creation failed: {}", window.error());
        return 1;
    }

    while (window->process_events()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}
