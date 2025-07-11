#pragma once

#include "LogicComponent.h"
#include "DxLib.h"

// ��ԏ��i�ʒu�E��]�E���x�j���Ǘ�����R���|�[�l���g
// NOTE: ��K�͂ȊJ���ɂȂ����ꍇ�́A�ʒu���]�̃f�[�^�Ɖ��Z�����𕪗�����
class TransformComponent : public LogicComponent
{
public:
    TransformComponent();
	explicit TransformComponent(const VECTOR& pos); // explicit��p���ăR���X�g���N�^�𖾎��I�ɒ�`

    // ���N���X�ɍ��킹�� override
    // NOTE: �����̑��x���g���Ď����̈ʒu���X�V���鎩�Ȋ���
    void Update(float deltaTime) override;

    // �ʒu
    const VECTOR& GetPosition() const;
    void SetPosition(const VECTOR& pos);

    // ���x
    const VECTOR& GetVelocity() const;
    void SetVelocity(const VECTOR& vel);

    // ��]�iYaw, Pitch, Roll�j
    const VECTOR& GetRotation() const;
    void SetRotation(const VECTOR& rot);

    // �X�P�[��
    const VECTOR& GetScale() const;
    void SetScale(const VECTOR& scale);

    // �O���x�N�g��
    VECTOR GetForward() const;

private:
    VECTOR m_position;
    VECTOR m_velocity;
    VECTOR m_rotation; // x:Pitch, y:Yaw, z:Roll
    VECTOR m_scale;
};