#include "HealthComponent.h"
#include <algorithm> // std::max �̂���

HealthComponent::HealthComponent(int maxHP, float initialInvincibilitySec)
    : m_maxHP(maxHP)
    , m_currentHP(maxHP)
    , m_invincibleTimer(initialInvincibilitySec)
    , m_dead(false)
{
}

void HealthComponent::Update(float deltaTime)
{
    // ���t���[���A�o�ߎ���(deltaTime)�����^�C�}�[�����炷
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
        // �_���[�W���󂯂���0.5�b�̖��G���Ԃ�t�^
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
    // ���݂̎c�莞�Ԃ�蒷�����Ԃ��w�肳�ꂽ�ꍇ�̂ݍX�V
    m_invincibleTimer = std::max(m_invincibleTimer, durationSec);
}

int HealthComponent::GetHP() const { return m_currentHP; }
int HealthComponent::GetMaxHP() const { return m_maxHP; }
bool HealthComponent::IsAlive() const { return !m_dead; }
bool HealthComponent::IsDead() const { return m_dead; }
bool HealthComponent::IsInvincible() const { return m_invincibleTimer > 0.0f; }
float HealthComponent::GetInvincibleTimeRemaining() const { return m_invincibleTimer; }

// --- �R�[���o�b�N�̃Z�b�^�[�͕ύX�Ȃ� ---
void HealthComponent::SetOnDeathCallback(const std::function<void()>& callback) { m_onDeathCallback = callback; }
void HealthComponent::SetOnDamageCallback(const std::function<void(int)>& callback) { m_onDamageCallback = callback; }
void HealthComponent::SetOnHealCallback(const std::function<void(int)>& callback) { m_onHealCallback = callback; }