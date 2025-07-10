#pragma once

#include "LogicComponent.h"
#include <memory>

// �O���錾
class TransformComponent; 

// �v���C���[�̈ړ����͂��������ATransform�̑��x�𐧌䂷��R���|�[�l���g
class PlayerControllerComponent : public LogicComponent
{
public:
    PlayerControllerComponent();

	// ���C�t�T�C�N�����\�b�h
    void Start() override;
    void Update(float deltaTime) override;

    // �ړ����x�̐ݒ�
    void SetMoveSpeed(float speed);
    float GetMoveSpeed() const;

private:
    std::shared_ptr<TransformComponent> m_transform;
    float m_moveSpeed = 5.0f; // ���x�Ȃ̂ŁA�����傫�߂̒l�ɕύX
};