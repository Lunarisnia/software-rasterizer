#pragma once

#include <cstdint>
#include <random>

namespace swr {

struct Color {
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    std::uint8_t alpha;
};

namespace colors {

inline constexpr Color White{255, 255, 255, 255};
inline constexpr Color Red{255, 0, 0, 255};
inline constexpr Color Green{0, 255, 0, 255};

inline Color RandomColor() {
    static thread_local std::mt19937 generator{std::random_device{}()};
    static thread_local std::uniform_int_distribution<int> channel{0, 255};

    return Color{
        static_cast<std::uint8_t>(channel(generator)),
        static_cast<std::uint8_t>(channel(generator)),
        static_cast<std::uint8_t>(channel(generator)),
        255,
    };
}

} // namespace colors

} // namespace swr
