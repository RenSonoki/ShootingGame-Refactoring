#include "ICollisionComponent.h"
#include "ColliderManager.h"

ICollisionComponent::~ICollisionComponent()
{
	// �R���|�[�l���g���j�������ۂ�ColliderManager����o�^����������
    ColliderManager::Instance().Unregister(shared_from_this());
}

void ICollisionComponent::SetOnCollision(std::function<void(Entity*)> callback)
{
    m_onCollision = std::move(callback);
}

void ICollisionComponent::TriggerCollision(Entity* other) const
{
    if (m_onCollision) m_onCollision(other);
}

void ICollisionComponent::SetOwner(Entity* owner)
{
    m_owner = owner;
    LogicComponent::SetOwner(owner);  // �x�[�X�N���X�������Ă�

	// �������ɓo�^����

    ColliderManager::Instance().Register(shared_from_this());
}