#pragma once
#include <cmath> // sqrtf���g�p����ꍇ�Ȃǂ�

struct Vector2I
{
    int x;
    int y;

    // �R���X�g���N�^
    // NOTE: constexpr�ŃR���p�C�����萔�Ƃ��Ă����p�\��
	// NOTE: noexcept��t���邱�ƂŁA��O�𓊂��Ȃ����Ƃ𖾎�
    constexpr Vector2I(int _x = 0, int _y = 0) noexcept : x(_x), y(_y) {}

    // --- �P�����Z�q ---
    constexpr Vector2I operator+() const noexcept
    {
        return *this;
    }
    constexpr Vector2I operator-() const noexcept
    {
        return Vector2I(-x, -y);
    }

    // --- �񍀉��Z�q (Vector2I) ---
    constexpr Vector2I operator+(const Vector2I& other) const noexcept
    {
        return Vector2I(x + other.x, y + other.y);
    }
    constexpr Vector2I operator-(const Vector2I& other) const noexcept
    {
        return Vector2I(x - other.x, y - other.y);
    }

    // --- �񍀉��Z�q (�X�J���[) ---
    constexpr Vector2I operator*(int scalar) const noexcept
    {
        return Vector2I(x * scalar, y * scalar);
    }
    constexpr Vector2I operator/(int scalar) const noexcept
    {
        // NOTE: �[�����Z�̃`�F�b�N�͌Ăяo�����ōs�����A��O�𓊂���݌v���l����
        return Vector2I(x / scalar, y / scalar);
    }

    // --- ����������Z�q (Vector2I) ---
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

    // --- ����������Z�q (�X�J���[) ---
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

    // --- ��r���Z�q ---
    constexpr bool operator==(const Vector2I& other) const noexcept
    {
        return (x == other.x) && (y == other.y);
    }
    constexpr bool operator!=(const Vector2I& other) const noexcept
    {
        return !(*this == other);
    }

    // --- �悭�g���֗��֐� ---

    // ������2���Ԃ�
    // NOTE: sqrt�͏d�������Ȃ̂ŁA�����̔�r�����Ȃ炱���炪����
    int LengthSq() const noexcept
    {
        return x * x + y * y;
    }

    // ������Ԃ�
    // NOTE: float�ŕԋp
    float Length() const noexcept
    {
        return std::sqrtf(static_cast<float>(LengthSq()));
    }
};

// �X�J���[�������ɗ���ꍇ�̏�Z (��: 2 * vec)
static constexpr Vector2I operator*(int scalar, const Vector2I& vec) noexcept
{
    return vec * scalar;
}