#pragma once

#include <memory>
#include <vector>

// 前方宣言
class CameraComponent;
class Entity; // EntitySystemとの連携のために追加

// 複数のカメラを管理し、アクティブなカメラをDxLibに適用するシステム
class CameraSystem
{
public:
    // Entityを渡して、そこからCameraComponentを自動で探す
    void Register(const std::shared_ptr<Entity>& cameraEntity);
    void Unregister(const std::shared_ptr<Entity>& cameraEntity);

    void SetActiveCamera(const std::shared_ptr<CameraComponent>& camera);
    std::shared_ptr<CameraComponent> GetActiveCamera() const;

    // 毎フレーム、アクティブカメラをDxLibに反映
    void ApplyActiveCamera();

private:
    // 管理するのはCameraComponentだけで良い
    std::vector<std::shared_ptr<CameraComponent>> m_cameras;
    std::weak_ptr<CameraComponent> m_activeCamera;
};