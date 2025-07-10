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

    // --- 各コンポーネントを生成し、設定し、アタッチする ---

    // 1. TransformComponent
    auto transform = std::make_shared<TransformComponent>();
    transform->SetPosition(position);
    AddComponent(transform);

    // 2. RenderModelComponent
    AddComponent(std::make_shared<RenderModelComponent>(modelPath));

    // 3. HomingMoveComponent
    auto homingMove = std::make_shared<HomingMoveComponent>(speed);
    AddComponent(homingMove);
    // ※ターゲットはSetTargetメソッドで後から設定する

    // 4. HealthComponent（体力）
    auto health = std::make_shared<HealthComponent>(10); // 例：体力10
    health->SetOnDeathCallback([this]
        {
        // 体力がゼロになったら（死んだら）スコアを通知して、自身を非アクティブ化
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
        // 弾に当たったら...
        if (other && other->GetTag() == L"Bullet")
        {
            // 弾を非アクティブ化
            other->SetActive(false);

            // 自身のHealthComponentにダメージを伝える
            if (auto healthComp = this->GetComponent<HealthComponent>())
            {
                healthComp->TakeDamage(1); // 例：ダメージ1
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