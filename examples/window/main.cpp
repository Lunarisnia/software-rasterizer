#include "SDL3/SDL_render.h"
#include "fmt/base.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "swr/color.hpp"
#include "swr/framebuffer.hpp"
#include "swr/math/vec2.hpp"
#include "swr/math/vec3.hpp"
#include "swr/rasterizer.hpp"
#include "swr/window.hpp"

#include <SDL3/SDL.h>
#include <fmt/format.h>

#include <chrono>
#include <memory>
#include <thread>

int main() {
    fmt::println("=== Running: {} ===", swr::version());

    auto sdl = swr::SdlContext::create();
    if (!sdl) {
        fmt::println(stderr, "SDL initialization failed: {}", sdl.error());
        return 1;
    }

    auto window = swr::Window::create(1280, 720, "Software Rasterizer");
    if (!window) {
        fmt::println(stderr, "Window creation failed: {}", window.error());
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForOther(static_cast<SDL_Window*>(window->native_handle()));
    auto* renderer = static_cast<SDL_Renderer*>(window->renderer_handle());
    ImGui_ImplSDLRenderer3_Init(renderer);

    constexpr int texture_width = 640;
    constexpr int texture_height = 360;
    auto* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                                      texture_width, texture_height);
    if (texture == nullptr) {
        fmt::println(stderr, "Texture creation failed: {}", SDL_GetError());
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        return 1;
    }

    std::unique_ptr<swr::Framebuffer> colorBuffer =
        std::make_unique<swr::Framebuffer>(texture_width, texture_height);
    auto* framebuffer = colorBuffer.get();
    swr::Rasterizer rasterizer(std::move(colorBuffer));

    SDL_Event event;
    bool running = true;

    float point_a[3]{100.0F, 100.0F, 0.0F};
    float point_b[3]{300.0F, 200.0F, 0.0F};
    float point_c[3]{200.0F, 300.0F, 0.0F};

    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        rasterizer.Clear();
        rasterizer.DrawTriangle(swr::math::Vec3{point_a[0], point_a[1], point_a[2]},
                                swr::math::Vec3{point_b[0], point_b[1], point_b[2]},
                                swr::math::Vec3{point_c[0], point_c[1], point_c[2]},
                                swr::Color{
                                    .red = 255,
                                    .green = 255,
                                    .blue = 255,
                                    .alpha = 255,
                                });
        SDL_UpdateTexture(texture, nullptr, framebuffer->Data(), framebuffer->Pitch());

        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Triangle Inspector");
        ImGui::DragFloat3("Point A", point_a, 1.0F, 0.0F, static_cast<float>(texture_width));
        ImGui::DragFloat3("Point B", point_b, 1.0F, 0.0F, static_cast<float>(texture_width));
        ImGui::DragFloat3("Point C", point_c, 1.0F, 0.0F, static_cast<float>(texture_width));
        ImGui::End();

        ImGui::Begin("Raster Output");
        ImGui::Image(reinterpret_cast<ImTextureID>(texture),
                     ImVec2(static_cast<float>(texture_width), static_cast<float>(texture_height)));
        ImGui::End();

        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    SDL_DestroyTexture(texture);
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
