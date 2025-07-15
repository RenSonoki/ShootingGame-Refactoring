#include "SpriteRenderer.h"
#include "ResourceManager.h" // 各自のヘッダーパスに調整
#include "ResourceTraits.h"
#include <DxLib.h>

// -------------------------------------------------------------------
// RAIIを活用して描画設定を管理するヘルパークラス
// 「設定を変更し、処理を行い、設定を元に戻す」という考え方
// このクラスのオブジェクトが生存している間だけ描画設定が変更される
// -------------------------------------------------------------------
class ScopedDrawSettings
{
public:
    // コンストラクタで新しい設定を適用
    ScopedDrawSettings(unsigned int color, int blendMode, int blendParam)
    {
        // DXライブラリの描画設定を変更
        SetDrawBright(ColorUtil::GetR(color), ColorUtil::GetG(color), ColorUtil::GetB(color));
        SetDrawBlendMode(blendMode, blendParam);
    }

    // デストラクタで自動的にデフォルト設定に戻す
    ~ScopedDrawSettings()
    {
        SetDrawBright(255, 255, 255);
        SetDrawBlendMode(BlendMode::None, 255);
    }

    // このクラスはリソース管理専用なので、コピーとムーブを禁止する
    ScopedDrawSettings(const ScopedDrawSettings&) = delete;
    ScopedDrawSettings& operator=(const ScopedDrawSettings&) = delete;
};


// --- SpriteRendererの実装 ---

SpriteRenderer::SpriteRenderer(const std::wstring& path)
{
    if (!path.empty())
    {
        Load(path);
    }
}

void SpriteRenderer::Load(const std::wstring& path)
{
    m_handle = ResourceManager::Instance().Get<ImageTag>(path);
    if (m_handle != -1)
    {
        GetGraphSize(m_handle, &m_originalWidth, &m_originalHeight);
    }
    else
    {
        m_originalWidth = 0;
        m_originalHeight = 0;
    }
}

void SpriteRenderer::Draw(const Transform2D& transform, bool visible, unsigned int color, int blendMode, int blendParam) const
{
    if (!visible || m_handle == -1)
    {
        return;
    }

    // RAIIクラスのオブジェクトをスタックに生成
    // この関数のスコープを抜けるときに、デストラクタが呼ばれ、設定が自動で元に戻る
    const ScopedDrawSettings settings(color, blendMode, blendParam);

    // --- 描画処理本体 ---
    const VECTOR2 pos = transform.GetPosition();
    const VECTOR2 scale = transform.GetScale();
    const float rotation = transform.GetRotation();
    const VECTOR2 pivot = transform.GetPivot();

    const float centerX = static_cast<float>(m_originalWidth * pivot.x);
    const float centerY = static_cast<float>(m_originalHeight * pivot.y);

    DrawRotaGraph3F(
        pos.x, pos.y,
        centerX, centerY,
        scale.x,
        scale.y,
        static_cast<double>(rotation),
        m_handle,
        TRUE
    );
    // ここで settings オブジェクトが破棄され、デストラクタが呼ばれる
}

int SpriteRenderer::GetOriginalWidth() const { return m_originalWidth; }
int SpriteRenderer::GetOriginalHeight() const { return m_originalHeight; }
int SpriteRenderer::GetHandle() const { return m_handle; }