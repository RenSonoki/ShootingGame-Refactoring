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

    // --- 各コンポーネントを、最新のアーキテクチャに沿って生成・設定し、アタッチ ---

    // 1. TransformComponent: 生成後に位置を設定
    auto transform = std::make_shared<TransformComponent>();
    transform->SetPosition(pos);
    AddComponent(transform);

    // 2. RenderModelComponent: モデルパスを指定するだけ
    AddComponent(std::make_shared<RenderModelComponent>(modelPath));

    // ★★★ ここが最後の修正箇所です ★★★
    // 3. MoveComponent: 引数なしで生成し、セッターで設定する
    auto move = std::make_shared<MoveComponent>();
    move->SetSpeed(speed);
    move->SetDirection(dir);
    AddComponent(move);
    // ★★★ ここまで ★★★

    // 4. LifetimeComponent: 寿命を秒数で設定
    auto life = std::make_shared<LifetimeComponent>(lifetimeInSeconds);
    life->SetOnExpired([this]() {
        this->SetActive(false);
        });
    AddComponent(life);

    // 5. SphereCollisionComponent: 半径を指定するだけ
    auto collider = std::make_shared<SphereCollisionComponent>(0.5f);
    collider->SetOnCollision([this](Entity* other) {
        if (other && other->GetTag() == L"Enemy") {
            this->SetActive(false);
        }
        });
    AddComponent(collider);
}