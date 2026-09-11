#include <doctest/doctest.h>

#include "swr/math/vec2.hpp"
#include "swr/math/vec3.hpp"

TEST_CASE("Vec2 addition adds corresponding components") {
    constexpr auto result = swr::math::Vec2{1.0F, 2.0F} +
                            swr::math::Vec2{3.0F, 4.0F};

    static_assert(result.x() == 4.0F);
    static_assert(result.y() == 6.0F);
}

TEST_CASE("Vec3 addition adds corresponding components") {
    constexpr auto result = swr::math::Vec3{1.0F, 2.0F, 3.0F} +
                            swr::math::Vec3{4.0F, 5.0F, 6.0F};

    static_assert(result.x() == 5.0F);
    static_assert(result.y() == 7.0F);
    static_assert(result.z() == 9.0F);
}

TEST_CASE("Vec2 scalar addition adds to every component") {
    constexpr auto result = swr::math::Vec2{1.0F, 2.0F} + 3.0F;

    static_assert(result.x() == 4.0F);
    static_assert(result.y() == 5.0F);
}

TEST_CASE("Vec3 scalar addition adds to every component") {
    constexpr auto result = swr::math::Vec3{1.0F, 2.0F, 3.0F} + 4.0F;

    static_assert(result.x() == 5.0F);
    static_assert(result.y() == 6.0F);
    static_assert(result.z() == 7.0F);
}

TEST_CASE("Vec2 subtraction subtracts corresponding components") {
    constexpr auto result = swr::math::Vec2{4.0F, 6.0F} -
                            swr::math::Vec2{1.0F, 2.0F};

    static_assert(result.x() == 3.0F);
    static_assert(result.y() == 4.0F);
}

TEST_CASE("Vec3 subtraction subtracts corresponding components") {
    constexpr auto result = swr::math::Vec3{5.0F, 7.0F, 9.0F} -
                            swr::math::Vec3{1.0F, 2.0F, 3.0F};

    static_assert(result.x() == 4.0F);
    static_assert(result.y() == 5.0F);
    static_assert(result.z() == 6.0F);
}

TEST_CASE("Vec2 scalar division divides every component") {
    constexpr auto result = swr::math::Vec2{6.0F, 9.0F} / 3.0F;

    static_assert(result.x() == 2.0F);
    static_assert(result.y() == 3.0F);
}

TEST_CASE("Vec3 scalar division divides every component") {
    constexpr auto result = swr::math::Vec3{6.0F, 9.0F, 12.0F} / 3.0F;

    static_assert(result.x() == 2.0F);
    static_assert(result.y() == 3.0F);
    static_assert(result.z() == 4.0F);
}

TEST_CASE("Vec2 unary negation reverses every component") {
    constexpr auto result = -swr::math::Vec2{1.0F, -2.0F};

    static_assert(result.x() == -1.0F);
    static_assert(result.y() == 2.0F);
}

TEST_CASE("Vec3 unary negation reverses every component") {
    constexpr auto result = -swr::math::Vec3{1.0F, -2.0F, 3.0F};

    static_assert(result.x() == -1.0F);
    static_assert(result.y() == 2.0F);
    static_assert(result.z() == -3.0F);
}

TEST_CASE("Vec2 dot product returns the sum of component products") {
    constexpr auto result = swr::math::Vec2{1.0F, 2.0F}.dot(
        swr::math::Vec2{3.0F, 4.0F});

    static_assert(result == 11.0F);
}

TEST_CASE("Vec3 dot product returns the sum of component products") {
    constexpr auto result = swr::math::Vec3{1.0F, 2.0F, 3.0F}.dot(
        swr::math::Vec3{4.0F, 5.0F, 6.0F});

    static_assert(result == 32.0F);
}

TEST_CASE("vector length uses its dot product with itself") {
    CHECK(swr::math::Vec2{3.0F, 4.0F}.length() == doctest::Approx(5.0F));
    CHECK(swr::math::Vec3{2.0F, 3.0F, 6.0F}.length() == doctest::Approx(7.0F));
}

TEST_CASE("Vec2 squared length equals its dot product with itself") {
    constexpr swr::math::Vec2 vector{3.0F, 4.0F};

    static_assert(vector.lengthSquared() == 25.0F);
}

TEST_CASE("Vec3 squared length equals its dot product with itself") {
    constexpr swr::math::Vec3 vector{2.0F, 3.0F, 6.0F};

    static_assert(vector.lengthSquared() == 49.0F);
}
