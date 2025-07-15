#pragma once
#include "IComponent.h"

// �O���錾
class Entity;

// �R���|�[�l���g�����̂��߂̋��ʊ��N���X
// NOTE: IComponent�̊�{�I�ȃC���^�[�t�F�[�X������
class ComponentBase : public IComponent
{
protected:
    std::weak_ptr<Entity> m_owner;
    bool m_isActive = true;

public:
    virtual ~ComponentBase() = default;

    // --- ��{�@�\�̎��� ---
    void SetOwner(std::weak_ptr<Entity> owner) override { m_owner = owner; }
    std::shared_ptr<Entity> GetOwner() const override { return m_owner.lock(); }

    void SetActive(bool active) override { m_isActive = active; }
    bool IsActive() const override { return m_isActive; }

    // NOTE: Start, Update, Draw��IComponent�̃f�t�H���g���������̂܂܌p�����܂��B
    //       GetID()�́A���̃N���X���p�������̓I�ȃR���|�[�l���g��
    //       ���g��ID��Ԃ��ӔC�������߁A�����ł͎������܂���B
};