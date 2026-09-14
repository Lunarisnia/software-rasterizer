#include <doctest/doctest.h>

#include "swr/math/mat3.hpp"

TEST_CASE("Mat3x3 zero contains only zeroes") {
    constexpr auto matrix = swr::math::Mat3::Zero();

    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            CHECK(matrix(row, column) == 0.0F);
        }
    }
}

TEST_CASE("Mat3x3 identity has ones on its diagonal") {
    constexpr auto matrix = swr::math::Mat3::Identity();

    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            const float expected = row == column ? 1.0F : 0.0F;
            CHECK(matrix(row, column) == expected);
        }
    }
}

TEST_CASE("Mat3x3 addition adds corresponding elements") {
    constexpr auto result = swr::math::Mat3::Identity() + swr::math::Mat3::Identity();

    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            const float expected = row == column ? 2.0F : 0.0F;
            CHECK(result(row, column) == expected);
        }
    }
}

TEST_CASE("Mat3x3 subtraction subtracts corresponding elements") {
    constexpr auto result = swr::math::Mat3::Identity() - swr::math::Mat3::Identity();

    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            CHECK(result(row, column) == 0.0F);
        }
    }
}

TEST_CASE("Mat3x3 scalar multiplication multiplies every element") {
    // clang-format off
    constexpr swr::math::Mat3 matrix{{
         1.0F,  2.0F,  3.0F,
         4.0F,  5.0F,  6.0F,
         7.0F,  8.0F, -9.0F,
    }};
    constexpr swr::math::Mat3 expected{{
         2.0F,  4.0F,   6.0F,
         8.0F, 10.0F,  12.0F,
        14.0F, 16.0F, -18.0F,
    }};
    // clang-format on

    constexpr auto result = matrix * 2.0F;
    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            CHECK(result(row, column) == expected(row, column));
        }
    }
}

TEST_CASE("Mat3x3 multiplication computes row by column products") {
    // clang-format off
    constexpr swr::math::Mat3 left{{
        1.0F, 2.0F, 3.0F,
        4.0F, 5.0F, 6.0F,
        7.0F, 8.0F, 9.0F,
    }};
    constexpr swr::math::Mat3 right{{
        9.0F, 8.0F, 7.0F,
        6.0F, 5.0F, 4.0F,
        3.0F, 2.0F, 1.0F,
    }};
    constexpr swr::math::Mat3 expected{{
         30.0F,  24.0F, 18.0F,
         84.0F,  69.0F, 54.0F,
        138.0F, 114.0F, 90.0F,
    }};
    // clang-format on

    constexpr auto result = left * right;
    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            CHECK(result(row, column) == expected(row, column));
        }
    }
}

TEST_CASE("Mat3x3 identity preserves matrix multiplication") {
    // clang-format off
    constexpr swr::math::Mat3 matrix{{
        1.0F, 2.0F, 3.0F,
        4.0F, 5.0F, 6.0F,
        7.0F, 8.0F, 9.0F,
    }};
    // clang-format on

    constexpr auto left_identity = swr::math::Mat3::Identity() * matrix;
    constexpr auto right_identity = matrix * swr::math::Mat3::Identity();
    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            CHECK(left_identity(row, column) == matrix(row, column));
            CHECK(right_identity(row, column) == matrix(row, column));
        }
    }
}

TEST_CASE("Mat3x3 vector multiplication computes row dot products") {
    // clang-format off
    constexpr swr::math::Mat3 matrix{{
        1.0F, 2.0F, 3.0F,
        4.0F, 5.0F, 6.0F,
        7.0F, 8.0F, 9.0F,
    }};
    // clang-format on
    constexpr swr::math::Vec3 vector{1.0F, 2.0F, 3.0F};

    constexpr auto result = matrix * vector;

    static_assert(result.x() == 14.0F);
    static_assert(result.y() == 32.0F);
    static_assert(result.z() == 50.0F);
}

TEST_CASE("Mat3x3 identity preserves vector multiplication") {
    constexpr swr::math::Vec3 vector{1.0F, -2.0F, 3.0F};

    constexpr auto result = swr::math::Mat3::Identity() * vector;

    static_assert(result.x() == vector.x());
    static_assert(result.y() == vector.y());
    static_assert(result.z() == vector.z());
}

TEST_CASE("Mat3x3 transpose swaps rows and columns") {
    // clang-format off
    constexpr auto result = [] {
        swr::math::Mat3 matrix{{
            1.0F, 2.0F, 3.0F,
            4.0F, 5.0F, 6.0F,
            7.0F, 8.0F, 9.0F,
        }};
        matrix.T();
        return matrix;
    }();
    constexpr swr::math::Mat3 expected{{
        1.0F, 4.0F, 7.0F,
        2.0F, 5.0F, 8.0F,
        3.0F, 6.0F, 9.0F,
    }};
    // clang-format on

    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            CHECK(result(row, column) == expected(row, column));
        }
    }
}

TEST_CASE("Mat3x3 determinant computes signed volume scale") {
    // clang-format off
    constexpr swr::math::Mat3 matrix{{
         2.0F, -3.0F,  1.0F,
         2.0F,  0.0F, -1.0F,
         1.0F,  4.0F,  5.0F,
    }};
    // clang-format on

    static_assert(matrix.determinant() == 49.0F);
}

TEST_CASE("Mat3x3 identity determinant is one") {
    static_assert(swr::math::Mat3::Identity().determinant() == 1.0F);
}

TEST_CASE("Mat3x3 singular matrix determinant is zero") {
    // clang-format off
    constexpr swr::math::Mat3 matrix{{
        1.0F, 2.0F, 3.0F,
        2.0F, 4.0F, 6.0F,
        7.0F, 8.0F, 9.0F,
    }};
    // clang-format on

    static_assert(matrix.determinant() == 0.0F);
}

TEST_CASE("Mat3x3 inverse computes the adjugate over the determinant") {
    // clang-format off
    constexpr swr::math::Mat3 matrix{{
        1.0F, 2.0F, 3.0F,
        0.0F, 1.0F, 4.0F,
        5.0F, 6.0F, 0.0F,
    }};
    constexpr swr::math::Mat3 expected{{
        -24.0F,  18.0F,  5.0F,
         20.0F, -15.0F, -4.0F,
         -5.0F,   4.0F,  1.0F,
    }};
    // clang-format on

    constexpr auto result = matrix.inverse();
    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            CHECK(result(row, column) == expected(row, column));
        }
    }
}

TEST_CASE("Mat3x3 multiplied by its inverse produces identity") {
    // clang-format off
    constexpr swr::math::Mat3 matrix{{
        2.0F, 0.0F, 0.0F,
        0.0F, 4.0F, 0.0F,
        0.0F, 0.0F, 5.0F,
    }};
    // clang-format on

    constexpr auto result = matrix * matrix.inverse();
    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            const float expected = row == column ? 1.0F : 0.0F;
            CHECK(result(row, column) == expected);
        }
    }
}
