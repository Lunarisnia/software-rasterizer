add_executable(swr_model_loading_example
    main.cpp
)

target_link_libraries(swr_model_loading_example
    PRIVATE
        swr::rasterizer
        swr::window
        swr::imgui
)

swr_enable_warnings(swr_model_loading_example)
