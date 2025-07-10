#include "HealthComponent.h"
#include <algorithm> // std::max のため

HealthComponent::HealthComponent(int maxHP, float initialInvincibilitySec)
    : m_maxHP(maxHP)
    , m_currentHP(maxHP)
    , m_invincibleTimer(initialInvincibilitySec)
    , m_dead(false)
{
}

void HealthComponent::Update(float deltaTime)
{
    // 毎フレーム、経過時間(deltaTime)だけタイマーを減らす
    if (m_invincibleTimer > 0.0f)
    {
        m_invincibleTimer -= deltaTime;
    }
}

void HealthComponent::TakeDamage(int amount)
{
    if (IsInvincible() || IsDead()) return;

    m_currentHP -= amount;
    if (m_onDamageCallback) m_onDamageCallback(amount);

    if (m_currentHP <= 0)
    {
        m_currentHP = 0;
        m_dead = true;
        if (m_onDeathCallback) m_onDeathCallback();
    }
    else
    {
        // ダメージを受けたら0.5秒の無敵時間を付与
        SetInvincible(0.5f);
    }
}

void HealthComponent::Heal(int amount)
{
    if (IsDead()) return;

    m_currentHP += amount;
    if (m_currentHP > m_maxHP)
    {
        m_currentHP = m_maxHP;
    }

    if (m_onHealCallback) m_onHealCallback(amount);
}

void HealthComponent::SetInvincible(float durationSec)
{
    // 現在の残り時間より長い時間が指定された場合のみ更新
    m_invincibleTimer = std::max(m_invincibleTimer, durationSec);
}

int HealthComponent::GetHP() const { return m_currentHP; }
int HealthComponent::GetMaxHP() const { return m_maxHP; }
bool HealthComponent::IsAlive() const { return !m_dead; }
bool HealthComponent::IsDead() const { return m_dead; }
bool HealthComponent::IsInvincible() const { return m_invincibleTimer > 0.0f; }
float HealthComponent::GetInvincibleTimeRemaining() const { return m_invincibleTimer; }

// --- コールバックのセッターは変更なし ---
void HealthComponent::SetOnDeathCallback(const std::function<void()>& callback) { m_onDeathCallback = callback; }
void HealthComponent::SetOnDamageCallback(const std::function<void(int)>& callback) { m_onDamageCallback = callback; }
void HealthComponent::SetOnHealCallback(const std::function<void(int)>& callback) { m_onHealCallback = callback; }