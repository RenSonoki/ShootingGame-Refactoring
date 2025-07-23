#include "CameraEntity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "ThirdPersonCameraComponent.h" // ★ CameraControllerの代わりにこちらをインクルード

CameraEntity::CameraEntity()
{
    SetTag(L"Camera");
}

// ゲッターの実装
std::shared_ptr<CameraComponent> CameraEntity::GetCameraComponent() const { return GetComponent<CameraComponent>(); }
std::shared_ptr<TransformComponent> CameraEntity::GetTransformComponent() const { return GetComponent<TransformComponent>(); }

// ★ 修正点: 新しいTPSカメラコンポーネントを返すように実装
std::shared_ptr<ThirdPersonCameraComponent> CameraEntity::GetThirdPersonCamera() const
{
    return GetComponent<ThirdPersonCameraComponent>();
}