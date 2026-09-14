#pragma once

#include "swr/math/vec3.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <optional>
namespace swr::math {
class Mat3 {
  public:
    static constexpr Mat3 Zero() {
        return Mat3{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}};
    }

    static constexpr Mat3 Identity() {
        // clang-format off
        return Mat3{{
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
        }};
        // clang-format on
    }

  public:
    constexpr explicit Mat3(std::array<float, 9> values) : m_(values) {}

    constexpr float& operator()(std::size_t row, std::size_t column) {
        assert(row < 3 && column < 3);
        return m_[row * 3 + column];
    }

    constexpr float operator()(std::size_t row, std::size_t column) const {
        assert(row < 3 && column < 3);
        return m_[row * 3 + column];
    }

    constexpr Mat3 operator+(const Mat3& other) const {
        Mat3 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] + other.m_[index];
        }
        return result;
    }

    constexpr Mat3 operator-(const Mat3& other) const {
        Mat3 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] - other.m_[index];
        }
        return result;
    }

    constexpr Mat3 operator*(const float& other) const {
        Mat3 result = Zero();
        for (std::size_t i = 0; i < m_.size(); i++) {
            result.m_[i] = m_[i] * other;
        }

        return result;
    }

    constexpr Mat3 operator*(const Mat3& other) const {
        Mat3 result = Zero();
        for (std::size_t row = 0; row < 3; row++) {
            for (std::size_t col = 0; col < 3; col++) {
                for (std::size_t i = 0; i < 3; i++) {
                    result(row, col) += (*this)(row, i) * other(i, col);
                }
            }
        }
        return result;
    }

    constexpr Vec3 operator*(const Vec3& other) const {
        return Vec3{
            (*this)(0, 0) * other.x() + (*this)(0, 1) * other.y() + (*this)(0, 2) * other.z(),
            (*this)(1, 0) * other.x() + (*this)(1, 1) * other.y() + (*this)(1, 2) * other.z(),
            (*this)(2, 0) * other.x() + (*this)(2, 1) * other.y() + (*this)(2, 2) * other.z(),
        };
    }

    constexpr void T() {
        Mat3 result = Mat3::Zero();
        for (std::size_t row = 0; row < 3; row++) {
            for (std::size_t col = 0; col < 3; col++) {
                result(col, row) = (*this)(row, col);
            }
        }

        m_ = result.m_;
    }

    constexpr float determinant() const {
        const float m00 = (*this)(0, 0);
        const float m01 = (*this)(0, 1);
        const float m02 = (*this)(0, 2);
        const float m10 = (*this)(1, 0);
        const float m11 = (*this)(1, 1);
        const float m12 = (*this)(1, 2);
        const float m20 = (*this)(2, 0);
        const float m21 = (*this)(2, 1);
        const float m22 = (*this)(2, 2);

        const float minor00 = m11 * m22 - m12 * m21;
        const float minor01 = m10 * m22 - m12 * m20;
        const float minor02 = m10 * m21 - m11 * m20;

        return m00 * minor00 - m01 * minor01 + m02 * minor02;
    }

    constexpr std::optional<Mat3> inverse() const {
        const float m00 = (*this)(0, 0);
        const float m01 = (*this)(0, 1);
        const float m02 = (*this)(0, 2);
        const float m10 = (*this)(1, 0);
        const float m11 = (*this)(1, 1);
        const float m12 = (*this)(1, 2);
        const float m20 = (*this)(2, 0);
        const float m21 = (*this)(2, 1);
        const float m22 = (*this)(2, 2);

        const float determinantValue = determinant();
        if (determinantValue >= -std::numeric_limits<float>::epsilon() &&
            determinantValue <= std::numeric_limits<float>::epsilon()) {
            return std::nullopt;
        }
        const float inverseDeterminant = 1.0F / determinantValue;

        return Mat3{{
            (m11 * m22 - m12 * m21) * inverseDeterminant,
            (m02 * m21 - m01 * m22) * inverseDeterminant,
            (m01 * m12 - m02 * m11) * inverseDeterminant,
            (m12 * m20 - m10 * m22) * inverseDeterminant,
            (m00 * m22 - m02 * m20) * inverseDeterminant,
            (m02 * m10 - m00 * m12) * inverseDeterminant,
            (m10 * m21 - m11 * m20) * inverseDeterminant,
            (m01 * m20 - m00 * m21) * inverseDeterminant,
            (m00 * m11 - m01 * m10) * inverseDeterminant,
        }};
    }

  private:
    std::array<float, 9> m_{};
};

} // namespace swr::math
