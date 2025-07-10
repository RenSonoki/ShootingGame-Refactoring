#pragma once

#include "LogicComponent.h"
#include <memory>

// 前方宣言
class TransformComponent; 

// プレイヤーの移動入力を処理し、Transformの速度を制御するコンポーネント
class PlayerControllerComponent : public LogicComponent
{
public:
    PlayerControllerComponent();

	// ライフサイクルメソッド
    void Start() override;
    void Update(float deltaTime) override;

    // 移動速度の設定
    void SetMoveSpeed(float speed);
    float GetMoveSpeed() const;

private:
    std::shared_ptr<TransformComponent> m_transform;
    float m_moveSpeed = 5.0f; // 速度なので、少し大きめの値に変更
};