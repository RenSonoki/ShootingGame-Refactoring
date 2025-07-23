#include "BulletShooterComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "BulletPrototype.h"
#include "BulletEntity.h"
#include "EntitySystem.h"
#include <cassert>

// �� �C���_: �f�t�H���g�R���X�g���N�^�̎���
BulletShooterComponent::BulletShooterComponent()
    : m_entitySystem(nullptr)
    , m_prototype(nullptr)
    , m_transform(nullptr)
    , m_cooldownTime(0.3f)
    , m_timer(0.0f)
    , m_isShootRequested(false)
{
}

// �� �C���_: �ˑ����𒍓����邽�߂�Setup���\�b�h
void BulletShooterComponent::Setup(std::shared_ptr<BulletPrototype> prototype, EntitySystem* entitySystem)
{
    m_prototype = prototype;
    m_entitySystem = entitySystem;
    assert(m_prototype != nullptr && "BulletShooterComponent requires a BulletPrototype.");
    assert(m_entitySystem != nullptr && "BulletShooterComponent requires an EntitySystem.");
}


ComponentID BulletShooterComponent::GetID() const
{
    return ComponentID::Shooting;
}

void BulletShooterComponent::Start()
{
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_transform != nullptr && "BulletShooterComponent requires a TransformComponent.");
}

void BulletShooterComponent::Update(float deltaTime)
{
    if (m_timer > 0.0f)
    {
        m_timer -= deltaTime;
    }

    if (m_isShootRequested && CanShoot())
    {
        Shoot();
    }

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

bool BulletShooterComponent::CanShoot() const
{
    return m_timer <= 0.0f;
}

// private
void BulletShooterComponent::Shoot()
{
    // �ˑ��֌W���ݒ肳��Ă��Ȃ��ꍇ�͉������Ȃ�
    if (!m_transform || !m_prototype || !m_entitySystem) return;

    VECTOR pos = m_transform->GetPosition();
    VECTOR dir = m_transform->GetForward();

    // �v���g�^�C�v����e�𕡐�
    auto bullet = m_prototype->Clone(pos, dir);
    if (bullet)
    {
        // �G���e�B�e�B�V�X�e���ɐV�����e��ǉ�
        m_entitySystem->AddEntity(bullet);
        // �N�[���_�E���^�C�}�[�����Z�b�g
        m_timer = m_cooldownTime;
    }
}