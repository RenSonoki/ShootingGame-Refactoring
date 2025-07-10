#pragma once

#include <memory>
#include <vector>

// �O���錾
class CameraComponent;
class Entity; // EntitySystem�Ƃ̘A�g�̂��߂ɒǉ�

// �����̃J�������Ǘ����A�A�N�e�B�u�ȃJ������DxLib�ɓK�p����V�X�e��
class CameraSystem
{
public:
    // Entity��n���āA��������CameraComponent�������ŒT��
    void Register(const std::shared_ptr<Entity>& cameraEntity);
    void Unregister(const std::shared_ptr<Entity>& cameraEntity);

    void SetActiveCamera(const std::shared_ptr<CameraComponent>& camera);
    std::shared_ptr<CameraComponent> GetActiveCamera() const;

    // ���t���[���A�A�N�e�B�u�J������DxLib�ɔ��f
    void ApplyActiveCamera();

private:
    // �Ǘ�����̂�CameraComponent�����ŗǂ�
    std::vector<std::shared_ptr<CameraComponent>> m_cameras;
    std::weak_ptr<CameraComponent> m_activeCamera;
};