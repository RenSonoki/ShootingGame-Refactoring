#pragma once

#include "UIComponent.h"
#include "IUIInteractable.h"
#include "SpriteRenderer.h" // SpriteRenderer �𗘗p����
#include <functional>
#include <string>
#include <memory>

class UIButton : public UIComponent, public IUIInteractable
{
public:
	// �{�^���̏�Ԃ�\���񋓌^
    enum class ButtonState
    {
        Normal,
        Hovered,
        Pressed
    };

    UIButton(const std::wstring& normalPath,
        const std::wstring& hoverPath = L"",
        const std::wstring& pressedPath = L"");

    // IUIInteractable �̎���
    void UpdateInteraction() override;
    void OnClick() override {} // �����SetOnClick�Œ��ڃR�[���o�b�N��o�^

    // UIComponent �̎���
    void Draw(int targetScreen = -1) override;

    void SetOnClick(std::function<void()> callback);
    ButtonState GetState() const;

private:
    // int�n���h���ł͂Ȃ��ASpriteRenderer����Ԃ��ƂɎ���
    SpriteRenderer m_rendererNormal;
    SpriteRenderer m_rendererHover;
    SpriteRenderer m_rendererPressed;

    ButtonState m_state = ButtonState::Normal;
    std::function<void()> m_onClick;

    bool IsMouseOver() const;
    bool m_previousMouseDown = false;
};