#pragma once
#include "Entity.h"
#include <memory>

// 前方宣言
class CameraComponent;
class TransformComponent;
class ThirdPersonCameraComponent; // ★ CameraControllerの代わりにこちらを前方宣言

class CameraEntity : public Entity
{
public:
    CameraEntity();

    // ゲッター
    std::shared_ptr<CameraComponent> GetCameraComponent() const;
    std::shared_ptr<TransformComponent> GetTransformComponent() const;
    // ★ 修正点: 古いCameraControllerへのゲッターを修正
    std::shared_ptr<ThirdPersonCameraComponent> GetThirdPersonCamera() const;
};