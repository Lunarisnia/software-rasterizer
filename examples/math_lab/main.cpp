#include "fmt/base.h"
#include "swr/math/mat3.hpp"
int main() {
    // clang-format off
    swr::math::Mat3x3 mat3{{
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
    }};
    // clang-format on
    fmt::println("Mat3: {}", mat3(0, 0));
}
