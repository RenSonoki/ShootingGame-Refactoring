#pragma once
#include <cmath> // sqrtfを使用する場合などに

struct Vector2I
{
    int x;
    int y;

    // コンストラクタ
    // NOTE: constexprでコンパイル時定数としても利用可能に
	// NOTE: noexceptを付けることで、例外を投げないことを明示
    constexpr Vector2I(int _x = 0, int _y = 0) noexcept : x(_x), y(_y) {}

    // --- 単項演算子 ---
    constexpr Vector2I operator+() const noexcept
    {
        return *this;
    }
    constexpr Vector2I operator-() const noexcept
    {
        return Vector2I(-x, -y);
    }

    // --- 二項演算子 (Vector2I) ---
    constexpr Vector2I operator+(const Vector2I& other) const noexcept
    {
        return Vector2I(x + other.x, y + other.y);
    }
    constexpr Vector2I operator-(const Vector2I& other) const noexcept
    {
        return Vector2I(x - other.x, y - other.y);
    }

    // --- 二項演算子 (スカラー) ---
    constexpr Vector2I operator*(int scalar) const noexcept
    {
        return Vector2I(x * scalar, y * scalar);
    }
    constexpr Vector2I operator/(int scalar) const noexcept
    {
        // NOTE: ゼロ除算のチェックは呼び出し側で行うか、例外を投げる設計も考える
        return Vector2I(x / scalar, y / scalar);
    }

    // --- 複合代入演算子 (Vector2I) ---
    Vector2I& operator+=(const Vector2I& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2I& operator-=(const Vector2I& other) noexcept
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // --- 複合代入演算子 (スカラー) ---
    Vector2I& operator*=(int scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2I& operator/=(int scalar) noexcept
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // --- 比較演算子 ---
    constexpr bool operator==(const Vector2I& other) const noexcept
    {
        return (x == other.x) && (y == other.y);
    }
    constexpr bool operator!=(const Vector2I& other) const noexcept
    {
        return !(*this == other);
    }

    // --- よく使う便利関数 ---

    // 長さの2乗を返す
    // NOTE: sqrtは重い処理なので、長さの比較だけならこちらが高速
    int LengthSq() const noexcept
    {
        return x * x + y * y;
    }

    // 長さを返す
    // NOTE: floatで返却
    float Length() const noexcept
    {
        return std::sqrtf(static_cast<float>(LengthSq()));
    }
};

// スカラーが左側に来る場合の乗算 (例: 2 * vec)
static constexpr Vector2I operator*(int scalar, const Vector2I& vec) noexcept
{
    return vec * scalar;
}