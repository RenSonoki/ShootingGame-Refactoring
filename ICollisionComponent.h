#pragma once

#include "LogicComponent.h"
#include "DxLib.h"
#include <functional>
#include <memory>
#include "CollisionShapeType.h"

// �O���錾
class Entity;
class SphereCollisionComponent;
class BoxCollisionComponent;
class CapsuleCollisionComponent;

// �Փ˃C���^�[�t�F�[�X + �o�^����
class ICollisionComponent : public LogicComponent, public std::enable_shared_from_this<ICollisionComponent>
{
public:
    virtual ~ICollisionComponent();

	// �r�W�^�[�p�^�[����p���ďՓˌ`�������
	// NOTE: ����ɂ��A���M�⑼�̏Փˌ`��𒼐ڎQ�Ƃ��邱�ƂȂ��A�Փ˔�����s�����Ƃ��ł���
    virtual bool CheckCollision(const ICollisionComponent& other) const = 0;
    virtual bool Accept(const ICollisionComponent& other) const = 0;
    virtual bool Visit(const SphereCollisionComponent& sphere) const = 0;
    virtual bool Visit(const BoxCollisionComponent& box) const = 0;
    virtual bool Visit(const CapsuleCollisionComponent& capsule) const = 0;

    virtual VECTOR GetCenter() const = 0;
    virtual CollisionShapeType GetShapeType() const { return CollisionShapeType::Unknown; }

    // �Փ˃C�x���g
    void SetOnCollision(std::function<void(Entity*)> callback);
    void TriggerCollision(Entity* other) const;

    // ���L�ҁi�o�^���ɂ��g�p�j
    void SetOwner(Entity* owner) override;
    Entity* GetOwner() const { return m_owner; }

    // NOTE: �������ɓo�^���s���A�f�X�g���N�^�œo�^����������
	//       �������邱�ƂŁA�o�^�̂��Y�������̂��Y��ɂ�郁�������[�N��h��

protected:
    Entity* m_owner = nullptr;
    std::function<void(Entity*)> m_onCollision;
};