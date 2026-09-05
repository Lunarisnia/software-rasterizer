#include "swr/window.hpp"

#include <SDL3/SDL.h>

#include <string>
#include <utility>

namespace swr {

std::expected<SdlContext, std::string> SdlContext::create() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return std::unexpected(
            std::string("SDL initialization failed: ") + SDL_GetError());
    }

    return SdlContext{};
}

SdlContext::~SdlContext() {
    SDL_Quit();
}

struct Window::Impl {
    SDL_Window* handle{};
    SDL_Renderer* renderer{};
};

Window::Window(std::unique_ptr<Impl> impl)
    : impl_(std::move(impl)) {}

Window::Window(Window&& other) noexcept
    : impl_(std::exchange(other.impl_, nullptr)) {}

std::expected<Window, std::string>
Window::create(int width, int height, std::string_view title) {
    auto impl = std::make_unique<Impl>();
    const std::string title_string(title);
    impl->handle = SDL_CreateWindow(title_string.c_str(), width, height, 0);
    if (impl->handle == nullptr) {
        const std::string error =
            std::string("SDL window creation failed: ") + SDL_GetError();
        return std::unexpected(error);
    }

    impl->renderer = SDL_CreateRenderer(impl->handle, nullptr);
    if (impl->renderer == nullptr) {
        const std::string error =
            std::string("SDL renderer creation failed: ") + SDL_GetError();
        SDL_DestroyWindow(impl->handle);
        return std::unexpected(error);
    }

    return Window(std::move(impl));
}

Window::~Window() {
    if (impl_ != nullptr && impl_->handle != nullptr) {
        SDL_DestroyWindow(impl_->handle);
        SDL_DestroyRenderer(impl_->renderer);
    }
}

bool Window::process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }

    }
    return true;
}

void* Window::native_handle() const {
    return impl_->handle;
}

void* Window::renderer_handle() const {
    return impl_->renderer;
}

} // namespace swr
