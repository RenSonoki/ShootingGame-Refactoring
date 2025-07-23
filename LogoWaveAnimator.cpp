#include "LogoWaveAnimator.h"
#include "UIElement.h"   // Update�̈����Ŏg��
#include "Transform2D.h" // Transform2D�𑀍삷�邽�߂ɕK�v
#include <cmath>         // sinf

LogoWaveAnimator::LogoWaveAnimator()
    : m_baseY(0.0f)
    , m_amplitude(10.0f)
    , m_frequency(1.0f)
    , m_time(0.0f)
{
}

void LogoWaveAnimator::Setup(float baseY, float amplitude, float frequency)
{
    m_baseY = baseY;
    m_amplitude = amplitude;
    m_frequency = frequency;
}

void LogoWaveAnimator::Update(const UIElement* owner, Transform2D& transform, float deltaTime)
{
    // �����^�C�}�[���X�V
    m_time += deltaTime;

    // �T�C���g���v�Z
    const float angle = m_time * m_frequency;
    const float offsetY = std::sinf(angle) * m_amplitude;

    // ���W���X�V
    VECTOR2 pos = transform.GetPosition();
    pos.y = m_baseY + offsetY;
    transform.SetPosition(pos);
}