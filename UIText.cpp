#include "UIText.h"
#include "DxLib.h"

UIText::UIText(const std::wstring& text, unsigned int color)
    : m_text(text)
    , m_color(color == 0 ? ::GetColor(255, 255, 255) : color)  // ← グローバル呼び出し
    , m_fontSize(20)
{
}

void UIText::Draw(int targetScreen)
{
    if (!IsVisible()) return;

    // 現在のフォントサイズを保持
    int oldFontSize = GetFontSize();
    SetFontSize(m_fontSize);

    auto pos = GetTransform().GetPosition();

    if (targetScreen != -1)
    {
        int prev = GetDrawScreen();
        SetDrawScreen(targetScreen);
        DrawString(pos.x, pos.y, m_text.c_str(), m_color);
        SetDrawScreen(prev);
    }
    else
    {
        DrawString(pos.x, pos.y, m_text.c_str(), m_color);
    }

    SetFontSize(oldFontSize);
}

void UIText::SetText(const std::wstring& text)
{
    m_text = text;
}

void UIText::SetColor(unsigned int color)
{
    m_color = color;
}

void UIText::SetFontSizePx(int size)
{
    m_fontSize = size;
}

const std::wstring& UIText::GetText() const
{
    return m_text;
}

unsigned int UIText::GetColor() const
{
    return m_color;
}

int UIText::GetFontSizePx() const
{
    return m_fontSize;
}