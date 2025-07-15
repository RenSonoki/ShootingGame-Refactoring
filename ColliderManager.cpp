#include "ColliderManager.h"
#include <algorithm>
#include <iterator>

ColliderManager& ColliderManager::Instance()
{
    static ColliderManager instance;
    return instance;
}

void ColliderManager::Init(float worldWidth, float worldDepth, float cellSize)
{
    m_worldWidth = worldWidth;
    m_worldDepth = worldDepth;
    m_cellSize = cellSize;
    m_gridCols = static_cast<int>(std::ceil(worldWidth / cellSize));
    Clear();
}

void ColliderManager::Register(const std::shared_ptr<ICollisionComponent>& collider)
{
    if (!collider) return;
    auto it = std::find(m_colliders.begin(), m_colliders.end(), collider);
    if (it == m_colliders.end())
    {
        m_colliders.push_back(collider);
    }
}

void ColliderManager::Unregister(const std::shared_ptr<ICollisionComponent>& collider)
{
    if (collider)
    {
        m_pendingRemoval.push_back(collider);
    }
}

void ColliderManager::RegisterCollisionCheck(CollisionPair pair, CollisionFunc func)
{
    m_collisionCheckers[pair] = func;
}


// �Q�[���̐��E����Ղ̖ڂ̂悤�ȁu�O���b�h�v�ŕ������A�e�R���C�_�[�����̈ʒu�ɉ������Z���ɓo�^�B
// �����蔻����s���ۂ́A�u�����Ɠ����Z���ɂ���R���C�_�[�v�������`�F�b�N�ΏہB
// ����ɂ��`�F�b�N�񐔂����I�ɍ팸
void ColliderManager::CheckAllCollisions()
{
    ApplyPendingRemovals();
    UpdateGrid();

    // �O���b�h�̊e�Z�����`�F�b�N
    for (const auto& gridCellPair : m_grid)
    {
        const auto& cell = gridCellPair.second;
        if (cell.size() < 2) continue;

        // �Z�����̃R���C�_�[���m�ő�������`�F�b�N
        for (size_t i = 0; i < cell.size(); ++i)
        {
            auto& a = cell[i];
            if (!a || !a->IsActive()) continue;

            for (size_t j = i + 1; j < cell.size(); ++j)
            {
                auto& b = cell[j];
                if (!b || !b->IsActive()) continue;

                // ���b�N�A�b�v�e�[�u�����画��֐�������
                CollisionPair pair(a->GetShapeType(), b->GetShapeType());
                auto it = m_collisionCheckers.find(pair);
                if (it != m_collisionCheckers.end())
                {
                    // ���������֐��ŏՓ˔�������s
                    if (it->second(*a, *b))
                    {
                        a->TriggerCollision(b->GetOwner());
                        b->TriggerCollision(a->GetOwner());
                    }
                }
            }
        }
    }
}

void ColliderManager::Clear()
{
    m_colliders.clear();
    m_pendingRemoval.clear();
    m_grid.clear();
}

void ColliderManager::ApplyPendingRemovals()
{
    if (m_pendingRemoval.empty()) return;
    m_colliders.erase(
        std::remove_if(m_colliders.begin(), m_colliders.end(),
            [this](const auto& c) {
                return std::find(m_pendingRemoval.begin(), m_pendingRemoval.end(), c) != m_pendingRemoval.end();
            }),
        m_colliders.end());
    m_pendingRemoval.clear();
}

void ColliderManager::UpdateGrid()
{
    m_grid.clear();
    for (const auto& collider : m_colliders)
    {
        if (collider && collider->IsActive())
        {
            int index = GetGridIndex(collider->GetCenter());
            m_grid[index].push_back(collider);
        }
    }
}

int ColliderManager::GetGridIndex(const VECTOR& position) const
{
    int x = static_cast<int>(position.x / m_cellSize);
    int z = static_cast<int>(position.z / m_cellSize);
    return x + z * m_gridCols;
}