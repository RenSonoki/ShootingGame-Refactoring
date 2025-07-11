#pragma once
#include <cmath>
#include <algorithm> // std::clamp�ȂǁA���̏ꏊ�ŕK�v�ɂȂ�\��

// 2D�x�N�g���\����
struct VECTOR2
{
    float x = 0.0f;
    float y = 0.0f;

    // �R���X�g���N�^
    VECTOR2() = default;
    constexpr VECTOR2(float x, float y) : x(x), y(y) {}

    // --- ����������Z�q ---
    VECTOR2& operator+=(const VECTOR2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    VECTOR2& operator-=(const VECTOR2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    VECTOR2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    VECTOR2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    // --- �֗��֐� ---
    float LengthSq() const { return x * x + y * y; }
    float Length() const { return std::sqrtf(LengthSq()); }
    VECTOR2 Normalized() const
    {
        float len = Length();
        if (len > 1e-6f)
        { // �[�����Z��h�~
            return { x / len, y / len };
        }
        return { 0.0f, 0.0f };
    }
};

// --- VECTOR2�̂��߂̃O���[�o���ȉ��Z�q ---
inline constexpr VECTOR2 operator+(const VECTOR2& lhs, const VECTOR2& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }
inline constexpr VECTOR2 operator-(const VECTOR2& lhs, const VECTOR2& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
inline constexpr VECTOR2 operator*(const VECTOR2& vec, float scalar) { return { vec.x * scalar, vec.y * scalar }; }
inline constexpr VECTOR2 operator*(float scalar, const VECTOR2& vec) { return { vec.x * scalar, vec.y * scalar }; }
inline constexpr VECTOR2 operator/(const VECTOR2& vec, float scalar) { return { vec.x / scalar, vec.y / scalar }; }
// �������Ƃ̏�Z
inline constexpr VECTOR2 operator*(const VECTOR2& a, const VECTOR2& b) { return { a.x * b.x, a.y * b.y }; }
inline constexpr bool operator==(const VECTOR2& lhs, const VECTOR2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline constexpr bool operator!=(const VECTOR2& lhs, const VECTOR2& rhs) { return !(lhs == rhs); }

// -------------------------------------------------------------------------------------------------------------------------------

// UI��2D�I�u�W�F�N�g�p�̋�ԏ��N���X
class Transform2D
{
public:
    Transform2D();

    // �ʒu
    void SetPosition(const VECTOR2& pos) { m_position = pos; }
    VECTOR2 GetPosition() const { return m_position; }

    // �X�P�[��
    void SetScale(const VECTOR2& scale) { m_scale = scale; }
    VECTOR2 GetScale() const { return m_scale; }

    // ��]�i���W�A���j
    void SetRotation(float rot) { m_rotation = rot; }
    float GetRotation() const { return m_rotation; }

    // ��]�E�g�k�̒��S�_�i0.0-1.0�͈̔́j
    void SetPivot(const VECTOR2& pivot) { m_pivot = pivot; }
    VECTOR2 GetPivot() const { return m_pivot; }

    // ��Ԃ������l�ɖ߂�
    void Reset();

    // �w�肵�����[���h���W�̓_���A����Transform������`(size)�͈͓̔��ɂ��邩����
    bool Contains(const VECTOR2& worldPoint, const VECTOR2& size) const;

private:
    VECTOR2 m_position = { 0.0f, 0.0f };
    VECTOR2 m_scale = { 1.0f, 1.0f };
    float   m_rotation = 0.0f;
    VECTOR2 m_pivot = { 0.5f, 0.5f }; // ���S
};

// --- Transform2D �̎��� ---

inline Transform2D::Transform2D()
{
    // �f�t�H���g�R���X�g���N�^�̓N���X��`���ŏ������ς�
}

inline void Transform2D::Reset()
{
    m_position = { 0.0f, 0.0f };
    m_scale = { 1.0f, 1.0f };
    m_rotation = 0.0f;
    m_pivot = { 0.5f, 0.5f };
}

inline bool Transform2D::Contains(const VECTOR2& worldPoint, const VECTOR2& size) const
{
    // �X�P�[����0�ȉ��̏ꍇ�͓����蔻�肪�Ȃ����̂Ƃ���
    if (m_scale.x <= 0.0f || m_scale.y <= 0.0f) {
        return false;
    }

    // 1. �s�{�b�g�i��]�E�g�k�̒��S�j�̃I�t�Z�b�g���v�Z
    VECTOR2 pivotOffset = { m_pivot.x * size.x, m_pivot.y * size.y };

    // 2. ����Ώۂ̓_(worldPoint)���ATransform�̊�_�����_�Ƃ������W�n�ɕϊ�
    VECTOR2 pointInLocal = worldPoint - m_position - pivotOffset;

    // 3. 2�̓_���ATransform�̉�]�Ƌt�����ɉ�]������
    float sinRot = sinf(-m_rotation); // �t��]�Ȃ̂Ŋp�x�𔽓]
    float cosRot = cosf(-m_rotation);
    VECTOR2 rotatedPoint = {
        pointInLocal.x * cosRot - pointInLocal.y * sinRot,
        pointInLocal.x * sinRot + pointInLocal.y * cosRot
    };

    // 4. ��`�̔����̃T�C�Y���v�Z�i�X�P�[���K�p��j
    VECTOR2 halfSize = { (size.x * m_scale.x) / 2.0f, (size.y * m_scale.y) / 2.0f };

    // 5. ��]����Ă��Ȃ����[�J�����W�n�ŁA�_����`���i-halfSize ~ +halfSize�j�ɂ��邩����
    return (rotatedPoint.x >= -halfSize.x && rotatedPoint.x <= halfSize.x &&
        rotatedPoint.y >= -halfSize.y && rotatedPoint.y <= halfSize.y);
}