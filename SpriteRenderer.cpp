#include "SpriteRenderer.h"
#include "ResourceManager.h" // �e���̃w�b�_�[�p�X�ɒ���
#include "ResourceTraits.h"
#include <DxLib.h>

// -------------------------------------------------------------------
// RAII�����p���ĕ`��ݒ���Ǘ�����w���p�[�N���X
// �u�ݒ��ύX���A�������s���A�ݒ�����ɖ߂��v�Ƃ����l����
// ���̃N���X�̃I�u�W�F�N�g���������Ă���Ԃ����`��ݒ肪�ύX�����
// -------------------------------------------------------------------
class ScopedDrawSettings
{
public:
    // �R���X�g���N�^�ŐV�����ݒ��K�p
    ScopedDrawSettings(unsigned int color, int blendMode, int blendParam)
    {
        // DX���C�u�����̕`��ݒ��ύX
        SetDrawBright(ColorUtil::GetR(color), ColorUtil::GetG(color), ColorUtil::GetB(color));
        SetDrawBlendMode(blendMode, blendParam);
    }

    // �f�X�g���N�^�Ŏ����I�Ƀf�t�H���g�ݒ�ɖ߂�
    ~ScopedDrawSettings()
    {
        SetDrawBright(255, 255, 255);
        SetDrawBlendMode(BlendMode::None, 255);
    }

    // ���̃N���X�̓��\�[�X�Ǘ���p�Ȃ̂ŁA�R�s�[�ƃ��[�u���֎~����
    ScopedDrawSettings(const ScopedDrawSettings&) = delete;
    ScopedDrawSettings& operator=(const ScopedDrawSettings&) = delete;
};


// --- SpriteRenderer�̎��� ---

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

    // RAII�N���X�̃I�u�W�F�N�g���X�^�b�N�ɐ���
    // ���̊֐��̃X�R�[�v�𔲂���Ƃ��ɁA�f�X�g���N�^���Ă΂�A�ݒ肪�����Ō��ɖ߂�
    const ScopedDrawSettings settings(color, blendMode, blendParam);

    // --- �`�揈���{�� ---
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
    // ������ settings �I�u�W�F�N�g���j������A�f�X�g���N�^���Ă΂��
}

int SpriteRenderer::GetOriginalWidth() const { return m_originalWidth; }
int SpriteRenderer::GetOriginalHeight() const { return m_originalHeight; }
int SpriteRenderer::GetHandle() const { return m_handle; }