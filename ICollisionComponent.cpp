#include "ICollisionComponent.h"
#include "ColliderManager.h"
#include "Entity.h" // Entity�̊��S�Ȓ�`���K�v

ICollisionComponent::~ICollisionComponent()
{
    // �R���|�[�l���g���j�������ۂ�ColliderManager����o�^����������
    if (auto sharedThis = std::enable_shared_from_this<ICollisionComponent>::shared_from_this())
    {
        ColliderManager::GetInstance().Unregister(sharedThis);
    }
}

void ICollisionComponent::SetOnCollision(std::function<void(std::shared_ptr<Entity>)> callback)
{
    m_onCollision = std::move(callback);
}

void ICollisionComponent::TriggerCollision(std::shared_ptr<Entity> other) const
{
    if (m_onCollision)
    {
        m_onCollision(other);
    }
}

void ICollisionComponent::SetOwner(std::weak_ptr<Entity> owner)
{
    // �܂��A�e�N���X��SetOwner���Ăяo���āAm_owner��ݒ�
    ComponentBase::SetOwner(owner);

    // ���g��shared_ptr���擾���āAColliderManager�ɓo�^����
    // Entity��AddComponent��shared_ptr��Component�𐶐����Ă��邱�Ƃ��O��
    if (auto sharedThis = std::enable_shared_from_this<ICollisionComponent>::shared_from_this())
    {
        ColliderManager::GetInstance().Register(sharedThis);
    }
}