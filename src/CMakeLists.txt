add_library(swr_rasterizer
    rasterizer.cpp
    framebuffer.cpp
)

add_library(swr::rasterizer ALIAS swr_rasterizer)

target_compile_features(swr_rasterizer PUBLIC cxx_std_23)

target_link_libraries(swr_rasterizer PUBLIC fmt::fmt)

target_include_directories(swr_rasterizer
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

swr_enable_warnings(swr_rasterizer)

add_library(swr_window
    window.cpp
)

add_library(swr::window ALIAS swr_window)

target_compile_features(swr_window PUBLIC cxx_std_23)

target_include_directories(swr_window
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(swr_window PUBLIC SDL3::SDL3)
swr_enable_warnings(swr_window)

add_library(swr_imgui
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

add_library(swr::imgui ALIAS swr_imgui)

target_compile_features(swr_imgui PUBLIC cxx_std_23)

target_include_directories(swr_imgui
    PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(swr_imgui
    PUBLIC
        SDL3::SDL3
)

swr_enable_warnings(swr_imgui)
