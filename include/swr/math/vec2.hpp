#pragma once

#include <cmath>

namespace swr::math {

class Vec2 {
  public:
    constexpr Vec2() = default;
    constexpr Vec2(float x, float y) : x_(x), y_(y) {}

    constexpr float x() const {
        return x_;
    }

    constexpr float y() const {
        return y_;
    }

    float length() const {
        return std::sqrt(x_ * x_ + y_ * y_);
    }

  private:
    float x_{};
    float y_{};
};

} // namespace swr::math
