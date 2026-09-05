#include "fmt/base.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "swr/rasterizer.hpp"
#include "swr/window.hpp"

#include <SDL3/SDL.h>
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
    auto* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                      texture_width, texture_height);
    if (texture == nullptr) {
        fmt::println(stderr, "Texture creation failed: {}", SDL_GetError());
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        return 1;
    }

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Raster Output");
        ImGui::Image(reinterpret_cast<ImTextureID>(texture),
                     ImVec2(static_cast<float>(texture_width), static_cast<float>(texture_height)));
        ImGui::End();

        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        const SDL_FRect rectangle{100.0F, 100.0F, 300.0F, 200.0F};
        SDL_RenderFillRect(renderer, &rectangle);

        SDL_SetRenderTarget(renderer, nullptr);

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    SDL_DestroyTexture(texture);
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
