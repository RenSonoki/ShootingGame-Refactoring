#include "UIButton.h"
#include "ButtonRenderer.h"
#include "ButtonInteractor.h"
#include <memory>

UIButton::UIButton(const std::wstring& normalPath,
    const std::wstring& hoverPath,
    const std::wstring& pressedPath)
{
    // ���g�̐U�镑����S������u���i�v�𐶐�
    auto renderer = std::make_unique<ButtonRenderer>(normalPath, hoverPath, pressedPath);
    auto interactor = std::make_unique<ButtonInteractor>();

    // �����������i�����g�ɑ�������
    SetRenderer(std::move(renderer));
    SetInteractor(std::move(interactor));
}

void UIButton::SetOnClick(std::function<void()> callback)
{
    m_onClick = std::move(callback);
}

void UIButton::InvokeOnClick()
{
    if (m_onClick) { m_onClick(); }
}

UIButton::ButtonState UIButton::GetState() const
{
    return m_state;
}

void UIButton::SetState(ButtonState newState)
{
    m_state = newState;
}

VECTOR2 UIButton::GetBoundingSize() const
{
    // ���g�����L����Renderer�ɃT�C�Y�̖₢���킹���Ϗ�����
    if (const auto* renderer = static_cast<const ButtonRenderer*>(m_renderer.get()))
    {
        return renderer->GetNormalSpriteSize();
    }
    return { 0.0f, 0.0f };
}