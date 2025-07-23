#include "EnemyBuilder.h"
#include "EnemyEntity.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include "HomingMoveComponent.h"
#include "SphereCollisionComponent.h"
#include "HealthComponent.h"

EnemyBuilder::EnemyBuilder()
    : m_position({ 0,0,0 }), m_modelPath(L""), m_speed(5.f),
    m_collisionRadius(1.0f), m_maxHP(10), m_score(100)
{
}

EnemyBuilder& EnemyBuilder::SetPosition(const VECTOR& position) { m_position = position; return *this; }
EnemyBuilder& EnemyBuilder::SetModel(const std::wstring& modelPath) { m_modelPath = modelPath; return *this; }
EnemyBuilder& EnemyBuilder::SetSpeed(float speed) { m_speed = speed; return *this; }
EnemyBuilder& EnemyBuilder::SetCollisionRadius(float radius) { m_collisionRadius = radius; return *this; }
EnemyBuilder& EnemyBuilder::SetInitialHealth(int maxHP) { m_maxHP = maxHP; return *this; }
EnemyBuilder& EnemyBuilder::SetScore(int score) { m_score = score; return *this; }

// �� �C���_: �߂�l�̌^�ƁAmake_shared �ւ̕ύX
std::shared_ptr<EnemyEntity> EnemyBuilder::Build() const
{
    // �� ������ make_shared ���g�����ƂŁAAddComponent���Ă΂��O��
    //    �G���e�B�e�B�� shared_ptr �̊Ǘ����ɓ���A���S�ɂȂ�܂��B
    auto enemy = std::make_shared<EnemyEntity>();
    enemy->SetScore(m_score);

    // --- ����ȍ~�� AddComponent �Ăяo���͑S�Ĉ��S ---
    enemy->AddComponent<TransformComponent>()->SetPosition(m_position);
    enemy->AddComponent<RenderModelComponent>()->SetModel(m_modelPath);
    enemy->AddComponent<HomingMoveComponent>()->SetSpeed(m_speed);

    auto health = enemy->AddComponent<HealthComponent>();
    health->Setup(m_maxHP);
    health->SetOnDeathCallback([enemy_ptr = enemy.get()]() {
        enemy_ptr->SetActive(false);
        });

    auto collider = enemy->AddComponent<SphereCollisionComponent>();
    collider->SetRadius(m_collisionRadius);
    collider->SetOnCollision([enemy_ptr = enemy.get()](const std::shared_ptr<Entity>& other) {
        if (other && other->GetTag() == L"Bullet")
        {
            other->SetActive(false);
            if (auto healthComp = enemy_ptr->GetComponent<HealthComponent>())
            {
                healthComp->TakeDamage(1);
            }
        }
        });

    return enemy;
}