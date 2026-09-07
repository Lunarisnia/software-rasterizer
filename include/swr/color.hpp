#pragma once

#include <cstdint>

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

} // namespace colors

} // namespace swr
