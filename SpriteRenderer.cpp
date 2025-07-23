#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "ResourceTraits.h"
#include <utility>
#include <DxLib.h>

// --- SpriteRenderer�̎��� ---

SpriteRenderer::SpriteRenderer()
    : m_handle(-1), m_originalWidth(0), m_originalHeight(0),
    m_visible(true), m_color(ColorUtil::White), m_blendParam(255)
{
}

SpriteRenderer::SpriteRenderer(const std::wstring& path) : SpriteRenderer() { Load(path); }
SpriteRenderer::~SpriteRenderer() { Release(); }

// ���[�u�R���X�g���N�^
SpriteRenderer::SpriteRenderer(SpriteRenderer&& other) noexcept
    : m_handle(other.m_handle), m_originalWidth(other.m_originalWidth), m_originalHeight(other.m_originalHeight),
    m_visible(other.m_visible), m_color(other.m_color), m_blendParam(other.m_blendParam)
{
    other.m_handle = -1; // ���L�������[�u�����̂ŁA����͖�����
}

// ���[�u������Z�q
SpriteRenderer& SpriteRenderer::operator=(SpriteRenderer&& other) noexcept
{
    if (this != &other)
    {
        Release();
        m_handle = other.m_handle;
        m_originalWidth = other.m_originalWidth;
        m_originalHeight = other.m_originalHeight;
        m_visible = other.m_visible;
        m_color = other.m_color;
        m_blendParam = other.m_blendParam;

        other.m_handle = -1;
    }
    return *this;
}


bool SpriteRenderer::Load(const std::wstring& path)
{
    Release();
    m_handle = ResourceManager::Instance().Get<ImageTag>(path);
    if (m_handle != -1)
    {
        GetGraphSize(m_handle, &m_originalWidth, &m_originalHeight);
        return true;
    }
    return false;
}

void SpriteRenderer::Draw(const Transform2D& transform) const
{
    if (!m_visible || m_handle == -1) return;

    // �� �`��ݒ�͍s��Ȃ��I UISystem�Ɉ�C����

    // �F�̕ύX�����͌ʂɍs��
    SetDrawBright(ColorUtil::GetR(m_color), ColorUtil::GetG(m_color), ColorUtil::GetB(m_color));

    // �u�����h�̋�����ݒ�
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blendParam);

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
        TRUE, // �����L��
        FALSE
    );

    // �`���ɐF�𔒂ɖ߂�
    SetDrawBright(255, 255, 255);
}

// --- �Z�b�^�[�ƃQ�b�^�[�̎��� ---
void SpriteRenderer::SetVisible(bool visible) { m_visible = visible; }
void SpriteRenderer::SetColor(unsigned int color) { m_color = color; }
void SpriteRenderer::SetBlendParam(int blendParam) { m_blendParam = blendParam; }
int SpriteRenderer::GetOriginalWidth() const { return m_originalWidth; }
int SpriteRenderer::GetOriginalHeight() const { return m_originalHeight; }
int SpriteRenderer::GetHandle() const { return m_handle; }

void SpriteRenderer::Release()
{
    if (m_handle != -1)
    {
        m_handle = -1;
        m_originalWidth = 0;
        m_originalHeight = 0;
    }
}