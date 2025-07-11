#include "TransformComponent.h"
#include <cmath>

TransformComponent::TransformComponent()
    : m_position(VGet(0, 0, 0))
    , m_velocity(VGet(0, 0, 0))
    , m_rotation(VGet(0, 0, 0))
    , m_scale(VGet(1, 1, 1))
{
}

TransformComponent::TransformComponent(const VECTOR& pos)
    : m_position(pos)
    , m_velocity(VGet(0, 0, 0))
    , m_rotation(VGet(0, 0, 0))
    , m_scale(VGet(1, 1, 1))
{
}


void TransformComponent::Update(float deltaTime)
{
    // 0.0001f ‚Ì2æ‚Í 0.00000001f
    const float minVelocitySq = 0.0001f * 0.0001f;

    // ”äŠr‘ÎÛ‚Ì’l‚à2æ‚·‚é
    if (VSquareSize(m_velocity) > minVelocitySq)
    {
        VECTOR velocityForFrame = VScale(m_velocity, deltaTime);
        m_position = VAdd(m_position, velocityForFrame);
    }
}

const VECTOR& TransformComponent::GetPosition() const { return m_position; }
void TransformComponent::SetPosition(const VECTOR& pos) { m_position = pos; }

const VECTOR& TransformComponent::GetVelocity() const { return m_velocity; }
void TransformComponent::SetVelocity(const VECTOR& vel) { m_velocity = vel; }

const VECTOR& TransformComponent::GetRotation() const { return m_rotation; }
void TransformComponent::SetRotation(const VECTOR& rot) { m_rotation = rot; }

const VECTOR& TransformComponent::GetScale() const
{
    return m_scale;
}

void TransformComponent::SetScale(const VECTOR& scale)
{
    m_scale = scale;
}

VECTOR TransformComponent::GetForward() const
{
    float yaw = m_rotation.y;
    return VNorm(VGet(sinf(yaw), 0.0f, cosf(yaw)));
}