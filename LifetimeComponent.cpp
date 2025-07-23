#include "LifetimeComponent.h"
#include "Entity.h" // GetOwner()��SetActive()�̂��߂ɕK�v

LifetimeComponent::LifetimeComponent()
    : m_lifetime(-1.0f) // �f�t�H���g�͉i���i���̒l�j
    , m_expired(false)
    , m_onExpiredCallback(nullptr)
{
}

ComponentID LifetimeComponent::GetID() const
{
    return ComponentID::Life;
}

void LifetimeComponent::SetLifetime(float lifetimeInSeconds)
{
    m_lifetime = lifetimeInSeconds;
    // �V�����������ݒ肳�ꂽ��A�����t���O�����Z�b�g
    m_expired = (m_lifetime == 0.0f);
}

bool LifetimeComponent::IsExpired() const
{
    return m_expired;
}


void LifetimeComponent::Update(float deltaTime)
{
    // ���Ɏ������s���Ă���A�܂��͉i���i���̒l�j�̏ꍇ�͉������Ȃ�
    if (m_expired || m_lifetime < 0.0f)
    {
        return;
    }

    m_lifetime -= deltaTime;

    // �������s�����u�Ԃ̏���
    if (m_lifetime <= 0.0f)
    {
        m_expired = true;

        // �J�X�^���̃R�[���o�b�N���ݒ肳��Ă���΁A������Ăяo��
        if (m_onExpiredCallback)
        {
            m_onExpiredCallback();
        }
        else
        {
            // �R�[���o�b�N�����ݒ�̏ꍇ�̃f�t�H���g����F�I�[�i�[���A�N�e�B�u�ɂ���
            // GetOwner()��shared_ptr��Ԃ��̂ŁAnullptr�`�F�b�N�����S
            if (auto owner = GetOwner())
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