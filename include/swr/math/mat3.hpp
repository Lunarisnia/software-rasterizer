#pragma once

#include <array>
#include <cassert>
#include <cstddef>
namespace swr::math {
class Mat3x3 {
  public:
    static constexpr Mat3x3 Zero() {
        return Mat3x3{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}};
    }

    static constexpr Mat3x3 Identity() {
        // clang-format off
        return Mat3x3{{
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
        }};
        // clang-format on
    }

  public:
    constexpr explicit Mat3x3(std::array<float, 9> values) : m_(values) {}

    constexpr float& operator()(std::size_t row, std::size_t column) {
        assert(row < 3 && column < 3);
        return m_[row * 3 + column];
    }

    constexpr float operator()(std::size_t row, std::size_t column) const {
        assert(row < 3 && column < 3);
        return m_[row * 3 + column];
    }

    constexpr Mat3x3 operator+(const Mat3x3& other) const {
        Mat3x3 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] + other.m_[index];
        }
        return result;
    }

    constexpr Mat3x3 operator-(const Mat3x3& other) const {
        Mat3x3 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] - other.m_[index];
        }
        return result;
    }

    constexpr Mat3x3 operator*(const float& other) const {
        Mat3x3 result = Zero();
        for (std::size_t i = 0; i < m_.size(); i++) {
            result.m_[i] = m_[i] * other;
        }

        return result;
    }

    constexpr Mat3x3 operator*(const Mat3x3& other) const {
        Mat3x3 result = Zero();
        for (std::size_t row = 0; row < 3; row++) {
            for (std::size_t col = 0; col < 3; col++) {
                for (std::size_t i = 0; i < 3; i++) {
                    result(row, col) += (*this)(row, i) * other(i, col);
                }
            }
        }
        return result;
    }

  private:
    std::array<float, 9> m_{};
};

} // namespace swr::math
