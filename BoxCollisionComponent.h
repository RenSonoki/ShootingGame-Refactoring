#pragma once

#include "ICollisionComponent.h"
#include <memory>
#include <DxLib.h> // VECTORのため

// 前方宣言
class TransformComponent;

// ボックス（AABB）形状のコライダーコンポーネント
class BoxCollisionComponent : public ICollisionComponent
{
public:
    // ボックスのサイズ（幅、高さ、奥行き）を指定して作成
    explicit BoxCollisionComponent(const VECTOR& size);

    // ライフサイクルメソッド
    void Start() override;
    void Update(float deltaTime) override {} // 何もしない

    // Visitorパターン関連メソッド
    bool CheckCollision(const ICollisionComponent& other) const override;
    bool Accept(const ICollisionComponent& other) const override;
    bool Visit(const SphereCollisionComponent& sphere) const override;
    bool Visit(const BoxCollisionComponent& box) const override;
    bool Visit(const CapsuleCollisionComponent& capsule) const override;

    // 形状情報
    VECTOR GetCenter() const override;
    VECTOR GetSize() const; // スケールを反映した実質的なサイズ
    void SetBaseSize(const VECTOR& size);

    CollisionShapeType GetShapeType() const override { return CollisionShapeType::Box; }

private:
    VECTOR m_baseSize; // スケール適用前の基本サイズ
    std::shared_ptr<TransformComponent> m_transform;
};