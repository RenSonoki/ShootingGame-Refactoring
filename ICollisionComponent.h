#pragma once
#include "ComponentBase.h"
#include "CollisionShapeType.h"
#include <functional>
#include <memory>
#include <DxLib.h> // VECTOR�̂���

// �O���錾
class Entity;

// �y�C���z���N���X�� ComponentBase �ɕύX
class ICollisionComponent : public ComponentBase, public std::enable_shared_from_this<ICollisionComponent>
{
public:
    virtual ~ICollisionComponent();

    // �y���P�āz�r�W�^�[�p�^�[����p�~���A���g�̌`��^�C�v��Ԃ��V���v���ȃ��\�b�h�ɂ���
    virtual CollisionShapeType GetShapeType() const = 0;

    // �����蔻��ɕK�v�ȁA�`��̒��S�ʒu��Ԃ�
    virtual VECTOR GetCenter() const = 0;

    // �Փ˃C�x���g�̃R�[���o�b�N��ݒ�
    void SetOnCollision(std::function<void(std::shared_ptr<Entity>)> callback);
    // �Փ˃C�x���g�𔭉΂�����
    void TriggerCollision(std::shared_ptr<Entity> other) const;

    // ComponentBase��SetOwner���I�[�o�[���C�h���āAColliderManager�ւ̓o�^���s��
    void SetOwner(std::weak_ptr<Entity> owner) override;

protected:
    // �R�[���o�b�N�֐�
    std::function<void(std::shared_ptr<Entity>)> m_onCollision;
};