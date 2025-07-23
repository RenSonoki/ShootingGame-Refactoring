#pragma once
#include <vector>
#include <memory>
#include <string>

class Entity; // 前方宣言

// シーンに存在する全ての「ゲームワールドの」エンティティのライフサイクルを管理するクラス
class EntitySystem
{
public:
    EntitySystem() = default;
    ~EntitySystem() = default;

    EntitySystem(const EntitySystem&) = delete;
    EntitySystem& operator=(const EntitySystem&) = delete;

    // ★ 修正点: 構築済みのエンティティを受け取るようにシグネチャを変更
    void AddEntity(std::shared_ptr<Entity> entity);
    void RemoveEntity(std::shared_ptr<Entity> entity);
    const std::vector<std::shared_ptr<Entity>>& GetEntities() const;

    size_t GetEntityCount() const;

    void StartAll();
    void UpdateAll(float deltaTime);
    void DrawAll() const; // ★ const を追加
    void Clear();

private:
    void ApplyPendingActions();

    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<Entity>> m_pendingAdd;
    // ★ 改善案: 削除対象はポインタで十分
    std::vector<Entity*> m_pendingRemoval;

    bool m_isUpdating = false;
};