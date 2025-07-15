#include "TransformComponent.h"
#include <cmath> // Slerp�ȂǂŕK�v�ɂȂ�\�������邽�ߔO�̂���

TransformComponent::TransformComponent()
    : m_position(VGet(0.0f, 0.0f, 0.0f))
    , m_velocity(VGet(0.0f, 0.0f, 0.0f))
    , m_rotation(Quaternion::Identity()) // �P�ʃN�H�[�^�j�I���ŏ�����
    , m_scale(VGet(1.0f, 1.0f, 1.0f))
{
}

TransformComponent::TransformComponent(const VECTOR& pos)
    : m_position(pos)
    , m_velocity(VGet(0.0f, 0.0f, 0.0f))
    , m_rotation(Quaternion::Identity())
    , m_scale(VGet(1.0f, 1.0f, 1.0f))
{
}

void TransformComponent::Update(float deltaTime)
{
    if (VSquareSize(m_velocity) > 1e-8f)
    {
        m_position = VAdd(m_position, VScale(m_velocity, deltaTime));
    }
}

ComponentID TransformComponent::GetID() const
{
    return ComponentID::Transform;
}

MATRIX TransformComponent::GetWorldMatrix() const
{
    MATRIX rotMat = GetRotationMatrix();
    MATRIX scaleMat = MGetScale(m_scale);
    MATRIX transMat = MGetTranslate(m_position);

    // S -> R -> T �̏��ō���
    MATRIX worldMat = MMult(scaleMat, rotMat);
    return MMult(worldMat, transMat);
}

MATRIX TransformComponent::GetRotationMatrix() const
{
    return m_rotation.ToMatrix();
}

// --- Getters and Setters ---
const VECTOR& TransformComponent::GetPosition() const { return m_position; }
void TransformComponent::SetPosition(const VECTOR& pos) { m_position = pos; }

const VECTOR& TransformComponent::GetVelocity() const { return m_velocity; }
void TransformComponent::SetVelocity(const VECTOR& vel) { m_velocity = vel; }

const Quaternion& TransformComponent::GetRotation() const { return m_rotation; }
void TransformComponent::SetRotation(const Quaternion& rot)
{
    m_rotation = rot;
    m_rotation.Normalize();
}

void TransformComponent::SetRotation(const VECTOR& eulerAngles)
{
    m_rotation = Quaternion::FromEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

void TransformComponent::AddYaw(float angle)
{
    Quaternion yawRot = Quaternion::FromEulerAngles(0.0f, angle, 0.0f);
    m_rotation = m_rotation * yawRot; // �N�H�[�^�j�I���̐ςŉ�]������
}

void TransformComponent::AddPitch(float angle)
{
    // Pitch�̓��[�J����X������̉�]�Ƃ��č���
    Quaternion pitchRot = Quaternion::FromEulerAngles(angle, 0.0f, 0.0f);
    m_rotation = m_rotation * pitchRot;
}

const VECTOR& TransformComponent::GetScale() const { return m_scale; }
void TransformComponent::SetScale(const VECTOR& scale) { m_scale = scale; }

// --- Direction Vectors ---
VECTOR TransformComponent::GetForward() const
{
    // Z���v���X���u�O�v�Ƃ���
    return VTransform(VGet(0.0f, 0.0f, 1.0f), GetRotationMatrix());
}

VECTOR TransformComponent::GetRight() const
{
    // X���v���X���u�E�v�Ƃ���
    return VTransform(VGet(1.0f, 0.0f, 0.0f), GetRotationMatrix());
}

VECTOR TransformComponent::GetUp() const
{
    // Y���v���X���u��v�Ƃ���y�C���_�z
    return VTransform(VGet(0.0f, 1.0f, 0.0f), GetRotationMatrix());
}