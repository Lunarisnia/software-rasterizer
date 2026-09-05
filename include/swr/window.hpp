#pragma once

#include <expected>
#include <memory>
#include <string>
#include <string_view>

namespace swr {

class SdlContext {
public:
    static std::expected<SdlContext, std::string> create();
    ~SdlContext();

    SdlContext(const SdlContext&) = delete;
    SdlContext& operator=(const SdlContext&) = delete;
    SdlContext(SdlContext&&) = default;
    SdlContext& operator=(SdlContext&&) = delete;

private:
    SdlContext() = default;
};

class Window {
public:
    static std::expected<Window, std::string>
    create(int width, int height, std::string_view title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other) noexcept;
    Window& operator=(Window&&) = delete;

    bool process_events();

    void* native_handle() const;
    void* renderer_handle() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;

    explicit Window(std::unique_ptr<Impl> impl);
};

} // namespace swr
