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

	// ’x‰„Á‹‚Ì‚½‚ßA’¼Úíœ‚¹‚¸‚É—\–ñ
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
    // íœ—\–ñ‚³‚ê‚½Entity‚ğœ‹
    if (!m_pendingRemoval.empty())
    {
        m_entities.erase(
            std::remove_if(m_entities.begin(), m_entities.end(),
                [this](const std::shared_ptr<Entity>& e)
                {
                    // find‚Ì‘ã‚í‚è‚É‚‘¬‚Ècount‚ğg—p
                    return m_pendingRemoval.count(e) > 0;
                }),
            m_entities.end());

        m_pendingRemoval.clear();
    }

    // ‘SEntity‚ÌXV
    for (auto& entity : m_entities)
    {
        if (entity && entity->IsActive())
        {
            entity->Update(deltaTime); // deltaTime ‚ğ“n‚·
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