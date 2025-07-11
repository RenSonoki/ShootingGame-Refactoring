#include "PlayerEntity.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include "PlayerControllerComponent.h"
#include "BulletShooterComponent.h"
#include "HealthComponent.h"
#include "SphereCollisionComponent.h"
#include "ResourceManager.h" // �T�E���h�Đ��̂���
#include "ResourceTraits.h"  //
#include <DxLib.h>

PlayerEntity::PlayerEntity
(
    const std::wstring& modelPath,
    EntitySystem* entitySystem,
    std::shared_ptr<BulletPrototype> bulletPrototype)
{
    SetTag(L"Player");

    // --- �e�R���|�[�l���g�𐶐��E�ݒ肵�A�A�^�b�` ---

    AddComponent(std::make_shared<TransformComponent>());
    AddComponent(std::make_shared<RenderModelComponent>(modelPath));
    AddComponent(std::make_shared<PlayerControllerComponent>());

    auto shooter = std::make_shared<BulletShooterComponent>(entitySystem, bulletPrototype);
    AddComponent(shooter);

    // �̗͂�ݒ肵�A���G���Ԃ͕b��(float)�Ŏw��
    auto health = std::make_shared<HealthComponent>(3, 1.5f); // �̗�3�A�_���[�W��1.5�b���G
    health->SetOnDamageCallback([](int)
        {
        // ResourceManager�o�R�ŃT�E���h���擾�E�Đ�
        int handle = ResourceManager::Instance().Get<SoundTag>(L"Assets/SE/damage.wav");
        if (handle != -1) PlaySoundMem(handle, DX_PLAYTYPE_BACK);
        });
    health->SetOnDeathCallback([this]()
        {
        this->SetActive(false); // ���񂾂������
        });
    AddComponent(health);

    auto collider = std::make_shared<SphereCollisionComponent>(1.0f); // ���a1.0
    collider->SetOnCollision([this](Entity* other)
        {
        if (other && (other->GetTag() == L"Enemy" || other->GetTag() == L"EnemyBullet"))
        {
            // �G���G�̒e�ɓ���������AHealthComponent�Ƀ_���[�W��`����
            if (auto healthComp = this->GetComponent<HealthComponent>())
            {
                healthComp->TakeDamage(1);
            }
        }
        });
    AddComponent(collider);
}

// --- �Q�b�^�[��GetComponent���Ăяo������ ---

std::shared_ptr<TransformComponent> PlayerEntity::GetTransform() const
{
    return GetComponent<TransformComponent>();
}

std::shared_ptr<HealthComponent> PlayerEntity::GetHealth() const
{
    return GetComponent<HealthComponent>();
}

std::shared_ptr<BulletShooterComponent> PlayerEntity::GetShooter() const
{
    return GetComponent<BulletShooterComponent>();
}

int PlayerEntity::GetHP() const
{
    if (auto health = GetHealth())
    {
        return health->GetHP();
    }
    return 0;
}

bool PlayerEntity::IsAlive() const
{
    if (auto health = GetHealth())
    {
        return health->IsAlive();
    }
    return false;
}