#pragma once

#include <vector>
#include <memory>
#include <unordered_set> // vectorの代わりにunordered_setを使用
#include "Entity.h"

// シーンに存在する全てのエンティティのライフサイクル（生成、更新、描画、破棄）を管理するクラス
class EntitySystem
{
public:
    EntitySystem() = default;
    ~EntitySystem() = default;

    void AddEntity(std::shared_ptr<Entity> entity);
    void RemoveEntity(std::shared_ptr<Entity> entity);

    void Start();
    void Update(float deltaTime);
    void Draw();
    void Clear();

    const std::vector<std::shared_ptr<Entity>>& GetEntities() const;
    
private:
    std::vector<std::shared_ptr<Entity>> m_entities;

    // 削除待ちリストをunordered_setに変更
    std::unordered_set<std::shared_ptr<Entity>> m_pendingRemoval;

    bool m_started = false;
};