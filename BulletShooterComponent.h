#pragma once

#include "LogicComponent.h"
#include <memory>

class TransformComponent;
class EntitySystem;
class BulletPrototype;

// 弾の発射とクールダウンを制御するコンポーネント
class BulletShooterComponent : public LogicComponent
{
public:
    // 自身のTransformは渡さず、外部のシステムや設計図を受け取る
    BulletShooterComponent(EntitySystem* entitySystem, std::shared_ptr<BulletPrototype> prototype);

    void Start() override;
    void Update(float deltaTime) override;

    // 発射リクエスト
    void RequestShoot();

    // クールダウン時間を秒数で設定
    void SetCooldown(float seconds);

private:
    void Shoot(); // 内部的な発射処理

    std::shared_ptr<TransformComponent> m_transform;
    EntitySystem* m_entitySystem;
    std::shared_ptr<BulletPrototype> m_prototype;

    // タイマーとクールダウンを秒数(float)で管理
    float m_cooldownTime = 0.3f; // デフォルトは0.3秒
    float m_timer = 0.0f;
    bool m_isShootRequested = false;
};