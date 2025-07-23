#pragma once
#include "ComponentBase.h"
#include <functional>

/**
 * @class HealthComponent
 * @brief �L�����N�^�[�̗̑͂␶���A���G��Ԃ��Ǘ�����R���|�[�l���g
 */
class HealthComponent : public ComponentBase
{
public:
    HealthComponent();

    ComponentID GetID() const override;

    // --- ���C�t�T�C�N�����\�b�h ---
    void Update(float deltaTime) override;

    /**
     * @brief �R���|�[�l���g�̏����ݒ���s���܂��B
     * @param maxHP �ő�̗�
     * @param initialInvincibilitySec ��������̖��G���ԁi�b�j
     */
    void Setup(int maxHP, float initialInvincibilitySec = 0.0f);

    // --- �A�N�V���� ---
    void TakeDamage(int amount);
    void Heal(int amount);
    void SetInvincible(float durationSec);

    // --- ��Ԏ擾�Q�b�^�[ ---
    int GetHP() const;
    int GetMaxHP() const;
    bool IsAlive() const;
    bool IsDead() const;
    bool IsInvincible() const;
    float GetInvincibleTimeRemaining() const;

    // --- �C�x���g�R�[���o�b�N�ݒ� ---
    void SetOnDeathCallback(const std::function<void()>& callback);
    void SetOnDamageCallback(const std::function<void(int)>& callback);
    void SetOnHealCallback(const std::function<void(int)>& callback);

private:
    int m_maxHP;
    int m_currentHP;
    bool m_dead;
    float m_invincibleTimer;

    // �e��R�[���o�b�N�֐�
    std::function<void()> m_onDeathCallback;
    std::function<void(int)> m_onDamageCallback;
    std::function<void(int)> m_onHealCallback;
};