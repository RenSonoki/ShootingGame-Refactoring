#include "EntitySystem.h"
#include <algorithm>

void EntitySystem::AddEntity(std::shared_ptr<Entity> entity)
{
    if (!entity) return;
    m_entities.push_back(entity);

    if (m_started)
    {
        entity->Start();
    }
}

void EntitySystem::RemoveEntity(std::shared_ptr<Entity> entity)
{
    if (!entity) return;

	// 遅延消去のため、直接削除せずに予約
    m_pendingRemoval.insert(entity);
}

void EntitySystem::Start()
{
    for (auto& entity : m_entities)
    {
        if (entity)
        {
            entity->Start();
        }
    }
    m_started = true;
}

void EntitySystem::Update(float deltaTime)
{
    // 削除予約されたEntityを除去
    if (!m_pendingRemoval.empty())
    {
        m_entities.erase(
            std::remove_if(m_entities.begin(), m_entities.end(),
                [this](const std::shared_ptr<Entity>& e)
                {
                    // findの代わりに高速なcountを使用
                    return m_pendingRemoval.count(e) > 0;
                }),
            m_entities.end());

        m_pendingRemoval.clear();
    }

    // 全Entityの更新
    for (auto& entity : m_entities)
    {
        if (entity && entity->IsActive())
        {
            entity->Update(deltaTime); // deltaTime を渡す
        }
    }
}

void EntitySystem::Draw()
{
    for (auto& entity : m_entities)
    {
        if (entity && entity->IsActive())
        {
            entity->Draw();
        }
    }
}

const std::vector<std::shared_ptr<Entity>>& EntitySystem::GetEntities() const
{
    return m_entities;
}

void EntitySystem::Clear()
{
    m_entities.clear();
    m_pendingRemoval.clear();
    m_started = false;
}