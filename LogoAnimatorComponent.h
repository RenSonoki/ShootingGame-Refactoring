#pragma once

#include "LogicComponent.h"
#include <memory>

// �O���錾
class Transform2D; 

// UI�ɔg�̂悤�ȏ㉺����^����A�j���[�V�����R���|�[�l���g
class LogoAnimatorComponent : public LogicComponent
{
public:
    LogoAnimatorComponent(float baseY, float amplitude, float frequency);

    // ���C�t�T�C�N�����\�b�h
    void Start() override;
    void Update(float deltaTime) override;

    // �p�����[�^�ύX�p�̃Z�b�^�[
    void SetBaseY(float baseY);
    void SetAmplitude(float amplitude);
    void SetFrequency(float frequency);

private:
    // shared_ptr�ł͂Ȃ����|�C���^�ŃL���b�V������i���L�͂��Ȃ����߁j
    Transform2D* m_transform = nullptr;

    float m_baseY;
    float m_amplitude;
    float m_frequency;

    // int�ł͂Ȃ�float�̃^�C�}�[�ɕύX
    float m_time = 0.0f;
};