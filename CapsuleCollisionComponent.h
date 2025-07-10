#pragma once

#include "ICollisionComponent.h"
#include <memory>
#include <utility> // for std::pair
#include <DxLib.h>

// 前方宣言
class TransformComponent;

// カプセル形状のコライダーコンポーネント
class CapsuleCollisionComponent : public ICollisionComponent
{
public:
    // カプセルの半径と、中心線の長さ（高さ）を指定して作成
    explicit CapsuleCollisionComponent(float radius, float height);

    // ライフサイクルメソッド
    void Start() override;
    void Update(float deltaTime) override {}

    // Visitorパターン関連メソッド
    bool CheckCollision(const ICollisionComponent& other) const override;
    bool Accept(const ICollisionComponent& other) const override;
    bool Visit(const SphereCollisionComponent& sphere) const override;
    bool Visit(const BoxCollisionComponent& box) const override;
    bool Visit(const CapsuleCollisionComponent& capsule) const override;

    // 形状情報
    VECTOR GetCenter() const override;
    float GetRadius() const;
    float GetHeight() const;

    // カプセルの中心線（線分）の始点と終点をワールド座標で取得
    std::pair<VECTOR, VECTOR> GetLineSegment() const;

    void SetBaseRadius(float radius);
    void SetBaseHeight(float height);

    CollisionShapeType GetShapeType() const override { return CollisionShapeType::Capsule; }

private:
    float m_baseRadius; // スケール適用前の基本半径
    float m_baseHeight; // スケール適用前の基本高さ
    std::shared_ptr<TransformComponent> m_transform;
};