#pragma once

#include "LogicComponent.h"
#include <functional>

// 寿命を管理するコンポーネント
class LifetimeComponent : public LogicComponent
{
public:
    // 寿命を秒数で指定
    explicit LifetimeComponent(float lifetimeInSeconds);

    void Update(float deltaTime) override;

    // 寿命を秒数で設定
    void SetLifetime(float lifetimeInSeconds);
    bool IsExpired() const;

    // 寿命が尽きた時のコールバックを設定
	// 寿命が尽きる動作をコンポーネント設定側で定義できるようにする例: エフェクトの削除など)
    void SetOnExpired(const std::function<void()>& callback);

private:
    // 寿命を秒数(float)で管理
    float m_lifetime = 0.0f;
    bool m_expired = false;

    // コールバック関数
    std::function<void()> m_onExpiredCallback;
};