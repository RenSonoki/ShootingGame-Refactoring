#pragma once
#include "UIElement.h"
#include "Color.h" // �����ColorUtil���g�p
#include <string>

// UI�p�̃e�L�X�g�v�f��\���N���X
class UIText : public UIElement
{
public:
    explicit UIText(const std::wstring& text = L"", unsigned int color = ColorUtil::White, int fontSize = 20);
    virtual ~UIText() = default;

    // --- ��Ԑݒ� ---
    void SetText(const std::wstring& text);
    void SetColor(unsigned int color);
    void SetFontSizePx(int size);

    // --- ��Ԏ擾�iRenderer���`��Ɏg���j ---
    const std::wstring& GetText() const;
    unsigned int GetColor() const;
    int GetFontSizePx() const;

private:
    std::wstring m_text;
    unsigned int m_color;
    int m_fontSize; // Px�P��
};