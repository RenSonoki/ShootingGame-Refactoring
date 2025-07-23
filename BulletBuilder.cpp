#include "BulletBuilder.h"
#include "BulletEntity.h"

// �e�R���|�[�l���g�̃w�b�_���C���N���[�h
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include "MoveComponent.h"
#include "LifetimeComponent.h"
#include "SphereCollisionComponent.h"

// �R���X�g���N�^��Z�b�^�[�͕ύX�Ȃ�
BulletBuilder::BulletBuilder()
    : m_pos({ 0.0f, 0.0f, 0.0f })
    , m_dir({ 0.0f, 0.0f, 1.0f })
    , m_speed(100.0f)
    , m_lifetime(5.0f)
    , m_modelPath(L"")
    , m_collisionRadius(0.5f)
{
}
BulletBuilder& BulletBuilder::SetPosition(const VECTOR& pos) { m_pos = pos; return *this; }
BulletBuilder& BulletBuilder::SetDirection(const VECTOR& dir) { m_dir = dir; return *this; }
BulletBuilder& BulletBuilder::SetSpeed(float speed) { m_speed = speed; return *this; }
BulletBuilder& BulletBuilder::SetLifetime(float lifetime) { m_lifetime = lifetime; return *this; }
BulletBuilder& BulletBuilder::SetModel(const std::wstring& modelPath) { m_modelPath = modelPath; return *this; }
BulletBuilder& BulletBuilder::SetCollisionRadius(float radius) { m_collisionRadius = radius; return *this; }


// ������ Build���\�b�h��S�ʓI�ɏC�� ������
std::shared_ptr<BulletEntity> BulletBuilder::Build() const
{
    // �� ������ make_shared ���g�����ƂŁAAddComponent���Ă΂��O��
    //    �G���e�B�e�B�� shared_ptr �̊Ǘ����ɓ���A���S�ɂȂ�܂��B
    auto bullet = std::make_shared<BulletEntity>();

    // 1. TransformComponent��Entity�ɍ���Ă��炢�A�ݒ肷��
    auto transform = bullet->AddComponent<TransformComponent>();
    transform->SetPosition(m_pos);

    // 2. RenderModelComponent��Entity�ɍ���Ă��炢�A�ݒ肷��
    auto renderer = bullet->AddComponent<RenderModelComponent>();
    renderer->SetModel(m_modelPath);

    // 3. MoveComponent��Entity�ɍ���Ă��炢�A�ݒ肷��
    auto move = bullet->AddComponent<MoveComponent>();
    move->SetSpeed(m_speed);
    move->SetDirection(m_dir);

    // 4. LifetimeComponent��Entity�ɍ���Ă��炢�A�ݒ肷��
    auto life = bullet->AddComponent<LifetimeComponent>();
    life->SetLifetime(m_lifetime);
    life->SetOnExpired([bullet_ptr = bullet.get()]() {
        bullet_ptr->SetActive(false);
        });

    // 5. SphereCollisionComponent��Entity�ɍ���Ă��炢�A�ݒ肷��
    auto collider = bullet->AddComponent<SphereCollisionComponent>();
    collider->SetRadius(m_collisionRadius);

    // �����_���̈����� `Entity*` ���� `const std::shared_ptr<Entity>&` �ɕύX
    collider->SetOnCollision([bullet_ptr = bullet.get()](const std::shared_ptr<Entity>& other) {
        if (other && other->GetTag() == L"Enemy") {
            bullet_ptr->SetActive(false);
        }
        });

    return bullet;
}