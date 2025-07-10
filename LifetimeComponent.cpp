#include "LifetimeComponent.h"
#include "Entity.h"
#include "ColliderManager.h" // Entity���V�[������폜����ꍇ�ɕK�v�ɂȂ邩��

LifetimeComponent::LifetimeComponent(float lifetimeInSeconds)
{
    SetLifetime(lifetimeInSeconds);
}

void LifetimeComponent::SetLifetime(float lifetimeInSeconds)
{
    m_lifetime = lifetimeInSeconds;
    m_expired = false;
}

bool LifetimeComponent::IsExpired() const
{
    return m_expired;
}

void LifetimeComponent::Update(float deltaTime)
{
    if (m_expired || m_lifetime < 0.0f) return; // �i���i���̒l�j�̏ꍇ�͉������Ȃ�

    m_lifetime -= deltaTime;
    if (m_lifetime <= 0.0f)
    {
        m_expired = true;

        // �R�[���o�b�N���ݒ肳��Ă���΁A������Ăяo��
        if (m_onExpiredCallback)
        {
            m_onExpiredCallback();
        }
        else
        {
            // �f�t�H���g�̓���F�I�[�i�[���A�N�e�B�u�ɂ���
            if (Entity* owner = GetOwner())
            {
                owner->SetActive(false);
            }
        }
    }
}

void LifetimeComponent::SetOnExpired(const std::function<void()>& callback)
{
    m_onExpiredCallback = callback;
}