#pragma once

#include "LogicComponent.h"
#include "DxLib.h"

// 空間情報（位置・回転・速度）を管理するコンポーネント
// NOTE: 大規模な開発になった場合は、位置や回転のデータと演算処理を分離する
class TransformComponent : public LogicComponent
{
public:
    TransformComponent();
	explicit TransformComponent(const VECTOR& pos); // explicitを用いてコンストラクタを明示的に定義

    // 基底クラスに合わせて override
    // NOTE: 自分の速度を使って自分の位置を更新する自己完結
    void Update(float deltaTime) override;

    // 位置
    const VECTOR& GetPosition() const;
    void SetPosition(const VECTOR& pos);

    // 速度
    const VECTOR& GetVelocity() const;
    void SetVelocity(const VECTOR& vel);

    // 回転（Yaw, Pitch, Roll）
    const VECTOR& GetRotation() const;
    void SetRotation(const VECTOR& rot);

    // スケール
    const VECTOR& GetScale() const;
    void SetScale(const VECTOR& scale);

    // 前方ベクトル
    VECTOR GetForward() const;

private:
    VECTOR m_position;
    VECTOR m_velocity;
    VECTOR m_rotation; // x:Pitch, y:Yaw, z:Roll
    VECTOR m_scale;
};