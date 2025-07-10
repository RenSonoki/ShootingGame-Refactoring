#include "CameraSystem.h"
#include "Entity.h"
#include "CameraComponent.h"
#include <algorithm>
#include <DxLib.h>

void CameraSystem::Register(const std::shared_ptr<Entity>& cameraEntity)
{
    if (!cameraEntity) return;

    // EntityからCameraComponentを取得
    auto camera = cameraEntity->GetComponent<CameraComponent>();
    if (camera)
    {
        m_cameras.push_back(camera);

        // 最初に追加されたカメラをアクティブにする
        if (m_activeCamera.expired())
        {
            m_activeCamera = camera;
        }
    }
}

void CameraSystem::Unregister(const std::shared_ptr<Entity>& cameraEntity)
{
    if (!cameraEntity) return;
    auto camera = cameraEntity->GetComponent<CameraComponent>();
    if (!camera) return;

    // std::erase_if (C++20) を使うとより簡潔
    std::erase(m_cameras, camera);

    if (m_activeCamera.lock() == camera)
    {
        m_activeCamera.reset();
    }
}

void CameraSystem::SetActiveCamera(const std::shared_ptr<CameraComponent>& camera)
{
    // 指定されたカメラが登録済みか確認
    auto it = std::find(m_cameras.begin(), m_cameras.end(), camera);
    if (it != m_cameras.end())
    {
        m_activeCamera = camera;
    }
}

std::shared_ptr<CameraComponent> CameraSystem::GetActiveCamera() const
{
    return m_activeCamera.lock();
}

void CameraSystem::ApplyActiveCamera()
{
    if (auto active = m_activeCamera.lock())
    {
        // カメラコンポーネント自身に、DxLibへの適用を命令するだけ
        active->ApplyToDxLibCamera();
    }
}