#pragma once

#include <cmath>       // sqrtf�Ȃǂ̐��w�֐�
#include <type_traits> // is_floating_point_v�Ȃǂ̌^���


// �e���v���[�g�x�N�g���\���� TVector2<T>
template <typename T>
struct TVector2
{
    T x, y;

    // --- �R���X�g���N�^ ---

    // �f�t�H���g�R���X�g���N�^
    constexpr TVector2(T _x = 0, T _y = 0) noexcept : x(_x), y(_y) {}

    // �قȂ�^��TVector2����̕ϊ��R���X�g���N�^
    // NOTE: explicit��t���A�Ӑ}���Ȃ��Öق̌^�ϊ���h��
    template <typename U>
    explicit constexpr TVector2(const TVector2<U>& other) noexcept
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {
    }

    // --- �P�����Z�q ---
    constexpr TVector2<T> operator+() const noexcept { return *this; }
    constexpr TVector2<T> operator-() const noexcept { return TVector2<T>(-x, -y); }

    // --- ����������Z�q ---
    TVector2<T>& operator+=(const TVector2<T>& other) noexcept { x += other.x; y += other.y; return *this; }
    TVector2<T>& operator-=(const TVector2<T>& other) noexcept { x -= other.x; y -= other.y; return *this; }
    TVector2<T>& operator*=(T scalar) noexcept { x *= scalar; y *= scalar; return *this; }
    TVector2<T>& operator/=(T scalar) noexcept { x /= scalar; y /= scalar; return *this; }

    // --- ��r���Z�q ---
    constexpr bool operator==(const TVector2<T>& other) const noexcept { return (x == other.x) && (y == other.y); }
    constexpr bool operator!=(const TVector2<T>& other) const noexcept { return !(*this == other); }

    // --- �֗��֐� ---

    // ������2���Ԃ�
    T LengthSq() const noexcept
    {
        return x * x + y * y;
    }

    // ������Ԃ� (�߂�l��float�œ��ꂷ��ƈ����₷��)
    float Length() const noexcept
    {
        return std::sqrtf(static_cast<float>(LengthSq()));
    }

    // �h�b�g�ρi���ρj
    T Dot(const TVector2<T>& other) const noexcept
    {
        return x * other.x + y * other.y;
    }

    // 2D�O��
    T Cross(const TVector2<T>& other) const noexcept
    {
        return x * other.y - y * other.x;
    }

    // --- �^�ɓ��������֗��֐� (C++17: if constexpr) ---

    // �x�N�g���𐳋K������i������1�ɂ���j
    // NOTE: ���������_�^(float, double)�̏ꍇ�̂ݗL���Ȏ���
    void Normalize() noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            float len = Length();
            constexpr T epsilon = static_cast<T>(1e-6);
            if (len > epsilon)
            {
                T invLen = static_cast<T>(1.0) / len;
                x *= invLen;
                y *= invLen;
            }
        }
        // �����^�Ȃǂł��̊֐����Ă΂�Ă��A�������Ȃ��i�R���p�C���G���[�ɂ��Ȃ�Ȃ��j
    }

    // ���K�����ꂽ�x�N�g����V�����C���X�^���X�Ƃ��ĕԂ�
    TVector2<T> GetNormalized() const noexcept
    {
        TVector2<T> temp = *this;
        temp.Normalize();
        return temp;
    }
};

// --- �񍀉��Z�q (�񃁃��o�֐�) ---
// NOTE: �e���v���[�g�N���X���ł͂Ȃ��A�O�Œ�`���邱�ƂŁA�l�X�Ȍ^�̍��Ӓl�ɑΉ��ł���i��Fint * TVector2<float>�Ȃǁj
//       ����̓V���v���ɂ��邽�߁AT�^�̃X�J���[�݂̂�z��

template <typename T>
constexpr TVector2<T> operator+(const TVector2<T>& lhs, const TVector2<T>& rhs) noexcept { return TVector2<T>(lhs.x + rhs.x, lhs.y + rhs.y); }

template <typename T>
constexpr TVector2<T> operator-(const TVector2<T>& lhs, const TVector2<T>& rhs) noexcept { return TVector2<T>(lhs.x - rhs.x, lhs.y - rhs.y); }

template <typename T>
constexpr TVector2<T> operator*(const TVector2<T>& vec, T scalar) noexcept { return TVector2<T>(vec.x * scalar, vec.y * scalar); }

template <typename T>
constexpr TVector2<T> operator*(T scalar, const TVector2<T>& vec) noexcept { return TVector2<T>(vec.x * scalar, vec.y * scalar); }

template <typename T>
constexpr TVector2<T> operator/(const TVector2<T>& vec, T scalar) noexcept { return TVector2<T>(vec.x / scalar, vec.y / scalar); }



// �^�G�C���A�X
using Vector2F = TVector2<float>;
using Vector2I = TVector2<int>;