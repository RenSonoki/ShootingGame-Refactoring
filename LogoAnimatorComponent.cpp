//#include "LogoAnimatorComponent.h"
//#include "Entity.h"
//#include "UIComponent.h" // UIComponent��T�����߂ɃC���N���[�h
//#include "Transform2D.h"
//#include <cmath> // sinf
//#include <cassert>
//
//LogoAnimatorComponent::LogoAnimatorComponent(float baseY, float amplitude, float frequency)
//    : m_baseY(baseY)
//    , m_amplitude(amplitude)
//    , m_frequency(frequency)
//{
//}
//
//void LogoAnimatorComponent::Start()
//{
//    // �I�[�i�[�G���e�B�e�B����UIComponent��T���A����Transform���擾����
//    auto uiComponent = GetOwner()->GetComponent<UIComponent>();
//    assert(uiComponent != nullptr && "LogoAnimatorComponent requires a UIComponent on the same entity.");
//
//    m_transform = &uiComponent->GetTransform();
//}
//
//void LogoAnimatorComponent::Update(float deltaTime)
//{
//    if (!m_transform) return;
//
//    // ���Ԃ��o�ߎ���(deltaTime)�Ői�߂�
//    m_time += deltaTime;
//
//    // sin�̊p�x���v�Z
//    float angle = m_time * m_frequency;
//
//    // Y���W�̃I�t�Z�b�g���v�Z
//    float offsetY = std::sinf(angle) * m_amplitude;
//
//    VECTOR2 pos = m_transform->GetPosition();
//    pos.y = m_baseY + offsetY;
//    m_transform->SetPosition(pos);
//}
//
//void LogoAnimatorComponent::SetBaseY(float baseY)
//{
//    m_baseY = baseY;
//}
//
//void LogoAnimatorComponent::SetAmplitude(float amplitude)
//{
//    m_amplitude = amplitude;
//}
//
//void LogoAnimatorComponent::SetFrequency(float frequency)
//{
//    m_frequency = frequency;
//}