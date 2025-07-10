#pragma once

#include "Entity.h"
#include <memory>

// �O���錾
class CameraComponent;
class TransformComponent;
class CameraController;
class CameraSystem;

// �Q�[�����̃J�������\������A�R���|�[�l���g���v���Z�b�g���ꂽ�G���e�B�e�B
class CameraEntity : public Entity
{
public:
    CameraEntity();

    // �e�R���|�[�l���g�ւ̃A�N�Z�X�p�Q�b�^�[
    std::shared_ptr<CameraComponent> GetCameraComponent() const;
    std::shared_ptr<TransformComponent> GetTransformComponent() const;
    std::shared_ptr<CameraController> GetCameraController() const;

private:
    // �����o�[�Ƃ��ĕێ�����K�v�͂Ȃ��iEntity�̋@�\�Ŏ擾�ł��邽�߁j
};