#include "UIButton.h"
#include "DxLib.h"
#include "VirtualScreenManager.h" // IsMouseOverで必要

UIButton::UIButton(const std::wstring& normalPath,
    const std::wstring& hoverPath,
    const std::wstring& pressedPath)
{
    // 各SpriteRendererに画像をロードさせる
    m_rendererNormal.Load(normalPath);

    // パスが空なら、通常時の画像をコピーして使う
    m_rendererHover = hoverPath.empty() ? m_rendererNormal : SpriteRenderer(hoverPath);
    m_rendererPressed = pressedPath.empty() ? m_rendererNormal : SpriteRenderer(hoverPath);
}

void UIButton::UpdateInteraction()
{
    if (!IsVisible() || !IsActive())
    {
        // 非アクティブ時は状態をNormalに戻す
        m_state = ButtonState::Normal;
        return;
    }

    bool isOver = IsMouseOver();
    bool isDown = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    if (isOver)
    {
        m_state = isDown ? ButtonState::Pressed : ButtonState::Hovered;

        // マウスが上で、前のフレームで押されていて、今フレームで離された瞬間にクリックイベント発火
        if (m_previousMouseDown && !isDown && m_onClick)
        {
            m_onClick();
        }
    }
    else
    {
        m_state = ButtonState::Normal;
    }

    m_previousMouseDown = isDown;
}

void UIButton::Draw(int targetScreen)
{
    if (!IsVisible()) return;

    // 状態に応じて、担当のSpriteRendererに描画を依頼するだけ
    const SpriteRenderer* rendererToUse = &m_rendererNormal;
    switch (m_state)
    {
    case ButtonState::Hovered:
        rendererToUse = &m_rendererHover;
        break;
    case ButtonState::Pressed:
        rendererToUse = &m_rendererPressed;
        break;
    default:
        break;
    }

    // SpriteRendererのDrawは Transform を正しく扱ってくれる
    rendererToUse->Draw(GetTransform(), true);
}

void UIButton::SetOnClick(std::function<void()> callback)
{
    m_onClick = std::move(callback);
}

UIButton::ButtonState UIButton::GetState() const
{
    return m_state;
}

bool UIButton::IsMouseOver() const
{
    // Transform2D の Contains メソッドを使って正確な当たり判定を行う
    Vector2I mousePosInt = VirtualScreenManager::ConvertMousePositionToVirtual();
    VECTOR2 mousePos = { (float)mousePosInt.x, (float)mousePosInt.y };

    // ボタンのサイズは、通常時の画像のサイズを基準にする
    VECTOR2 size = {
        (float)m_rendererNormal.GetOriginalWidth(),
        (float)m_rendererNormal.GetOriginalHeight()
    };

    return GetTransform().Contains(mousePos, size);
}