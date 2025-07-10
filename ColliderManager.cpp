#include "ColliderManager.h"
#include <algorithm> // std::find �̂��߂ɒǉ�

ColliderManager& ColliderManager::Instance()
{
    static ColliderManager instance;
    return instance;
}

void ColliderManager::Register(const std::shared_ptr<ICollisionComponent>& collider)
{
    if (collider)
    {
        // �O�̂��߁A���ɒǉ�����Ă��Ȃ����`�F�b�N
        auto it = std::find(m_colliders.begin(), m_colliders.end(), collider);
        if (it == m_colliders.end())
        {
            m_colliders.push_back(collider);
        }
    }
}

// Unregister�͍폜�҂����X�g�ɒǉ����邾��
void ColliderManager::Unregister(const std::shared_ptr<ICollisionComponent>& collider)
{
    if (collider)
    {
        m_pendingRemoval.push_back(collider);
    }
}

void ColliderManager::CheckAllCollisions()
{
    // �܂��A�O��̃t���[���ŗ\�񂳂ꂽ�폜�����S�Ɏ��s����
    ApplyPendingRemovals();

    const size_t count = m_colliders.size();
    for (size_t i = 0; i < count; ++i)
    {
        auto& a = m_colliders[i];
        if (!a || !a->IsActive()) continue;

        for (size_t j = i + 1; j < count; ++j)
        {
            auto& b = m_colliders[j];
            if (!b || !b->IsActive()) continue;

            if (a->CheckCollision(*b))
            {
                a->TriggerCollision(b->GetOwner());
                b->TriggerCollision(a->GetOwner());
            }
        }
    }
}

void ColliderManager::Clear()
{
    m_colliders.clear();
    m_pendingRemoval.clear();
}

// �폜�������s���v���C�x�[�g�ȃw���p�[
void ColliderManager::ApplyPendingRemovals()
{
    if (m_pendingRemoval.empty()) return;

    m_colliders.erase(
        std::remove_if(m_colliders.begin(), m_colliders.end(),
            [this](const std::shared_ptr<ICollisionComponent>& c) {
                return std::find(m_pendingRemoval.begin(), m_pendingRemoval.end(), c) != m_pendingRemoval.end();
            }),
        m_colliders.end());

    m_pendingRemoval.clear();
}