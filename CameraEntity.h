#pragma once
#include "Entity.h"
#include <memory>

// �O���錾
class CameraComponent;
class TransformComponent;
class ThirdPersonCameraComponent; // �� CameraController�̑���ɂ������O���錾

class CameraEntity : public Entity
{
public:
    CameraEntity();

    // �Q�b�^�[
    std::shared_ptr<CameraComponent> GetCameraComponent() const;
    std::shared_ptr<TransformComponent> GetTransformComponent() const;
    // �� �C���_: �Â�CameraController�ւ̃Q�b�^�[���C��
    std::shared_ptr<ThirdPersonCameraComponent> GetThirdPersonCamera() const;
};