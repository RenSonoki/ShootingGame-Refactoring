#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <cassert>

CameraComponent::CameraComponent()
    : m_fov(DX_PI_F / 4.0f), m_nearClip(0.1f), m_farClip(5000.0f)
{
}

ComponentID CameraComponent::GetID() const { return ComponentID::Camera; }

void CameraComponent::SetFov(float fovAngleRad) { m_fov = fovAngleRad; }
void CameraComponent::SetNearFarClip(float nearClip, float farClip)
{
    m_nearClip = nearClip;
    m_farClip = farClip;
}

void CameraComponent::Activate() const
{
    ApplyProjectionSettings();
    ApplyViewSettings();
}

void CameraComponent::ApplyProjectionSettings() const
{
    // 射影行列（パース）に関する設定
    SetupCamera_Perspective(m_fov);
    SetCameraNearFar(m_nearClip, m_farClip);
}

void CameraComponent::ApplyViewSettings() const
{
    // ビュー行列（カメラの位置・向き）に関する設定
    auto owner = GetOwner();
    if (!owner) return;
    auto transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    VECTOR position = transform->GetPosition();
    VECTOR forward = transform->GetForward();
    VECTOR target = VAdd(position, forward);
    VECTOR up = transform->GetUp();

    // ✅ 関数リストにある、最も適切な関数を使用
    SetCameraPositionAndTargetAndUpVec(position, target, up);
}