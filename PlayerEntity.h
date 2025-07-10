#pragma once

#include "Entity.h"
#include <memory>
#include <string>

// 前方宣言
class TransformComponent;
class HealthComponent;
class BulletShooterComponent;
class BulletPrototype;
class EntitySystem;

// プレイヤーキャラクターの設計図となるエンティティクラス
class PlayerEntity : public Entity
{
public:
    // 生成に必要な情報をコンストラクタで受け取る
    PlayerEntity(const std::wstring& modelPath,
        EntitySystem* entitySystem,                          // 弾を生成するために必要
        std::shared_ptr<BulletPrototype> bulletPrototype);

    // GetComponent<T>()を直接呼び出すように変更
    std::shared_ptr<TransformComponent> GetTransform() const;
    std::shared_ptr<HealthComponent> GetHealth() const;
    std::shared_ptr<BulletShooterComponent> GetShooter() const;

    int GetHP() const;
    bool IsAlive() const;
};