#pragma once

#include "Entity.h"
#include <memory>

// 前方宣言
class CameraComponent;
class TransformComponent;
class CameraController;
class CameraSystem;

// ゲーム中のカメラを構成する、コンポーネントがプリセットされたエンティティ
class CameraEntity : public Entity
{
public:
    CameraEntity();

    // 各コンポーネントへのアクセス用ゲッター
    std::shared_ptr<CameraComponent> GetCameraComponent() const;
    std::shared_ptr<TransformComponent> GetTransformComponent() const;
    std::shared_ptr<CameraController> GetCameraController() const;

private:
    // メンバーとして保持する必要はない（Entityの機能で取得できるため）
};