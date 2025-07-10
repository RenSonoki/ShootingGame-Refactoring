#include "CameraSystem.h"
#include "Entity.h"
#include "CameraComponent.h"
#include <algorithm>
#include <DxLib.h>

void CameraSystem::Register(const std::shared_ptr<Entity>& cameraEntity)
{
    if (!cameraEntity) return;

    // Entity����CameraComponent���擾
    auto camera = cameraEntity->GetComponent<CameraComponent>();
    if (camera)
    {
        m_cameras.push_back(camera);

        // �ŏ��ɒǉ����ꂽ�J�������A�N�e�B�u�ɂ���
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

    // std::erase_if (C++20) ���g���Ƃ��Ȍ�
    std::erase(m_cameras, camera);

    if (m_activeCamera.lock() == camera)
    {
        m_activeCamera.reset();
    }
}

void CameraSystem::SetActiveCamera(const std::shared_ptr<CameraComponent>& camera)
{
    // �w�肳�ꂽ�J�������o�^�ς݂��m�F
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
        // �J�����R���|�[�l���g���g�ɁADxLib�ւ̓K�p�𖽗߂��邾��
        active->ApplyToDxLibCamera();
    }
}