#include "CapsuleCollisionComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <algorithm>
#include <cassert>

CapsuleCollisionComponent::CapsuleCollisionComponent(float radius, float height)
    : m_baseRadius(radius), m_baseHeight(height)
{
}

void CapsuleCollisionComponent::Start()
{
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(!m_transform.expired() && "CapsuleCollisionComponent requires a TransformComponent.");
}

VECTOR CapsuleCollisionComponent::GetCenter() const
{
    if (auto transform = m_transform.lock())
    {
        return transform->GetPosition();
    }
    return VGet(0, 0, 0);
}

float CapsuleCollisionComponent::GetRadius() const
{
    if (auto transform = m_transform.lock())
    {
        const auto& scale = transform->GetScale();
        return m_baseRadius * (std::max)({ scale.x, scale.y, scale.z });
    }
    return m_baseRadius;
}

float CapsuleCollisionComponent::GetHeight() const
{
    if (auto transform = m_transform.lock())
    {
        return m_baseHeight * transform->GetScale().y;
    }
    return m_baseHeight;
}

void CapsuleCollisionComponent::SetBaseRadius(float radius) { m_baseRadius = radius; }
void CapsuleCollisionComponent::SetBaseHeight(float height) { m_baseHeight = height; }

// �y�C���_�z��]�𐳂������f����
std::pair<VECTOR, VECTOR> CapsuleCollisionComponent::GetWorldLineSegment() const
{
    if (auto transform = m_transform.lock())
    {
        // 1. �J�v�Z���̒��S�����A�܂����[�J����ԂŒ�`���� (Y���ɉ���)
        const float halfHeight = m_baseHeight / 2.0f;
        const VECTOR localStart = VGet(0.0f, -halfHeight, 0.0f);
        const VECTOR localEnd = VGet(0.0f, halfHeight, 0.0f);

        // 2. �I�u�W�F�N�g�̃��[���h�s����擾
        const MATRIX worldMat = transform->GetWorldMatrix();

        // 3. ���[�J���̎n�_�ƏI�_�����[���h�s��ŕϊ����A���[���h���W�̐����𓾂�
        const VECTOR worldStart = VTransform(localStart, worldMat);
        const VECTOR worldEnd = VTransform(localEnd, worldMat);

        return { worldStart, worldEnd };
    }

    // Transform���Ȃ���΁A���_�ɂ�������Ƃ��ĕԂ�
    return { VGet(0,0,0), VGet(0,0,0) };
}