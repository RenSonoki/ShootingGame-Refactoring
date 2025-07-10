#pragma once

#include "LogicComponent.h"
#include <memory>
#include <DxLib.h>

// 前方宣言
class TransformComponent; 

// 一定方向に速度で移動させるコンポーネント
class MoveComponent : public LogicComponent
{
public:
    MoveComponent();

    void Start() override;
    void Update(float deltaTime) override;

    void SetDirection(const VECTOR& dir);
    void SetSpeed(float speed);

private:
    std::shared_ptr<TransformComponent> m_transform;
    VECTOR m_direction = VGet(0, 0, 1); // デフォルトはZ軸正方向
    float m_speed = 10.0f;
};