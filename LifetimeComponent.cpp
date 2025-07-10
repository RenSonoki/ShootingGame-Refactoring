#include "LifetimeComponent.h"
#include "Entity.h"
#include "ColliderManager.h" // Entityをシーンから削除する場合に必要になるかも

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
    if (m_expired || m_lifetime < 0.0f) return; // 永続（負の値）の場合は何もしない

    m_lifetime -= deltaTime;
    if (m_lifetime <= 0.0f)
    {
        m_expired = true;

        // コールバックが設定されていれば、それを呼び出す
        if (m_onExpiredCallback)
        {
            m_onExpiredCallback();
        }
        else
        {
            // デフォルトの動作：オーナーを非アクティブにする
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