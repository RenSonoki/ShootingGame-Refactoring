#include "CameraBuilder.h"
#include "CameraEntity.h"

// �K�v�ȃR���|�[�l���g�̃w�b�_�[���C���N���[�h
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "ThirdPersonCameraComponent.h" // �� CameraController�̑���ɂ�������C���N���[�h

CameraBuilder::CameraBuilder()
    : m_position({ 0.0f, 10.0f, -20.0f }) // �f�t�H���g�̏����ʒu
{
}

CameraBuilder& CameraBuilder::SetPosition(const VECTOR& pos)
{
    m_position = pos;
    return *this; // ���\�b�h�`�F�[���̂��ߎ��g�̎Q�Ƃ�Ԃ�
}

std::shared_ptr<CameraEntity> CameraBuilder::Build() const
{
    // 1. �܂��A�R���|�[�l���g�̓��ꕨ�ƂȂ�Entity�𐶐�
    auto cameraEntity = std::make_shared<CameraEntity>();

    // 2. Entity��AddComponent<T>�@�\���g���Ċe�R���|�[�l���g�𐶐��E�ǉ�

    // TransformComponent��ǉ����A�ʒu��ݒ�
    auto transform = cameraEntity->AddComponent<TransformComponent>();
    transform->SetPosition(m_position);

    // CameraComponent��ǉ��i�J�����Ƃ��Ă̊�{�I�ȋ@�\�j
    cameraEntity->AddComponent<CameraComponent>();

    // ThirdPersonCameraComponent��ǉ��i�O�l�̎��_�̃J�������䃍�W�b�N�j
    cameraEntity->AddComponent<ThirdPersonCameraComponent>();

    // 3. ���������G���e�B�e�B��Ԃ�
    return cameraEntity;
}