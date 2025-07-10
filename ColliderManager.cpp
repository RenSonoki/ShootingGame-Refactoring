#include "ColliderManager.h"
#include <algorithm> // std::find のために追加

ColliderManager& ColliderManager::Instance()
{
    static ColliderManager instance;
    return instance;
}

void ColliderManager::Register(const std::shared_ptr<ICollisionComponent>& collider)
{
    if (collider)
    {
        // 念のため、既に追加されていないかチェック
        auto it = std::find(m_colliders.begin(), m_colliders.end(), collider);
        if (it == m_colliders.end())
        {
            m_colliders.push_back(collider);
        }
    }
}

// Unregisterは削除待ちリストに追加するだけ
void ColliderManager::Unregister(const std::shared_ptr<ICollisionComponent>& collider)
{
    if (collider)
    {
        m_pendingRemoval.push_back(collider);
    }
}

void ColliderManager::CheckAllCollisions()
{
    // まず、前回のフレームで予約された削除を安全に実行する
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

// 削除処理を行うプライベートなヘルパー
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