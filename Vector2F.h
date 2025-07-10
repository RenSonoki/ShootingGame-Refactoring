#pragma once

#include <cmath> // sqrtf, fabsf �Ȃǐ��w�֐����g�p���邽�߂ɕK�v

// ���������_���̔�r�Ɏg�p����A�����킸���Ȓl�i�C�v�V�����j
constexpr float VECTOR_EPSILON = 1e-6f;

struct Vector2F
{
    float x;
    float y;

    // �R���X�g���N�^
    constexpr Vector2F(float _x = 0.0f, float _y = 0.0f) noexcept : x(_x), y(_y) {}

    // --- �P�����Z�q ---
    constexpr Vector2F operator+() const noexcept
    {
        return *this;
    }
    constexpr Vector2F operator-() const noexcept
    {
        return Vector2F(-x, -y);
    }

    // --- �񍀉��Z�q (Vector2F) ---
    constexpr Vector2F operator+(const Vector2F& other) const noexcept
    {
        return Vector2F(x + other.x, y + other.y);
    }
    constexpr Vector2F operator-(const Vector2F& other) const noexcept
    {
        return Vector2F(x - other.x, y - other.y);
    }

    // --- �񍀉��Z�q (�X�J���[) ---
    constexpr Vector2F operator*(float scalar) const noexcept
    {
        return Vector2F(x * scalar, y * scalar);
    }
    constexpr Vector2F operator/(float scalar) const noexcept
    {
        return Vector2F(x / scalar, y / scalar);
    }

    // --- ����������Z�q (Vector2F) ---
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

    // --- ����������Z�q (�X�J���[) ---
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

    // --- ��r���Z�q ---
    // NOTE: float�̊��S��v��r�͊댯�ȏꍇ�����邽�߁AEpsilonEquals�̎g�p�𐄏�
    constexpr bool operator==(const Vector2F& other) const noexcept
    {
        return (x == other.x) && (y == other.y);
    }
    constexpr bool operator!=(const Vector2F& other) const noexcept
    {
        return !(*this == other);
    }

    // --- �悭�g���֗��֐� ---

    // �덷���l��������r
    bool EpsilonEquals(const Vector2F& other, float epsilon = VECTOR_EPSILON) const noexcept
    {
        return (std::fabsf(x - other.x) < epsilon) &&
            (std::fabsf(y - other.y) < epsilon);
    }

    // ������2���Ԃ�
    float LengthSq() const noexcept
    {
        return x * x + y * y;
    }

    // ������Ԃ�
    float Length() const noexcept
    {
        return std::sqrtf(LengthSq());
    }

    // �x�N�g���𐳋K������i������1�ɂ���j
    // NOTE: �����x�N�g���Ƃ��ė��p����ۂɔ��ɏd�v
    void Normalize() noexcept
    {
        float len = Length();
        if (len > VECTOR_EPSILON)
        { // �[���x�N�g���łȂ����Ƃ��m�F
            x /= len;
            y /= len;
        }
    }

    // ���K�����ꂽ�x�N�g����V����Vector2F�Ƃ��ĕԂ��i���̃x�N�g���͕ύX���Ȃ��j
    Vector2F GetNormalized() const noexcept
    {
        Vector2F temp = *this;
        temp.Normalize();
        return temp;
    }
};

// �X�J���[�������ɗ���ꍇ�̏�Z (��: 2.0f * vec)
static constexpr Vector2F operator*(float scalar, const Vector2F& vec) noexcept
{
    return vec * scalar;
}