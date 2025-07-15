#pragma once
#include "ComponentID.h"
#include <memory>

// �O���錾
class Entity;

// �S�ẴR���|�[�l���g���]���ׂ��C���^�[�t�F�[�X
class IComponent
{
public:
    virtual ~IComponent() = default;

    // --- ��{�@�\ ---
    // NOTE: Entity�N���X��AddComponent���\�b�h����Ăяo����邱�Ƃ�z��
    //       ���L�҂� std::weak_ptr �ň��S�ɐݒ�E�擾
    virtual void SetOwner(std::weak_ptr<Entity> owner) = 0;
    virtual std::shared_ptr<Entity> GetOwner() const = 0;

    virtual void SetActive(bool active) = 0;
    virtual bool IsActive() const = 0;

    // --- ���C�t�T�C�N�����\�b�h ---
    // NOTE: �f�t�H���g�̋�������������邱�ƂŁA�h���N���X�͕K�v�Ȃ��̂����I�[�o�[���C�h�B

    // Entity�ɒǉ�����A���������������Ɉ�x�����Ă΂��
    virtual void Start() {}

    // ���t���[���Ă΂��X�V����
    virtual void Update(float deltaTime) {}

    // ���t���[���Ă΂��`�揈��
    // NOTE: �`��͏�Ԃ�ύX���Ȃ��͂��Ȃ̂� const ��t���܂�
    virtual void Draw() const {}

    // --- �^��� ---
    // NOTE: �h���N���X�͕K�����g��ID��Ԃ��悤�ɋ���
    virtual ComponentID GetID() const = 0;
};