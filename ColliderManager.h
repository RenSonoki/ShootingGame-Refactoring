#pragma once

#include "ICollisionComponent.h"
#include <vector>
#include <memory>

// シングルトンとして、登録された全てのコライダーを管理するクラス
class ColliderManager
{
public:
    static ColliderManager& Instance();

    // AddColliderを削除し、登録/解除に統一
    void Register(const std::shared_ptr<ICollisionComponent>& collider);
    void Unregister(const std::shared_ptr<ICollisionComponent>& collider);

    void CheckAllCollisions();
    void Clear();

private:
    std::vector<std::shared_ptr<ICollisionComponent>> m_colliders;

    // 遅延削除のための「削除待ちリスト」を追加
    std::vector<std::shared_ptr<ICollisionComponent>> m_pendingRemoval;

    ColliderManager() = default;
    ~ColliderManager() = default;
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;

    // 実際の削除処理を行うヘルパー関数
    void ApplyPendingRemovals();
};