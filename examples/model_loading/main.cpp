#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "swr/framebuffer.hpp"
#include "swr/math/vec3.hpp"
#include "swr/mesh_renderer.hpp"
#include "swr/obj_loader.hpp"
#include "swr/rasterizer.hpp"
#include "swr/window.hpp"

#include <SDL3/SDL.h>
#include <fmt/format.h>

#include <array>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <memory>
#include <string>
#include <thread>

int main() {
    auto head = swr::OBJLoader::Load("obj/african_head/african_head.obj");
    if (!head) {
        fmt::println(stderr, "Error: {}", head.error());
        return 1;
    }

    constexpr int texture_width = 800;
    constexpr int texture_height = 600;

    auto sdl = swr::SdlContext::create();
    if (!sdl) {
        fmt::println(stderr, "SDL initialization failed: {}", sdl.error());
        return 1;
    }

    auto window = swr::Window::create(1280, 720, "Model Loading");
    if (!window) {
        fmt::println(stderr, "Window creation failed: {}", window.error());
        return 1;
    }

    auto* renderer = static_cast<SDL_Renderer*>(window->renderer_handle());
    auto* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                                      texture_width, texture_height);
    if (texture == nullptr) {
        fmt::println(stderr, "Texture creation failed: {}", SDL_GetError());
        return 1;
    }
    auto* depth_texture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                          texture_width, texture_height);
    if (depth_texture == nullptr) {
        fmt::println(stderr, "Texture creation failed: {}", SDL_GetError());
        return 1;
    }

    auto color_buffer = std::make_unique<swr::Framebuffer>(texture_width, texture_height);
    auto depth_buffer = std::make_unique<swr::Framebuffer>(texture_width, texture_height);
    auto* framebuffer = color_buffer.get();
    auto* depthbuffer = depth_buffer.get();
    swr::Rasterizer rasterizer(std::move(color_buffer), std::move(depth_buffer));

    auto head_renderer = std::make_unique<swr::MeshRenderer>(rasterizer, std::move(*head));
    float position[3]{};

    std::array<char, 512> model_path{};
    std::strncpy(model_path.data(), "obj/african_head/african_head.obj", model_path.size() - 1);
    std::string load_error;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForOther(static_cast<SDL_Window*>(window->native_handle()));
    ImGui_ImplSDLRenderer3_Init(renderer);

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        head_renderer->SetPosition(swr::math::Vec3{position[0], position[1], position[2]});

        rasterizer.Clear();
        head_renderer->Render();
        SDL_UpdateTexture(texture, nullptr, framebuffer->Data(), framebuffer->Pitch());
        SDL_UpdateTexture(depth_texture, nullptr, depthbuffer->Data(), depthbuffer->Pitch());

        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Model Loader");
        ImGui::InputText("OBJ path", model_path.data(), model_path.size());
        if (ImGui::Button("Load Model")) {
            auto loaded = swr::OBJLoader::Load(std::filesystem::path{model_path.data()});
            if (loaded) {
                head_renderer = std::make_unique<swr::MeshRenderer>(rasterizer, std::move(*loaded));
                load_error.clear();
            } else {
                load_error = loaded.error();
            }
        }
        if (!load_error.empty()) {
            ImGui::TextColored(ImVec4(1.0F, 0.3F, 0.3F, 1.0F), "%s", load_error.c_str());
        }
        ImGui::End();

        ImGui::Begin("Model Inspector");
        if (ImGui::DragFloat2("Position XY", position, 0.25F, -300.0F, 300.0F)) {
            head_renderer->SetPosition(swr::math::Vec3{position[0], position[1], position[2]});
        }
        if (ImGui::DragFloat("Position Z", &position[2], 0.01F, -2.0F, 2.0F)) {
            head_renderer->SetPosition(swr::math::Vec3{position[0], position[1], position[2]});
        }
        ImGui::End();

        ImGui::Begin("Loaded Model");
        ImGui::Image(reinterpret_cast<ImTextureID>(texture),
                     ImVec2(static_cast<float>(texture_width), static_cast<float>(texture_height)));
        ImGui::End();

        ImGui::Begin("Depth Buffer");
        ImGui::Image(reinterpret_cast<ImTextureID>(depth_texture),
                     ImVec2(static_cast<float>(texture_width), static_cast<float>(texture_height)));
        ImGui::End();

        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyTexture(texture);
}
