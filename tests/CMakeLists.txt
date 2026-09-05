include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(doctest)

add_executable(swr_tests
    rasterizer_test.cpp
    framebuffer_test.cpp
)

target_link_libraries(swr_tests PRIVATE swr::rasterizer doctest::doctest)
swr_enable_warnings(swr_tests)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(swr_tests)
