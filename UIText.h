#pragma once

#include "UIComponent.h"
#include <string>

// UI 上に文字列を描画するためのコンポーネント
// NOTE: 将来的にはResourceManagerを使用してフォントを管理することを検討
class UIText : public UIComponent
{
public:
    explicit UIText(const std::wstring& text = L"", unsigned int color = 0);

    // 描画（仮想画面対応）
    void Draw(int targetScreen = -1) override;

    // 状態設定
    void SetText(const std::wstring& text);
    void SetColor(unsigned int color);
    void SetFontSizePx(int size); // サイズ（ピクセル）単位で指定

    // 状態取得
    const std::wstring& GetText() const;
    unsigned int GetColor() const;
    int GetFontSizePx() const;

private:
    std::wstring m_text;
    unsigned int m_color;
    int m_fontSize; // Px単位
};