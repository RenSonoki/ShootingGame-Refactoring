#pragma once
#include "ComponentBase.h"
#include "Quaternion.h" // ���������쐬����Quaternion�N���X
#include <DxLib.h>

class TransformComponent : public ComponentBase
{
public:
    TransformComponent();
    explicit TransformComponent(const VECTOR& pos);
    virtual ~TransformComponent() = default;

    void Update(float deltaTime) override;
    ComponentID GetID() const override;

    MATRIX GetWorldMatrix() const;

    const VECTOR& GetPosition() const;
    void SetPosition(const VECTOR& pos);

    const VECTOR& GetVelocity() const;
    void SetVelocity(const VECTOR& vel);

    // ��]���N�H�[�^�j�I���Œ��ڐݒ�E�擾
    const Quaternion& GetRotation() const;
    void SetRotation(const Quaternion& rot);
    // �I�C���[�p(���W�A��)�����]��ݒ�i�݊����̂��߁j
    void SetRotation(const VECTOR& eulerAngles);

    // Y������̉�]�iYaw�j�����݂̉�]�ɒǉ�����
    void AddYaw(float angle);
    // X������̉�]�iPitch�j�����݂̉�]�ɒǉ�����
    void AddPitch(float angle);

    const VECTOR& GetScale() const;
    void SetScale(const VECTOR& scale);

    VECTOR GetForward() const;
    VECTOR GetRight() const;
    VECTOR GetUp() const;

private:
    MATRIX GetRotationMatrix() const;

    VECTOR m_position;
    VECTOR m_velocity;
    Quaternion m_rotation; // �����\����Quaternion�ɕύX
    VECTOR m_scale;
};