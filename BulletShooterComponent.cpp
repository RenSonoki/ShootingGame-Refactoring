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
    // �N�[���_�E���^�C�}�[��i�߂�
    if (m_timer > 0.0f)
    {
        m_timer -= deltaTime;
    }

    // ���˂��v������Ă��āA�N�[���_�E�����I����Ă���Δ���
    if (m_isShootRequested && m_timer <= 0.0f)
    {
        Shoot();
    }

    // �v���t���O�͖��t���[�����Z�b�g
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

    // BulletFactory�ł͂Ȃ��A�v���g�^�C�v��Clone���\�b�h�𒼐ڎg��
    auto bullet = m_prototype->Clone(pos, dir);
    if (bullet)
    {
        m_entitySystem->AddEntity(bullet);
        m_timer = m_cooldownTime; // �N�[���_�E���^�C�}�[�����Z�b�g
    }
}