#include <doctest/doctest.h>

#include "swr/math/mat3.hpp"
#include "swr/math/mat4.hpp"

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
    static_assert(result.has_value());
    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            CHECK((*result)(row, column) == expected(row, column));
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

    constexpr auto inverse = matrix.inverse();
    static_assert(inverse.has_value());
    constexpr auto result = matrix * *inverse;
    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            const float expected = row == column ? 1.0F : 0.0F;
            CHECK(result(row, column) == expected);
        }
    }
}

TEST_CASE("Mat3x3 inverse rejects singular and near-singular matrices") {
    // clang-format off
    constexpr swr::math::Mat3 singular{{
        1.0F, 2.0F, 3.0F,
        2.0F, 4.0F, 6.0F,
        7.0F, 8.0F, 9.0F,
    }};
    constexpr swr::math::Mat3 nearSingular{{
        1.0F, 0.0F, 0.0F,
        0.0F, 1.0F, 0.0F,
        0.0F, 0.0F, std::numeric_limits<float>::epsilon() / 2.0F,
    }};
    // clang-format on

    static_assert(!singular.inverse().has_value());
    static_assert(!nearSingular.inverse().has_value());
}

TEST_CASE("Mat4 zero and identity contain the expected elements") {
    constexpr auto zero = swr::math::Mat4::Zero();
    constexpr auto identity = swr::math::Mat4::Identity();

    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t column = 0; column < 4; ++column) {
            CHECK(zero(row, column) == 0.0F);
            CHECK(identity(row, column) == (row == column ? 1.0F : 0.0F));
        }
    }
}

TEST_CASE("Mat4 arithmetic operates on corresponding elements") {
    constexpr auto sum = swr::math::Mat4::Identity() + swr::math::Mat4::Identity();
    constexpr auto difference = sum - swr::math::Mat4::Identity();
    constexpr auto scaled = difference * 3.0F;

    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t column = 0; column < 4; ++column) {
            const float expected = row == column ? 3.0F : 0.0F;
            CHECK(scaled(row, column) == expected);
        }
    }
}

TEST_CASE("Mat4 multiplication computes row by column products") {
    // clang-format off
    constexpr swr::math::Mat4 left{{
        1.0F,  2.0F,  3.0F,  4.0F,
        5.0F,  6.0F,  7.0F,  8.0F,
        9.0F, 10.0F, 11.0F, 12.0F,
       13.0F, 14.0F, 15.0F, 16.0F,
    }};
    constexpr swr::math::Mat4 right{{
        2.0F, 0.0F, 0.0F, 0.0F,
        0.0F, 3.0F, 0.0F, 0.0F,
        0.0F, 0.0F, 4.0F, 0.0F,
        0.0F, 0.0F, 0.0F, 5.0F,
    }};
    constexpr swr::math::Mat4 expected{{
         2.0F,  6.0F, 12.0F, 20.0F,
        10.0F, 18.0F, 28.0F, 40.0F,
        18.0F, 30.0F, 44.0F, 60.0F,
        26.0F, 42.0F, 60.0F, 80.0F,
    }};
    // clang-format on

    constexpr auto result = left * right;
    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t column = 0; column < 4; ++column) {
            CHECK(result(row, column) == expected(row, column));
        }
    }
}

TEST_CASE("Mat4 vector multiplication computes row dot products") {
    // clang-format off
    constexpr swr::math::Mat4 matrix{{
         1.0F,  2.0F,  3.0F,  4.0F,
         5.0F,  6.0F,  7.0F,  8.0F,
         9.0F, 10.0F, 11.0F, 12.0F,
        13.0F, 14.0F, 15.0F, 16.0F,
    }};
    // clang-format on
    constexpr swr::math::Vec4 vector{1.0F, 2.0F, 3.0F, 4.0F};

    constexpr auto result = matrix * vector;
    static_assert(result.x() == 30.0F);
    static_assert(result.y() == 70.0F);
    static_assert(result.z() == 110.0F);
    static_assert(result.w() == 150.0F);
}

TEST_CASE("Mat4 transpose swaps rows and columns") {
    // clang-format off
    constexpr auto result = [] {
        swr::math::Mat4 matrix{{
             1.0F,  2.0F,  3.0F,  4.0F,
             5.0F,  6.0F,  7.0F,  8.0F,
             9.0F, 10.0F, 11.0F, 12.0F,
            13.0F, 14.0F, 15.0F, 16.0F,
        }};
        matrix.T();
        return matrix;
    }();
    constexpr swr::math::Mat4 expected{{
        1.0F, 5.0F,  9.0F, 13.0F,
        2.0F, 6.0F, 10.0F, 14.0F,
        3.0F, 7.0F, 11.0F, 15.0F,
        4.0F, 8.0F, 12.0F, 16.0F,
    }};
    // clang-format on

    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t column = 0; column < 4; ++column) {
            CHECK(result(row, column) == expected(row, column));
        }
    }
}

TEST_CASE("Mat4 determinant expands through three by three minors") {
    // clang-format off
    constexpr swr::math::Mat4 matrix{{
        1.0F, 2.0F, 3.0F, 4.0F,
        0.0F, 2.0F, 0.0F, 0.0F,
        0.0F, 0.0F, 3.0F, 0.0F,
        0.0F, 0.0F, 0.0F, 4.0F,
    }};
    // clang-format on

    static_assert(matrix.determinant() == 24.0F);
    static_assert(swr::math::Mat4::Identity().determinant() == 1.0F);
}

TEST_CASE("Mat4 inverse produces identity when multiplied by its matrix") {
    // clang-format off
    constexpr swr::math::Mat4 matrix{{
        2.0F, 0.0F, 0.0F, 4.0F,
        0.0F, 4.0F, 0.0F, 8.0F,
        0.0F, 0.0F, 5.0F, 5.0F,
        0.0F, 0.0F, 0.0F, 1.0F,
    }};
    // clang-format on

    constexpr auto inverse = matrix.inverse();
    static_assert(inverse.has_value());
    const auto result = matrix * *inverse;
    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t column = 0; column < 4; ++column) {
            const float expected = row == column ? 1.0F : 0.0F;
            CHECK(result(row, column) == doctest::Approx(expected));
        }
    }
}

TEST_CASE("Mat4 inverse rejects singular and near-singular matrices") {
    // clang-format off
    constexpr swr::math::Mat4 singular{{
        1.0F, 0.0F, 0.0F, 0.0F,
        0.0F, 1.0F, 0.0F, 0.0F,
        0.0F, 0.0F, 0.0F, 0.0F,
        0.0F, 0.0F, 0.0F, 1.0F,
    }};
    constexpr swr::math::Mat4 nearSingular{{
        1.0F, 0.0F, 0.0F, 0.0F,
        0.0F, 1.0F, 0.0F, 0.0F,
        0.0F, 0.0F, 1.0F, 0.0F,
        0.0F, 0.0F, 0.0F, std::numeric_limits<float>::epsilon() / 2.0F,
    }};
    // clang-format on

    static_assert(!singular.inverse().has_value());
    static_assert(!nearSingular.inverse().has_value());
}
