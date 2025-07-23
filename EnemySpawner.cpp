#include "EnemySpawner.h"
#include "EnemyEntity.h"
#include "EntitySystem.h"
#include "EnemyPrototype.h"
#include "TransformComponent.h"
#include "Random.h"
#include <DxLib.h> // DX_PI_F�̂���
#include <cassert>

EnemySpawner::EnemySpawner(
    EntitySystem* entitySystem,
    std::shared_ptr<EnemyPrototype> prototype,
    std::weak_ptr<TransformComponent> playerTransform)
    // �����o�[�ϐ���������
    : m_entitySystem(entitySystem)
    , m_prototype(prototype)
    , m_playerTransform(playerTransform)
    , m_spawnInterval(3.0f) // �f�t�H���g�̏o���Ԋu
    , m_spawnDistance(60.0f) // �f�t�H���g�̏o������
    , m_timer(0.0f)
{
    // �ˑ��֌W���������n����Ă��邩�f�o�b�O���Ƀ`�F�b�N
    assert(m_entitySystem != nullptr && "EnemySpawner requires an EntitySystem.");
    assert(m_prototype != nullptr && "EnemySpawner requires an EnemyPrototype.");
}

void EnemySpawner::Update(float deltaTime)
{
    m_timer += deltaTime;
    if (m_timer >= m_spawnInterval)
    {
        m_timer -= m_spawnInterval; // �^�C�}�[�����Z�b�g
        Spawn();
    }
}

void EnemySpawner::SetSpawnInterval(float seconds) { m_spawnInterval = seconds; }
void EnemySpawner::SetSpawnDistance(float distance) { m_spawnDistance = distance; }

// private
void EnemySpawner::Spawn()
{
    // �v���C���[��Transform�����S�Ɏ擾
    auto playerTr = m_playerTransform.lock();
    if (!playerTr) return; // �v���C���[�����Ȃ��ꍇ�͉������Ȃ�

    // PlayScene�ɂ��������W�b�N�����̂܂܈ڐA
    float angle = Random::GetInstance().GetFloat(0.f, DX_PI_F * 2.0f);
    VECTOR offset = VGet(sinf(angle) * m_spawnDistance, 0, cosf(angle) * m_spawnDistance);
    VECTOR spawnPos = VAdd(playerTr->GetPosition(), offset);

    // �v���g�^�C�v����G�𕡐����AEntitySystem�ɒǉ�
    auto enemy = m_prototype->Clone(spawnPos, playerTr);
    m_entitySystem->AddEntity(enemy);
}