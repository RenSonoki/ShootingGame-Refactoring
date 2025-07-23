#pragma once

#include "ComponentBase.h"
#include <functional>

/**
 * @class LifetimeComponent
 * @brief �G���e�B�e�B�̎������Ǘ����A�������s�������ɓ���̃A�N�V���������s����R���|�[�l���g
 */
class LifetimeComponent : public ComponentBase
{
public:
    /**
     * @brief �R���X�g���N�^
     */
    LifetimeComponent();

    ComponentID GetID() const override;

    /**
     * @brief ���t���[���̍X�V�B���������Z���A0�ȉ��ɂȂ����珈�������s���܂��B
     * @param deltaTime �O�̃t���[������̌o�ߎ��ԁi�b�j
     */
    void Update(float deltaTime) override;

    /**
     * @brief ������b���Őݒ肵�܂��B
     * @param lifetimeInSeconds �����i�b�j�B���̒l��ݒ肷��Ɖi�����܂��B
     */
    void SetLifetime(float lifetimeInSeconds);

    /**
     * @brief �������s�������ǂ�����Ԃ��܂��B
     * @return true�̏ꍇ�A�������s���Ă���
     */
    bool IsExpired() const;

    /**
     * @brief �������s�������ɌĂяo�����R�[���o�b�N�֐���ݒ肵�܂��B
     * @param callback ���s�������������L�q�����֐�
     */
    void SetOnExpired(const std::function<void()>& callback);

private:
    float m_lifetime;
    bool m_expired;

    // �������s�������Ɏ��s�����J�X�^������
    std::function<void()> m_onExpiredCallback;
};