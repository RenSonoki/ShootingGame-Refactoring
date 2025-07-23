#include "EnemyPrototype.h"
#include "EnemyBuilder.h"
#include "EnemyEntity.h"
#include "TransformComponent.h"
#include <utility>

EnemyPrototype::EnemyPrototype()
    : m_modelPath(L""), m_speed(5.0f), m_radius(1.5f), m_score(100)
{
}

void EnemyPrototype::SetModelPath(const std::wstring& path) { m_modelPath = path; }
void EnemyPrototype::SetSpeed(float speed) { m_speed = speed; }
void EnemyPrototype::SetCollisionRadius(float radius) { m_radius = radius; }
void EnemyPrototype::SetScore(int score) { m_score = score; }
void EnemyPrototype::SetOnDestroyCallback(std::function<void(int)> callback) { m_onDestroyCallback = std::move(callback); }

std::shared_ptr<EnemyEntity> EnemyPrototype::Clone(const VECTOR& spawnPos, std::weak_ptr<TransformComponent> targetTransform) const
{
    EnemyBuilder builder;

    // �� Build()������shared_ptr��Ԃ��̂ŁA���̂܂܎󂯎��
    auto enemy = builder.SetPosition(spawnPos)
        .SetModel(m_modelPath)
        .SetSpeed(m_speed)
        .SetCollisionRadius(m_radius)
        .SetScore(m_score)
        .Build();

    // �\�z���ꂽEnemyEntity�̃C���X�^���X�ɁA�ǉ��̐ݒ���s��
    if (auto target = targetTransform.lock())
    {
        enemy->SetTarget(target);
    }

    if (m_onDestroyCallback)
    {
        enemy->SetOnDestroyCallback(m_onDestroyCallback);
    }

    return enemy;
}