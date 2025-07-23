#include "CameraEntity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "ThirdPersonCameraComponent.h" // �� CameraController�̑���ɂ�������C���N���[�h

CameraEntity::CameraEntity()
{
    SetTag(L"Camera");
}

// �Q�b�^�[�̎���
std::shared_ptr<CameraComponent> CameraEntity::GetCameraComponent() const { return GetComponent<CameraComponent>(); }
std::shared_ptr<TransformComponent> CameraEntity::GetTransformComponent() const { return GetComponent<TransformComponent>(); }

// �� �C���_: �V����TPS�J�����R���|�[�l���g��Ԃ��悤�Ɏ���
std::shared_ptr<ThirdPersonCameraComponent> CameraEntity::GetThirdPersonCamera() const
{
    return GetComponent<ThirdPersonCameraComponent>();
}