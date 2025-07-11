#include "SpriteRenderer.h"
#include "ResourceManager.h"  // ResourceManager を利用するためにインクルード
#include "ResourceTraits.h"   // ImageTag を利用するためにインクルード
#include "DxLib.h"

SpriteRenderer::SpriteRenderer(const std::wstring& path)
{
    if (!path.empty())
    {
        Load(path);
    }
}

void SpriteRenderer::Load(const std::wstring& path)
{
    // DXライブラリの関数を直接呼ぶ代わりに、ResourceManagerに依頼する
    // これにより、画像の読み込みがキャッシュされ、メモリ効率が向上する
    m_handle = ResourceManager::Instance().Get<ImageTag>(path);

    if (m_handle != -1)
    {
        // ハンドルさえ取得できれば、画像サイズは取得できる
        GetGraphSize(m_handle, &m_originalWidth, &m_originalHeight);
    }
    else
    {
        m_originalWidth = 0;
        m_originalHeight = 0;
    }
}

void SpriteRenderer::Draw(const Transform2D& transform, bool visible) const
{
    if (!visible || m_handle == -1)
    {
        return;
    }

    VECTOR2 pos = transform.GetPosition();
    VECTOR2 scale = transform.GetScale();
    float rotation = transform.GetRotation();
    VECTOR2 pivot = transform.GetPivot();

    // Transform2Dのpivot情報を使って、回転・拡縮の中心座標を計算
    float centerX = static_cast<float>(m_originalWidth * pivot.x);
    float centerY = static_cast<float>(m_originalHeight * pivot.y);

    // 座標をfloatで扱えるDrawRotaGraphFやDrawRotaGraph2Fの使用を推奨
    DrawRotaGraph2F(
        pos.x, pos.y,
        centerX, centerY,
        scale.x, // 拡縮率（Yスケールは反映されない点に注意）
        static_cast<double>(rotation), // 回転角度（ラジアン）
        m_handle, // グラフィックハンドル
        TRUE // 透明色を透過
    );
}

int SpriteRenderer::GetOriginalWidth() const { return m_originalWidth; }
int SpriteRenderer::GetOriginalHeight() const { return m_originalHeight; }
int SpriteRenderer::GetHandle() const { return m_handle; }