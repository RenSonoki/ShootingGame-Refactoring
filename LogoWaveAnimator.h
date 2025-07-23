#pragma once
#include "UIAnimator.h"

/**
 * @class LogoWaveAnimator
 * @brief UI�v�f���T�C���g�ŏ㉺�ɗh�炷��̓I�ȃA�j���[�^�[
 */
class LogoWaveAnimator : public UIAnimator
{
public:
    LogoWaveAnimator();

    // IUIAnimator�C���^�[�t�F�[�X�̎���
    void Update(const UIElement* owner, Transform2D& transform, float deltaTime) override;

    // �A�j���[�V�����̃p�����[�^��ݒ肷�郁�\�b�h
    void Setup(float baseY, float amplitude, float frequency);

private:
    // �A�j���[�V�����p�p�����[�^
    float m_baseY;
    float m_amplitude;
    float m_frequency;

    // �����^�C�}�[
    float m_time;
};