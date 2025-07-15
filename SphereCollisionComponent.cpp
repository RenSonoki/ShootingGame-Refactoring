#include "SphereCollisionComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <algorithm>
#include <cassert>

SphereCollisionComponent::SphereCollisionComponent(float radius)
    : m_baseRadius(radius)
{
}

void SphereCollisionComponent::Start()
{
    // �I�[�i�[����TransformComponent���擾���Aweak_ptr�ŕێ�
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(!m_transform.expired() && "SphereCollisionComponent requires a TransformComponent.");
}

VECTOR SphereCollisionComponent::GetCenter() const
{
    if (auto transform = m_transform.lock())
    {
        return transform->GetPosition();
    }
    // Transform��������Ȃ��ꍇ�́A���g�̃I�[�i�[�̈ʒu��Ԃ��Ȃǂ̃t�H�[���o�b�N
    if (auto owner = GetOwner())
    {
        // GetOwner���Ԃ��̂�Entity��shared_ptr�Ȃ̂ŁA�����Transform���擾
        if (auto ownerTransform = owner->GetComponent<TransformComponent>())
        {
            return ownerTransform->GetPosition();
        }
    }
    return VGet(0, 0, 0);
}

float SphereCollisionComponent::GetRadius() const
{
    if (auto transform = m_transform.lock())
    {
        VECTOR scale = transform->GetScale();
        float maxScale = (std::max)({ scale.x, scale.y, scale.z }); // C++11�ȍ~�̏�����
        return m_baseRadius * maxScale;
    }
    return m_baseRadius;
}

void SphereCollisionComponent::SetBaseRadius(float radius)
{
    m_baseRadius = radius;
}