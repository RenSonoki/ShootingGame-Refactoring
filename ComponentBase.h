#pragma once
#include "IComponent.h"

// �O���錾
class Entity;

// �R���|�[�l���g���ʊ��N���X(���C�t�T�C�N�����`)
class ComponentBase : public IComponent
{
    // NOTE: friend�w��͊댯�����ASetOwner��protected�ɂ��Ă��邽��
	//       ���L�҂݂̂��Ăяo���邽�ߖ��Ȃ�
    friend class Entity;

protected:
    Entity* m_owner = nullptr;
    bool m_active = true;

    void SetOwner(Entity* entity) override { m_owner = entity; }

public:
    virtual ~ComponentBase() = default;

    Entity* GetOwner() const override { return m_owner; }
    void SetActive(bool active) override { m_active = active; }
    bool IsActive() const override { return m_active; }

    // ---���C�t�T�C�N�����\�b�h�𓝈� ---

    // ����������
    virtual void Start() {}

    // �X�V����
    virtual void Update(float deltaTime) {}

    // �`�揈��
    virtual void Draw() {}
};