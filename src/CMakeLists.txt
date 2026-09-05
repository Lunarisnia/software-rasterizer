add_library(swr_rasterizer
    rasterizer.cpp
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
