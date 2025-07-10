#include "CameraEntity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "CameraController.h"

CameraEntity::CameraEntity()
{
    // --- �R���|�[�l���g�𐶐����A�����ǉ����邾�� ---
    // �ˑ��֌W�̉����́A�e�R���|�[�l���g��Start()�Ŏ����I�ɍs��

    auto camera = std::make_shared<CameraComponent>();
    AddComponent(camera);

    AddComponent(std::make_shared<TransformComponent>());

    // CameraController�́A����Ώۂ�CameraComponent���R���X�g���N�^�Ŏ󂯎��
    AddComponent(std::make_shared<CameraController>(camera));
}

// --- �Q�b�^�[�̎��� ---
// Entity��GetComponent<T>()�@�\���Ăяo������
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