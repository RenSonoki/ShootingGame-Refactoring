#pragma once

#include "UIComponent.h"
#include "IUIInteractable.h"
#include "SpriteRenderer.h" // SpriteRenderer を利用する
#include <functional>
#include <string>
#include <memory>

class UIButton : public UIComponent, public IUIInteractable
{
public:
	// ボタンの状態を表す列挙型
    enum class ButtonState
    {
        Normal,
        Hovered,
        Pressed
    };

    UIButton(const std::wstring& normalPath,
        const std::wstring& hoverPath = L"",
        const std::wstring& pressedPath = L"");

    // IUIInteractable の実装
    void UpdateInteraction() override;
    void OnClick() override {} // 今回はSetOnClickで直接コールバックを登録

    // UIComponent の実装
    void Draw(int targetScreen = -1) override;

    void SetOnClick(std::function<void()> callback);
    ButtonState GetState() const;

private:
    // intハンドルではなく、SpriteRendererを状態ごとに持つ
    SpriteRenderer m_rendererNormal;
    SpriteRenderer m_rendererHover;
    SpriteRenderer m_rendererPressed;

    ButtonState m_state = ButtonState::Normal;
    std::function<void()> m_onClick;

    bool IsMouseOver() const;
    bool m_previousMouseDown = false;
};