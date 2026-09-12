add_executable(swr_math_lab_example
    main.cpp
)

target_link_libraries(swr_math_lab_example
    PRIVATE
        fmt::fmt
        swr::math
)

swr_enable_warnings(swr_math_lab_example)
