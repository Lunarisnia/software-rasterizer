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

    auto window = swr::Window::create(800, 600, "Software Rasterizer");
    if (!window) {
        fmt::println(stderr, "Window creation failed: {}", window.error());
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForOther(
        static_cast<SDL_Window*>(window->native_handle()));
    ImGui_ImplSDLRenderer3_Init(
        static_cast<SDL_Renderer*>(window->renderer_handle()));

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

        ImGui::Render();
        SDL_SetRenderDrawColor(
            static_cast<SDL_Renderer*>(window->renderer_handle()), 20, 20, 20, 255);
        SDL_RenderClear(static_cast<SDL_Renderer*>(window->renderer_handle()));
        ImGui_ImplSDLRenderer3_RenderDrawData(
            ImGui::GetDrawData(),
            static_cast<SDL_Renderer*>(window->renderer_handle()));
        SDL_RenderPresent(static_cast<SDL_Renderer*>(window->renderer_handle()));
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
