#pragma once

#include "LogicComponent.h"
#include <functional>

// �������Ǘ�����R���|�[�l���g
class LifetimeComponent : public LogicComponent
{
public:
    // ������b���Ŏw��
    explicit LifetimeComponent(float lifetimeInSeconds);

    void Update(float deltaTime) override;

    // ������b���Őݒ�
    void SetLifetime(float lifetimeInSeconds);
    bool IsExpired() const;

    // �������s�������̃R�[���o�b�N��ݒ�
	// �������s���铮����R���|�[�l���g�ݒ葤�Œ�`�ł���悤�ɂ����: �G�t�F�N�g�̍폜�Ȃ�)
    void SetOnExpired(const std::function<void()>& callback);

private:
    // ������b��(float)�ŊǗ�
    float m_lifetime = 0.0f;
    bool m_expired = false;

    // �R�[���o�b�N�֐�
    std::function<void()> m_onExpiredCallback;
};