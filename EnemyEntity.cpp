#include "EnemyEntity.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include "HomingMoveComponent.h"
#include "SphereCollisionComponent.h"
#include "HealthComponent.h"

EnemyEntity::EnemyEntity(
    const VECTOR& position,
    const std::wstring& modelPath,
    float speed,
    float collisionRadius)
{
    SetTag(L"Enemy");

    // --- �e�R���|�[�l���g�𐶐����A�ݒ肵�A�A�^�b�`���� ---

    // 1. TransformComponent
    auto transform = std::make_shared<TransformComponent>();
    transform->SetPosition(position);
    AddComponent(transform);

    // 2. RenderModelComponent
    AddComponent(std::make_shared<RenderModelComponent>(modelPath));

    // 3. HomingMoveComponent
    auto homingMove = std::make_shared<HomingMoveComponent>(speed);
    AddComponent(homingMove);
    // ���^�[�Q�b�g��SetTarget���\�b�h�Ōォ��ݒ肷��

    // 4. HealthComponent�i�̗́j
    auto health = std::make_shared<HealthComponent>(10); // ��F�̗�10
    health->SetOnDeathCallback([this]
        {
        // �̗͂��[���ɂȂ�����i���񂾂�j�X�R�A��ʒm���āA���g���A�N�e�B�u��
        if (m_onDestroyCallback)
        {
            m_onDestroyCallback(m_score);
        }
        this->SetActive(false);
        });
    AddComponent(health);

    // 5. SphereCollisionComponent
    auto collider = std::make_shared<SphereCollisionComponent>(collisionRadius);
    collider->SetOnCollision([this](Entity* other)
        {
        // �e�ɓ���������...
        if (other && other->GetTag() == L"Bullet")
        {
            // �e���A�N�e�B�u��
            other->SetActive(false);

            // ���g��HealthComponent�Ƀ_���[�W��`����
            if (auto healthComp = this->GetComponent<HealthComponent>())
            {
                healthComp->TakeDamage(1); // ��F�_���[�W1
            }
        }
        });
    AddComponent(collider);
}

void EnemyEntity::SetTarget(std::shared_ptr<TransformComponent> target)
{
    if (auto homingMove = GetComponent<HomingMoveComponent>())
    {
        homingMove->SetTarget(target);
    }
}

void EnemyEntity::SetScore(int score)
{
    m_score = score;
}

void EnemyEntity::SetOnDestroyCallback(std::function<void(int)> callback)
{
    m_onDestroyCallback = std::move(callback);
}