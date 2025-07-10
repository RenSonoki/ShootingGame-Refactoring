#pragma once

#include "LogicComponent.h"
#include <functional>

// キャラクターのヘルス等を管理するコンポーネント
class HealthComponent : public LogicComponent
{
public:
    // 無敵時間を秒数で指定
    HealthComponent(int maxHP = 100, float initialInvincibilitySec = 1.0f);

    // 基底クラスに合わせて override
    void Update(float deltaTime) override;

    void TakeDamage(int amount);
    void Heal(int amount);

    // 無敵時間を秒数で指定する
    void SetInvincible(float durationSec);

    int GetHP() const;
    int GetMaxHP() const;
    bool IsAlive() const;
    bool IsDead() const;
    bool IsInvincible() const;

    // 残り無敵時間を秒数で返す
    float GetInvincibleTimeRemaining() const;

    // 各種イベントコールバック
    void SetOnDeathCallback(const std::function<void()>& callback);
    void SetOnDamageCallback(const std::function<void(int)>& callback);
    void SetOnHealCallback(const std::function<void(int)>& callback);

private:
    int m_maxHP;
    int m_currentHP;
    bool m_dead;

    float m_invincibleTimer;

    std::function<void()> m_onDeathCallback;
    std::function<void(int)> m_onDamageCallback;
    std::function<void(int)> m_onHealCallback;
};