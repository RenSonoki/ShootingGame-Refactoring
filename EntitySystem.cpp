#include "EntitySystem.h"
#include "Entity.h"
#include <algorithm>
#include <unordered_set>

// �� �C���_: �\�z�ς݂̃G���e�B�e�B���󂯎��
void EntitySystem::AddEntity(std::shared_ptr<Entity> entity)
{
    if (entity)
    {
        // �X�V���[�v���Ȃ�A��Œǉ����邽�߂ɃL���[�ɓ����
        if (m_isUpdating)
        {
            m_pendingAdd.push_back(entity);
        }
        else // �X�V���łȂ���Α����ɒǉ����AStart���Ă�
        {
            m_entities.push_back(entity);
            entity->Start(); // �� �d�v: ������Start���Ă�
        }
    }
}

void EntitySystem::RemoveEntity(std::shared_ptr<Entity> entity)
{
    if (entity)
    {
        // �폜�L���[�ɂ͐��̃|�C���^�����Ă���
        m_pendingRemoval.push_back(entity.get());
    }
}

size_t EntitySystem::GetEntityCount() const
{
    return m_entities.size();
}

const std::vector<std::shared_ptr<Entity>>& EntitySystem::GetEntities() const
{
    return m_entities;
}

void EntitySystem::StartAll()
{
    for (auto& e : m_entities)
    {
        if (e && e->IsActive())
        {
            e->Start();
        }
    }
}

void EntitySystem::UpdateAll(float deltaTime)
{
    m_isUpdating = true;
    for (auto& entity : m_entities)
    {
        if (entity && entity->IsActive())
        {
            entity->Update(deltaTime);
        }
    }
    m_isUpdating = false;

    ApplyPendingActions();
}

void EntitySystem::DrawAll() const
{
    for (const auto& entity : m_entities)
    {
        if (entity && entity->IsActive())
        {
            entity->Draw();
        }
    }
}

void EntitySystem::Clear()
{
    m_entities.clear();
    m_pendingAdd.clear();
    m_pendingRemoval.clear();
}


void EntitySystem::ApplyPendingActions()
{
    // --- �폜�����i�������I�ȕ��@�ɏC���j ---
    if (!m_pendingRemoval.empty())
    {
        // �폜�Ώۂ̃|�C���^�����������ł���Z�b�g�ɓ����
        const std::unordered_set<Entity*> removalSet(m_pendingRemoval.begin(), m_pendingRemoval.end());

        // C++20�� std::erase_if ���g��
        std::erase_if(m_entities, [&removalSet](const auto& entity) {
            return removalSet.count(entity.get()) > 0;
            });

        m_pendingRemoval.clear();
    }

    // --- �ǉ����� ---
    if (!m_pendingAdd.empty())
    {
        // �\�񂳂�Ă����G���e�B�e�B���܂Ƃ߂Ēǉ�
        for (const auto& toAdd : m_pendingAdd)
        {
            m_entities.push_back(toAdd);
            // �� �d�v: �ǉ������G���e�B�e�B��Start�������ɌĂяo��
            if (toAdd)
            {
                toAdd->Start();
            }
        }
        m_pendingAdd.clear();
    }
}