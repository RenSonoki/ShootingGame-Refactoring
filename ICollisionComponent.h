#pragma once

#include "LogicComponent.h"
#include "DxLib.h"
#include <functional>
#include <memory>
#include "CollisionShapeType.h"

// 前方宣言
class Entity;
class SphereCollisionComponent;
class BoxCollisionComponent;
class CapsuleCollisionComponent;

// 衝突インターフェース + 登録制御
class ICollisionComponent : public LogicComponent, public std::enable_shared_from_this<ICollisionComponent>
{
public:
    virtual ~ICollisionComponent();

	// ビジターパターンを用いて衝突形状を処理
	// NOTE: これにより、自信や他の衝突形状を直接参照することなく、衝突判定を行うことができる
    virtual bool CheckCollision(const ICollisionComponent& other) const = 0;
    virtual bool Accept(const ICollisionComponent& other) const = 0;
    virtual bool Visit(const SphereCollisionComponent& sphere) const = 0;
    virtual bool Visit(const BoxCollisionComponent& box) const = 0;
    virtual bool Visit(const CapsuleCollisionComponent& capsule) const = 0;

    virtual VECTOR GetCenter() const = 0;
    virtual CollisionShapeType GetShapeType() const { return CollisionShapeType::Unknown; }

    // 衝突イベント
    void SetOnCollision(std::function<void(Entity*)> callback);
    void TriggerCollision(Entity* other) const;

    // 所有者（登録時にも使用）
    void SetOwner(Entity* owner) override;
    Entity* GetOwner() const { return m_owner; }

    // NOTE: 生成時に登録を行い、デストラクタで登録を解除する
	//       こうすることで、登録のし忘れや解除のし忘れによるメモリリークを防ぐ

protected:
    Entity* m_owner = nullptr;
    std::function<void(Entity*)> m_onCollision;
};