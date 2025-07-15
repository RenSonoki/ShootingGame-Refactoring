#pragma once
#include "ICollisionComponent.h" // 私たちがリファクタリングしたICollisionComponent
#include <memory>

class TransformComponent;

// 球体衝突コンポーネント
class SphereCollisionComponent : public ICollisionComponent
{
public:
    explicit SphereCollisionComponent(float radius);
    virtual ~SphereCollisionComponent() = default;

    // --- ComponentBaseのライフサイクルメソッド ---
    void Start() override;
    // UpdateはColliderManagerが一括で処理するため、個々には不要
    void Update(float deltaTime) override {}

    // --- ICollisionComponentインターフェースの実装 ---
    CollisionShapeType GetShapeType() const override { return CollisionShapeType::Sphere; }
    VECTOR GetCenter() const override;

    // --- このクラス固有の機能 ---
    float GetRadius() const;
    void SetBaseRadius(float radius);

private:
    float m_baseRadius;
    // TransformComponentへのポインタはweak_ptrにすると、より安全です
    std::weak_ptr<TransformComponent> m_transform;
};