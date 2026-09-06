#pragma once

#include <cmath>

namespace swr::math {

class Vec3 {
  public:
    constexpr Vec3() = default;
    constexpr Vec3(float x, float y, float z) : x_(x), y_(y), z_(z) {}

    constexpr float x() const {
        return x_;
    }

    constexpr float y() const {
        return y_;
    }

    constexpr float z() const {
        return z_;
    }

    float length() const {
        return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

  private:
    float x_{};
    float y_{};
    float z_{};
};

} // namespace swr::math
