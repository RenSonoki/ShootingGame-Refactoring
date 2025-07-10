#pragma once

// �O���錾
class Entity;

// �R���|�[�l���g�̃C���^�[�t�F�[�X
class IComponent
{
public:
    virtual ~IComponent() = default;

	// NOTE: ���L�҂�m�邱�ƂŁAComponent�Ԃ̑��ݍ�p���\�ɂ���
    virtual void SetOwner(Entity* entity) = 0;
    virtual Entity* GetOwner() const = 0;

    virtual void SetActive(bool active) = 0;
    virtual bool IsActive() const = 0;
};