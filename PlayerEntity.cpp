#include "PlayerEntity.h"
#include "HealthComponent.h"
#include "TransformComponent.h"
#include "BulletShooterComponent.h"

PlayerEntity::PlayerEntity()
{
    SetTag(L"Player");
}

// �Q�b�^�[�̎����͕ύX�Ȃ�
std::shared_ptr<TransformComponent> PlayerEntity::GetTransform() const { return GetComponent<TransformComponent>(); }
std::shared_ptr<HealthComponent> PlayerEntity::GetHealth() const { return GetComponent<HealthComponent>(); }
std::shared_ptr<BulletShooterComponent> PlayerEntity::GetShooter() const { return GetComponent<BulletShooterComponent>(); }

int PlayerEntity::GetHP() const
{
    if (auto health = GetHealth()) return health->GetHP();
    return 0;
}

bool PlayerEntity::IsAlive() const
{
    if (auto health = GetHealth()) return health->IsAlive();
    return false;
}

bool PlayerEntity::IsDead() const
{
    // ���g��HealthComponent���擾
    if (auto health = GetComponent<HealthComponent>())
    {
        // HealthComponent��IsDead()�̌��ʂ�Ԃ�
        return health->IsDead();
    }
    // HealthComponent���Ȃ���΁A���S�̂��߂Ɂu���S���Ă���v�Ƃ݂Ȃ�
    return true;
}