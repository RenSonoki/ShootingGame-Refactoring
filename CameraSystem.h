#pragma once
#include <memory>
#include <vector>
#include <string>

// �O���錾
class CameraComponent;
class Entity;

// �����̃J�������Ǘ����A�A�N�e�B�u�ȃJ������DxLib�ɓK�p����V�X�e��
class CameraSystem
{
public:
    CameraSystem() = default;
    ~CameraSystem() = default;

    // ���̃V�X�e���̓R�s�[�ł��Ȃ�
    CameraSystem(const CameraSystem&) = delete;
    CameraSystem& operator=(const CameraSystem&) = delete;

    void Register(const std::shared_ptr<Entity>& cameraEntity);
    void Unregister(const std::shared_ptr<Entity>& cameraEntity);

    void SetActiveCamera(const std::shared_ptr<CameraComponent>& camera);
    std::shared_ptr<CameraComponent> GetActiveCamera() const;

    // ���t���[���A�A�N�e�B�u�J������DxLib�ɔ��f�i�X�V���������˂�j
    void ApplyActiveCamera();

    void Clear();

private:
    // �x���폜�����s����w���p�[�֐�
    void ApplyPendingRemovals();

    // CameraComponent�ւ̃|�C���^�𒼐ڊǗ�����
    std::vector<std::shared_ptr<CameraComponent>> m_cameras;
    std::weak_ptr<CameraComponent> m_activeCamera;

    // �x���폜�p�̃��X�g��ǉ�
    std::vector<std::shared_ptr<CameraComponent>> m_pendingRemoval;
};