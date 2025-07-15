#include "UIText.h"
#include "TextRenderer.h" // ���g�ɑ������镔�i
#include <memory>

UIText::UIText(const std::wstring& text, unsigned int color, int fontSize)
    : m_text(text)
    , m_color(color)
    , m_fontSize(fontSize)
{
    // ���g�́u�`��v�U�镑����S�����镔�i�𐶐����A��������
    auto renderer = std::make_unique<TextRenderer>();
    SetRenderer(std::move(renderer));
}

void UIText::SetText(const std::wstring& text) { m_text = text; }
void UIText::SetColor(unsigned int color) { m_color = color; }
void UIText::SetFontSizePx(int size) { m_fontSize = size; }
const std::wstring& UIText::GetText() const { return m_text; }
unsigned int UIText::GetColor() const { return m_color; }
int UIText::GetFontSizePx() const { return m_fontSize; }