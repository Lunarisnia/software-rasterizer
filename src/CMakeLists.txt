add_library(swr_rasterizer
    rasterizer.cpp
)

add_library(swr::rasterizer ALIAS swr_rasterizer)

target_compile_features(swr_rasterizer PUBLIC cxx_std_20)

target_link_libraries(swr_rasterizer PUBLIC fmt::fmt)

target_include_directories(swr_rasterizer
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

swr_enable_warnings(swr_rasterizer)
