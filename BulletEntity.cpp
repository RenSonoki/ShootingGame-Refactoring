#include "BulletEntity.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include "MoveComponent.h"
#include "LifetimeComponent.h"
#include "SphereCollisionComponent.h"

BulletEntity::BulletEntity(
        const VECTOR& pos, 
        const VECTOR& dir, 
        float speed, 
        float lifetimeInSeconds, 
        const std::wstring& modelPath
    )
{
    SetTag(L"Bullet");

    // --- 各コンポーネントを生成し、アタッチしていく ---
    // 最新の設計では、コンポーネント間の依存関係を手動で繋ぐ必要はない

    // 1. TransformComponent: 位置だけを設定
    auto transform = std::make_shared<TransformComponent>();
    transform->SetPosition(pos);
    AddComponent(transform);

    // 2. RenderModelComponent: モデルパスを指定するだけ
    AddComponent(std::make_shared<RenderModelComponent>(modelPath));

    // 3. MoveComponent: 速度と方向を設定
    auto move = std::make_shared<MoveComponent>(speed);
    move->SetDirection(dir);
    AddComponent(move);

    // 4. LifetimeComponent: 寿命を秒数で設定
    auto life = std::make_shared<LifetimeComponent>(lifetimeInSeconds);
    life->SetOnExpired([this]()
        {
        // 寿命が尽きたら、自身を非アクティブにする
        this->SetActive(false);
        });
    AddComponent(life);

    // 5. SphereCollisionComponent: 半径を指定するだけ
    auto collider = std::make_shared<SphereCollisionComponent>(0.5f);
    collider->SetOnCollision([this](Entity* other)
        {
        // 衝突した相手のタグが "Enemy" だったら...
        if (other && other->GetTag() == L"Enemy")
        {
            // 自身を非アクティブにする（消滅させる）
            this->SetActive(false);
        }
        });
    AddComponent(collider);
}