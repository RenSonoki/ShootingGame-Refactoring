#include "EnemyPrototype.h"
#include "EnemyEntity.h" // �ŐV��EnemyEntity���C���N���[�h

EnemyPrototype::EnemyPrototype() = default;

void EnemyPrototype::SetModelPath(const std::wstring& path) { m_modelPath = path; }
void EnemyPrototype::SetSpeed(float speed) { m_speed = speed; }
void EnemyPrototype::SetCollisionRadius(float radius) { m_radius = radius; }
void EnemyPrototype::SetScore(int score) { m_score = score; }
void EnemyPrototype::SetOnDestroyCallback(std::function<void(int)> callback) { m_onDestroyCallback = std::move(callback); }

std::shared_ptr<EnemyEntity> EnemyPrototype::Clone(const VECTOR& spawnPos, std::shared_ptr<TransformComponent> targetTransform) const
{
    // 1. �ŐV�ł̃R���X�g���N�^��EnemyEntity�𐶐�
    auto enemy = std::make_shared<EnemyEntity>(
        spawnPos,
        m_modelPath,
        m_speed,
        m_radius
    );

    // 2. �v���g�^�C�v�����ݒ�l�ŁA���������G���\������
    enemy->SetTarget(targetTransform);
    enemy->SetScore(m_score);

    if (m_onDestroyCallback)
    {
        enemy->SetOnDestroyCallback(m_onDestroyCallback);
    }

    return enemy;
}