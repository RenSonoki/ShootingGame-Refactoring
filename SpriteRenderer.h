#pragma once

#include <string>
#include "Transform2D.h" // 描画時の座標情報として利用

// スプライト描画に特化した、再利用可能な汎用ユーティリティクラス
class SpriteRenderer
{
public:
    SpriteRenderer() = default;
    explicit SpriteRenderer(const std::wstring& path);
    virtual ~SpriteRenderer() = default;

    // 画像をロードする（ResourceManager経由）
    void Load(const std::wstring& path);

    // 指定されたTransform情報に基づいて描画する
    void Draw(const Transform2D& transform, bool visible = true) const;

    // 画像の元サイズを取得
    int GetOriginalWidth() const;
    int GetOriginalHeight() const;

    // DXライブラリのグラフィックハンドルを取得
    int GetHandle() const;

private:
    int m_handle = -1;
    int m_originalWidth = 0;
    int m_originalHeight = 0;
};