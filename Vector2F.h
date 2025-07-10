#pragma once

#include <cmath> // sqrtf, fabsf など数学関数を使用するために必要

// 浮動小数点数の比較に使用する、ごくわずかな値（イプシロン）
constexpr float VECTOR_EPSILON = 1e-6f;

struct Vector2F
{
    float x;
    float y;

    // コンストラクタ
    constexpr Vector2F(float _x = 0.0f, float _y = 0.0f) noexcept : x(_x), y(_y) {}

    // --- 単項演算子 ---
    constexpr Vector2F operator+() const noexcept
    {
        return *this;
    }
    constexpr Vector2F operator-() const noexcept
    {
        return Vector2F(-x, -y);
    }

    // --- 二項演算子 (Vector2F) ---
    constexpr Vector2F operator+(const Vector2F& other) const noexcept
    {
        return Vector2F(x + other.x, y + other.y);
    }
    constexpr Vector2F operator-(const Vector2F& other) const noexcept
    {
        return Vector2F(x - other.x, y - other.y);
    }

    // --- 二項演算子 (スカラー) ---
    constexpr Vector2F operator*(float scalar) const noexcept
    {
        return Vector2F(x * scalar, y * scalar);
    }
    constexpr Vector2F operator/(float scalar) const noexcept
    {
        return Vector2F(x / scalar, y / scalar);
    }

    // --- 複合代入演算子 (Vector2F) ---
    Vector2F& operator+=(const Vector2F& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2F& operator-=(const Vector2F& other) noexcept
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // --- 複合代入演算子 (スカラー) ---
    Vector2F& operator*=(float scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2F& operator/=(float scalar) noexcept
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // --- 比較演算子 ---
    // NOTE: floatの完全一致比較は危険な場合があるため、EpsilonEqualsの使用を推奨
    constexpr bool operator==(const Vector2F& other) const noexcept
    {
        return (x == other.x) && (y == other.y);
    }
    constexpr bool operator!=(const Vector2F& other) const noexcept
    {
        return !(*this == other);
    }

    // --- よく使う便利関数 ---

    // 誤差を考慮した比較
    bool EpsilonEquals(const Vector2F& other, float epsilon = VECTOR_EPSILON) const noexcept
    {
        return (std::fabsf(x - other.x) < epsilon) &&
            (std::fabsf(y - other.y) < epsilon);
    }

    // 長さの2乗を返す
    float LengthSq() const noexcept
    {
        return x * x + y * y;
    }

    // 長さを返す
    float Length() const noexcept
    {
        return std::sqrtf(LengthSq());
    }

    // ベクトルを正規化する（長さを1にする）
    // NOTE: 方向ベクトルとして利用する際に非常に重要
    void Normalize() noexcept
    {
        float len = Length();
        if (len > VECTOR_EPSILON)
        { // ゼロベクトルでないことを確認
            x /= len;
            y /= len;
        }
    }

    // 正規化されたベクトルを新しいVector2Fとして返す（元のベクトルは変更しない）
    Vector2F GetNormalized() const noexcept
    {
        Vector2F temp = *this;
        temp.Normalize();
        return temp;
    }
};

// スカラーが左側に来る場合の乗算 (例: 2.0f * vec)
static constexpr Vector2F operator*(float scalar, const Vector2F& vec) noexcept
{
    return vec * scalar;
}