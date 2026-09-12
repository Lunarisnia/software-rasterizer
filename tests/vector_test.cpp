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

TEST_CASE("Vec2 normalization produces a unit vector") {
    const auto result = swr::math::Vec2{3.0F, 4.0F}.normalized();

    CHECK(result.x() == doctest::Approx(0.6F));
    CHECK(result.y() == doctest::Approx(0.8F));
    CHECK(result.length() == doctest::Approx(1.0F));
}

TEST_CASE("Vec3 normalization produces a unit vector") {
    const auto result = swr::math::Vec3{2.0F, 3.0F, 6.0F}.normalized();

    CHECK(result.x() == doctest::Approx(2.0F / 7.0F));
    CHECK(result.y() == doctest::Approx(3.0F / 7.0F));
    CHECK(result.z() == doctest::Approx(6.0F / 7.0F));
    CHECK(result.length() == doctest::Approx(1.0F));
}

TEST_CASE("normalizing zero vectors returns zero vectors") {
    const auto result2 = swr::math::Vec2{}.normalized();
    const auto result3 = swr::math::Vec3{}.normalized();

    CHECK(result2.x() == 0.0F);
    CHECK(result2.y() == 0.0F);
    CHECK(result3.x() == 0.0F);
    CHECK(result3.y() == 0.0F);
    CHECK(result3.z() == 0.0F);
}

TEST_CASE("Vec3 cross product follows the right-hand rule") {
    constexpr swr::math::Vec3 right{1.0F, 0.0F, 0.0F};
    constexpr swr::math::Vec3 up{0.0F, 1.0F, 0.0F};
    constexpr auto forward = right.cross(up);

    static_assert(forward.x() == 0.0F);
    static_assert(forward.y() == 0.0F);
    static_assert(forward.z() == 1.0F);
}

TEST_CASE("Vec3 cross product is perpendicular to both vectors") {
    constexpr swr::math::Vec3 a{1.0F, 2.0F, 3.0F};
    constexpr swr::math::Vec3 b{4.0F, 5.0F, 6.0F};
    constexpr auto result = a.cross(b);

    static_assert(result.dot(a) == 0.0F);
    static_assert(result.dot(b) == 0.0F);
}

TEST_CASE("Vec3 cross product of parallel vectors is zero") {
    constexpr auto result = swr::math::Vec3{1.0F, 2.0F, 3.0F}.cross(
        swr::math::Vec3{2.0F, 4.0F, 6.0F});

    static_assert(result.lengthSquared() == 0.0F);
}
