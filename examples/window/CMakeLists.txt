add_executable(swr_window_example
    main.cpp
)

target_link_libraries(swr_window_example PRIVATE swr::rasterizer swr::window
                      swr::imgui)
swr_enable_warnings(swr_window_example)
