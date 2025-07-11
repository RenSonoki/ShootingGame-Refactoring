#pragma once

#include "LogicComponent.h"
#include <memory>
#include <DxLib.h>

// �O���錾
class TransformComponent;
class CameraComponent;

// �^�[�Q�b�g��Ǐ]����O�l�̎��_�J�����̃��W�b�N
// NOTE: ���̃N���X�́A�J�����̈ʒu���^�[�Q�b�g��TransformComponent�Ɋ�Â��čX�V���܂��B
class ThirdPersonCameraComponent : public LogicComponent
{
public:
    // �Ǐ]�Ώۂ�TransformComponent���ア�|�C���^�Ŏ󂯎��
    // NOTE: �z�Q�Ƃ������邽��
    explicit ThirdPersonCameraComponent(std::weak_ptr<TransformComponent> targetTransform);

    // ���C�t�T�C�N�����\�b�h
    void Start() override;
    void Update(float deltaTime) override;

    // �J�����̋����⍂����ݒ肷��Z�b�^�[
    void SetOffset(const VECTOR& offset);

private:
    // �ˑ��R���|�[�l���g�ւ̃|�C���^
    std::shared_ptr<CameraComponent> m_camera;

    // �Ǐ]�Ώۂւ̃|�C���^
    std::weak_ptr<TransformComponent> m_targetTransform;

    // �^�[�Q�b�g����̑��ΓI�ȃJ�����̈ʒu
    VECTOR m_offset;
};