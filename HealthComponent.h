#pragma once

#include "LogicComponent.h"
#include <functional>

// �L�����N�^�[�̃w���X�����Ǘ�����R���|�[�l���g
class HealthComponent : public LogicComponent
{
public:
    // ���G���Ԃ�b���Ŏw��
    HealthComponent(int maxHP = 100, float initialInvincibilitySec = 1.0f);

    // ���N���X�ɍ��킹�� override
    void Update(float deltaTime) override;

    void TakeDamage(int amount);
    void Heal(int amount);

    // ���G���Ԃ�b���Ŏw�肷��
    void SetInvincible(float durationSec);

    int GetHP() const;
    int GetMaxHP() const;
    bool IsAlive() const;
    bool IsDead() const;
    bool IsInvincible() const;

    // �c�薳�G���Ԃ�b���ŕԂ�
    float GetInvincibleTimeRemaining() const;

    // �e��C�x���g�R�[���o�b�N
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