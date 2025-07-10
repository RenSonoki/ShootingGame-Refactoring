#pragma once

#include "IEntityPrototype.h"
#include <string>
#include <memory>
#include "DxLib.h" // VECTOR�̂���

// �e�G���e�B�e�B�̃v���g�^�C�v�i�݌v�}�j
class BulletPrototype : public IEntityPrototype
{
public:
    BulletPrototype(const std::wstring& modelPath, float speed, float lifetimeInSeconds);

    // Prototype�C���^�[�t�F�[�X�̎���
    // Clone�̃V�O�l�`�����A�����p�I�Ȃ��̂ɕύX
    std::shared_ptr<Entity> Clone(const VECTOR& position, const VECTOR& direction) const;

    // IEntityPrototype�̉��z�֐����I�[�o�[���C�h���邽�߂Ɏc�����A���܂�g��Ȃ�
    std::shared_ptr<Entity> Clone() const override;
    std::shared_ptr<Entity> CloneWithTransform(const VECTOR& position) const override;

    std::wstring GetName() const override;
    std::wstring GetCategory() const override;

    // (�Q�b�^�[/�Z�b�^�[�͕ύX�Ȃ��A������lifetime�̌^��float��)
    void SetSpeed(float speed);
    void SetLifetime(float lifetimeInSeconds);
    // ...

private:
    std::wstring m_modelPath;
    float m_speed;
    float m_lifetimeInSeconds;
};