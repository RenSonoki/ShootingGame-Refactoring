#include "PlayerEntity.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include "PlayerControllerComponent.h"
#include "BulletShooterComponent.h"
#include "HealthComponent.h"
#include "SphereCollisionComponent.h"
#include "ResourceManager.h" // サウンド再生のため
#include "ResourceTraits.h"  //
#include <DxLib.h>

PlayerEntity::PlayerEntity
(
    const std::wstring& modelPath,
    EntitySystem* entitySystem,
    std::shared_ptr<BulletPrototype> bulletPrototype)
{
    SetTag(L"Player");

    // --- 各コンポーネントを生成・設定し、アタッチ ---

    AddComponent(std::make_shared<TransformComponent>());
    AddComponent(std::make_shared<RenderModelComponent>(modelPath));
    AddComponent(std::make_shared<PlayerControllerComponent>());

    auto shooter = std::make_shared<BulletShooterComponent>(entitySystem, bulletPrototype);
    AddComponent(shooter);

    // 体力を設定し、無敵時間は秒数(float)で指定
    auto health = std::make_shared<HealthComponent>(3, 1.5f); // 体力3、ダメージ後1.5秒無敵
    health->SetOnDamageCallback([](int)
        {
        // ResourceManager経由でサウンドを取得・再生
        int handle = ResourceManager::Instance().Get<SoundTag>(L"Assets/SE/damage.wav");
        if (handle != -1) PlaySoundMem(handle, DX_PLAYTYPE_BACK);
        });
    health->SetOnDeathCallback([this]()
        {
        this->SetActive(false); // 死んだら消える
        });
    AddComponent(health);

    auto collider = std::make_shared<SphereCollisionComponent>(1.0f); // 半径1.0
    collider->SetOnCollision([this](Entity* other)
        {
        if (other && (other->GetTag() == L"Enemy" || other->GetTag() == L"EnemyBullet"))
        {
            // 敵か敵の弾に当たったら、HealthComponentにダメージを伝える
            if (auto healthComp = this->GetComponent<HealthComponent>())
            {
                healthComp->TakeDamage(1);
            }
        }
        });
    AddComponent(collider);
}

// --- ゲッターはGetComponentを呼び出すだけ ---

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