#pragma once

#include "LogicComponent.h"
#include <memory>
#include <DxLib.h>

// 前方宣言
class TransformComponent;
class CameraComponent;

// ターゲットを追従する三人称視点カメラのロジック
// NOTE: このクラスは、カメラの位置をターゲットのTransformComponentに基づいて更新します。
class ThirdPersonCameraComponent : public LogicComponent
{
public:
    // 追従対象のTransformComponentを弱いポインタで受け取る
    // NOTE: 循環参照をさけるため
    explicit ThirdPersonCameraComponent(std::weak_ptr<TransformComponent> targetTransform);

    // ライフサイクルメソッド
    void Start() override;
    void Update(float deltaTime) override;

    // カメラの距離や高さを設定するセッター
    void SetOffset(const VECTOR& offset);

private:
    // 依存コンポーネントへのポインタ
    std::shared_ptr<CameraComponent> m_camera;

    // 追従対象へのポインタ
    std::weak_ptr<TransformComponent> m_targetTransform;

    // ターゲットからの相対的なカメラの位置
    VECTOR m_offset;
};