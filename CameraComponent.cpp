#include "CameraComponent.h"

void CameraComponent::SetPosition(const VECTOR& pos)
{
    m_params.position = pos;
}

void CameraComponent::SetTarget(const VECTOR& target)
{
    m_params.target = target;
}

void CameraComponent::SetUpVector(const VECTOR& up)
{
    m_params.up = up;
}

VECTOR CameraComponent::GetPosition() const
{
    return m_params.position;
}

VECTOR CameraComponent::GetTarget() const
{
    return m_params.target;
}

VECTOR CameraComponent::GetUpVector() const
{
    return m_params.up;
}

void CameraComponent::ApplyToDxLibCamera() const
{
    SetCameraPositionAndTargetAndUpVec(m_params.position, m_params.target, m_params.up);
}

void CameraComponent::Draw()
{
    ApplyToDxLibCamera();
}