#pragma once
#include <string>
#include "Transform2D.h"
#include "Color.h"

// ブレンドモードを定数として定義
namespace BlendMode
{
    constexpr int None = 0;       // DX_BLENDMODE_NOBLEND
    constexpr int Alpha = 2;      // DX_BLENDMODE_ALPHA
    constexpr int Add = 1;        // DX_BLENDMODE_ADD
    constexpr int Subtract = 3;   // DX_BLENDMODE_SUB
    // 必要に応じて他のブレンドモードも追加
}

class SpriteRenderer
{
public:
    SpriteRenderer() = default;
    explicit SpriteRenderer(const std::wstring& path);
    virtual ~SpriteRenderer() = default;

    void Load(const std::wstring& path);

    // デフォルト引数をマジックナンバーから意味のある定数に変更
    void Draw(
        const Transform2D& transform,
        bool visible = true,
        unsigned int color = ColorUtil::White,
        int blendMode = BlendMode::Alpha, // 定数を使用
        int blendParam = 255
    ) const;

    int GetOriginalWidth() const;
    int GetOriginalHeight() const;
    int GetHandle() const;

private:
    int m_handle = -1;
    int m_originalWidth = 0;
    int m_originalHeight = 0;
};