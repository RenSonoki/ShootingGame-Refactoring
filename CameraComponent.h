#pragma once//修正済み

#include "DrawComponent.h"
#include <DxLib.h>

// カメラパラメータ保持用の構造体
struct CameraParameters
{
    VECTOR position = VGet(0, 0, -10);
    VECTOR target = VGet(0, 0, 0);
    VECTOR up = VGet(0, 1, 0);
};

// カメラ設定コンポーネント（描画時にカメラ反映）
class CameraComponent : public DrawComponent
{
public:
    CameraComponent() = default;

    void SetPosition(const VECTOR& pos);
    void SetTarget(const VECTOR& target);
    void SetUpVector(const VECTOR& up);

    VECTOR GetPosition() const;
    VECTOR GetTarget() const;
    VECTOR GetUpVector() const;

    // 描画系処理（EntitySystemから呼ばれる）
	// 自動的にApplyToDxLibCamera()が呼ばれるようにする
    void Draw() override;

    // DxLibにカメラ反映
    void ApplyToDxLibCamera() const;

private:
    CameraParameters m_params;
};