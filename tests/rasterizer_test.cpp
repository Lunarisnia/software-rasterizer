#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "swr/rasterizer.hpp"

TEST_CASE("rasterizer reports its version") {
    CHECK(swr::version() == 1);
}
