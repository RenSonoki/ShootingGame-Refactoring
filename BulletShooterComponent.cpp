#include "BulletShooterComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "BulletPrototype.h"
#include "EntitySystem.h"
#include <cassert>

BulletShooterComponent::BulletShooterComponent(
    EntitySystem* entitySystem,
    std::shared_ptr<BulletPrototype> prototype)
    : m_entitySystem(entitySystem)
    , m_prototype(prototype)
    , m_transform(nullptr)
{
    assert(m_entitySystem != nullptr && "BulletShooterComponent requires an EntitySystem.");
    assert(m_prototype != nullptr && "BulletShooterComponent requires a BulletPrototype.");
}

void BulletShooterComponent::Start()
{
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_transform != nullptr && "BulletShooterComponent requires a TransformComponent.");
}

void BulletShooterComponent::Update(float deltaTime)
{
    // クールダウンタイマーを進める
    if (m_timer > 0.0f)
    {
        m_timer -= deltaTime;
    }

    // 発射が要求されていて、クールダウンが終わっていれば発射
    if (m_isShootRequested && m_timer <= 0.0f)
    {
        Shoot();
    }

    // 要求フラグは毎フレームリセット
    m_isShootRequested = false;
}

void BulletShooterComponent::RequestShoot()
{
    m_isShootRequested = true;
}

void BulletShooterComponent::SetCooldown(float seconds)
{
    m_cooldownTime = seconds;
}

void BulletShooterComponent::Shoot()
{
    if (!m_transform) return;

    VECTOR pos = m_transform->GetPosition();
    VECTOR dir = m_transform->GetForward();

    // BulletFactoryではなく、プロトタイプのCloneメソッドを直接使う
    auto bullet = m_prototype->Clone(pos, dir);
    if (bullet)
    {
        m_entitySystem->AddEntity(bullet);
        m_timer = m_cooldownTime; // クールダウンタイマーをリセット
    }
}