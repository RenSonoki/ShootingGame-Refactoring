#include "CameraEntity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "CameraController.h"

CameraEntity::CameraEntity()
{
    // --- コンポーネントを生成し、ただ追加するだけ ---
    // 依存関係の解決は、各コンポーネントがStart()で自動的に行う

    auto camera = std::make_shared<CameraComponent>();
    AddComponent(camera);

    AddComponent(std::make_shared<TransformComponent>());

    // CameraControllerは、制御対象のCameraComponentをコンストラクタで受け取る
    AddComponent(std::make_shared<CameraController>(camera));
}

// --- ゲッターの実装 ---
// EntityのGetComponent<T>()機能を呼び出すだけ
std::shared_ptr<CameraComponent> CameraEntity::GetCameraComponent() const
{
    return GetComponent<CameraComponent>();
}
std::shared_ptr<TransformComponent> CameraEntity::GetTransformComponent() const
{
    return GetComponent<TransformComponent>();
}
std::shared_ptr<CameraController> CameraEntity::GetCameraController() const
{
    return GetComponent<CameraController>();
}