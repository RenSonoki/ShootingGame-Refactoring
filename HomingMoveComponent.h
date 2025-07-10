#pragma once

#include "LogicComponent.h"
#include <memory>

class TransformComponent;

// 特定の対象へ向かって移動するコンポーネント
class HomingMoveComponent : public LogicComponent
{
public:
    explicit HomingMoveComponent(float speed);

    void Start() override;
    void Update(float deltaTime) override;

    // 追尾対象の設定
    void SetTarget(std::shared_ptr<TransformComponent> target);

private:
    std::shared_ptr<TransformComponent> m_selfTransform;

    // ターゲットは弱参照(weak_ptr)で持つのがより安全
    std::weak_ptr<TransformComponent> m_targetTransform;
    float m_speed = 1.0f;
};