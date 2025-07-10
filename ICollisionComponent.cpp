#include "ICollisionComponent.h"
#include "ColliderManager.h"

ICollisionComponent::~ICollisionComponent()
{
	// コンポーネントが破棄される際にColliderManagerから登録を解除する
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
    LogicComponent::SetOwner(owner);  // ベースクラス処理も呼ぶ

	// 生成時に登録する

    ColliderManager::Instance().Register(shared_from_this());
}