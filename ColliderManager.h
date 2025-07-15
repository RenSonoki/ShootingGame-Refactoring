#pragma once
#include "ICollisionComponent.h"
#include "CollisionSystemTypes.h" // 作成した共有ヘッダ
#include <vector>
#include <memory>
#include <map>

class ColliderManager
{
public:
    static ColliderManager& Instance();

    void Init(float worldWidth, float worldDepth, float cellSize);

    void Register(const std::shared_ptr<ICollisionComponent>& collider);
    void Unregister(const std::shared_ptr<ICollisionComponent>& collider);
    void RegisterCollisionCheck(CollisionPair pair, CollisionFunc func);

    void CheckAllCollisions();
    void Clear();

private:
    // --- メンバー変数 ---
    // 全てのコライダーを保持するマスターリスト
    std::vector<std::shared_ptr<ICollisionComponent>> m_colliders;

    // 空間分割用のグリッド (キーはGridIndex, 値はそのセル内のコライダーリスト)
    std::map<int, std::vector<std::shared_ptr<ICollisionComponent>>> m_grid;

    // 衝突判定関数のルックアップテーブル
    std::map<CollisionPair, CollisionFunc> m_collisionCheckers;

    // 遅延削除用のリスト
    std::vector<std::shared_ptr<ICollisionComponent>> m_pendingRemoval;

    // グリッドのパラメータ
    float m_worldWidth;
    float m_worldDepth;
    float m_cellSize;
    int m_gridCols;

    // --- シングルトンのお作法 ---
    ColliderManager() = default;
    ~ColliderManager() = default;
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;

    // --- プライベートなヘルパー関数 ---
    void ApplyPendingRemovals();
    void UpdateGrid();
    int GetGridIndex(const VECTOR& position) const;
};