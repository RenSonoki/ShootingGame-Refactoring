#pragma once

#include "UIComponent.h"
#include <string>

// UI ��ɕ������`�悷�邽�߂̃R���|�[�l���g
// NOTE: �����I�ɂ�ResourceManager���g�p���ăt�H���g���Ǘ����邱�Ƃ�����
class UIText : public UIComponent
{
public:
    explicit UIText(const std::wstring& text = L"", unsigned int color = 0);

    // �`��i���z��ʑΉ��j
    void Draw(int targetScreen = -1) override;

    // ��Ԑݒ�
    void SetText(const std::wstring& text);
    void SetColor(unsigned int color);
    void SetFontSizePx(int size); // �T�C�Y�i�s�N�Z���j�P�ʂŎw��

    // ��Ԏ擾
    const std::wstring& GetText() const;
    unsigned int GetColor() const;
    int GetFontSizePx() const;

private:
    std::wstring m_text;
    unsigned int m_color;
    int m_fontSize; // Px�P��
};