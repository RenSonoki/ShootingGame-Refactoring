#pragma once

#include "LogicComponent.h"
#include <memory>
#include <DxLib.h>

// �O���錾
class CameraComponent;
class TransformComponent;

// �J�������[�h�̎�ނ̗񋓌^
enum class CameraMode
{
    ThirdPerson,
    FirstPerson,
    Free // ���̃R���|�[�l���g�ł͐��䂵�Ȃ����[�h
};

// �J�����̒Ǐ]�⃂�[�h�ؑւȂǁA���G�ȃ��W�b�N��S���R���|�[�l���g
class CameraController : public LogicComponent
{
public:
    // ����Ώۂ�CameraComponent���R���X�g���N�^�Ŏ󂯎��
    explicit CameraController(std::shared_ptr<CameraComponent> camera);

    // LogicComponent�̏������z�֐����I�[�o�[���C�h
    void Update(float deltaTime) override;

    // �Ǐ]����^�[�Q�b�g�i�v���C���[�Ȃǁj��ݒ�
    void SetTarget(std::shared_ptr<TransformComponent> target);

    // �J�������[�h�̐؂�ւ�
    void SetMode(CameraMode mode);
    CameraMode GetMode() const;

    // TPS���[�h�ł̃^�[�Q�b�g����̑��Έʒu��ݒ�
    void SetOffset(const VECTOR& offset);

    // �J�����Ǐ]�̊��炩����ݒ�
    void SetLerpSpeed(float speed);

private:
    std::shared_ptr<CameraComponent> m_camera;
    std::shared_ptr<TransformComponent> m_target;

    CameraMode m_mode = CameraMode::ThirdPerson;
    VECTOR m_offset = VGet(0.0f, 5.0f, -15.0f); // �f�t�H���g��TPS�I�t�Z�b�g
    float m_lerpSpeed = 10.0f; // �Ǐ]�̋����i�傫���قǑ����Ǐ]�j

    // ���`��Ԃ��s���w���p�[�֐�
    static VECTOR Lerp(const VECTOR& from, const VECTOR& to, float t);
};