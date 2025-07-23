#include "CameraSystem.h"
#include "Entity.h"
#include "CameraComponent.h"
#include <algorithm>

void CameraSystem::Register(const std::shared_ptr<Entity>& cameraEntity)
{
    if (!cameraEntity) return;

    auto camera = cameraEntity->GetComponent<CameraComponent>();
    if (camera)
    {
        // �d�����Ȃ����m�F
        auto it = std::find(m_cameras.begin(), m_cameras.end(), camera);
        if (it == m_cameras.end())
        {
            m_cameras.push_back(camera);
            // �ŏ��ɒǉ����ꂽ�J�������A�N�e�B�u�ɂ���
            if (m_activeCamera.expired())
            {
                m_activeCamera = camera;
            }
        }
    }
}

void CameraSystem::Unregister(const std::shared_ptr<Entity>& cameraEntity)
{
    if (!cameraEntity) return;
    auto camera = cameraEntity->GetComponent<CameraComponent>();
    if (camera)
    {
        // �y�C���_�z�����폜�ł͂Ȃ��A�폜�҂����X�g�ɒǉ�����
        m_pendingRemoval.push_back(camera);
    }
}

void CameraSystem::SetActiveCamera(const std::shared_ptr<CameraComponent>& camera)
{
    // �w�肳�ꂽ�J�������o�^�ς݂��m�F�inullptr���l���j
    if (camera) {
        auto it = std::find(m_cameras.begin(), m_cameras.end(), camera);
        if (it != m_cameras.end())
        {
            m_activeCamera = camera;
        }
    }
    else {
        m_activeCamera.reset();
    }
}

std::shared_ptr<CameraComponent> CameraSystem::GetActiveCamera() const
{
    return m_activeCamera.lock();
}

void CameraSystem::ApplyActiveCamera()
{
    // 1. �܂��A���S�ɍ폜�������s��
    ApplyPendingRemovals();

    // 2. �A�N�e�B�u�ȃJ�������擾���Đݒ��K�p
    if (auto active = m_activeCamera.lock())
    {
        // �y�C���_�z���\�b�h����Activate()�ɓ���
        active->Activate();
    }
}

void CameraSystem::Clear()
{
    m_cameras.clear();
    m_pendingRemoval.clear();
    m_activeCamera.reset();
}

// private:
void CameraSystem::ApplyPendingRemovals()
{
    if (m_pendingRemoval.empty()) return;

    // �폜�҂����X�g�ɂ���J�������A���C���̃��X�g���珜������
    m_cameras.erase(
        std::remove_if(m_cameras.begin(), m_cameras.end(),
            [this](const auto& cam) {
                return std::find(m_pendingRemoval.begin(), m_pendingRemoval.end(), cam) != m_pendingRemoval.end();
            }),
        m_cameras.end());

    m_pendingRemoval.clear();
}