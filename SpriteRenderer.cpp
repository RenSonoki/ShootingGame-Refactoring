#include "SpriteRenderer.h"
#include "ResourceManager.h"  // ResourceManager �𗘗p���邽�߂ɃC���N���[�h
#include "ResourceTraits.h"   // ImageTag �𗘗p���邽�߂ɃC���N���[�h
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
    // DX���C�u�����̊֐��𒼐ڌĂԑ���ɁAResourceManager�Ɉ˗�����
    // ����ɂ��A�摜�̓ǂݍ��݂��L���b�V������A���������������シ��
    m_handle = ResourceManager::Instance().Get<ImageTag>(path);

    if (m_handle != -1)
    {
        // �n���h�������擾�ł���΁A�摜�T�C�Y�͎擾�ł���
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

    // Transform2D��pivot�����g���āA��]�E�g�k�̒��S���W���v�Z
    float centerX = static_cast<float>(m_originalWidth * pivot.x);
    float centerY = static_cast<float>(m_originalHeight * pivot.y);

    // ���W��float�ň�����DrawRotaGraphF��DrawRotaGraph2F�̎g�p�𐄏�
    DrawRotaGraph2F(
        pos.x, pos.y,
        centerX, centerY,
        scale.x, // �g�k���iY�X�P�[���͔��f����Ȃ��_�ɒ��Ӂj
        static_cast<double>(rotation), // ��]�p�x�i���W�A���j
        m_handle, // �O���t�B�b�N�n���h��
        TRUE // �����F�𓧉�
    );
}

int SpriteRenderer::GetOriginalWidth() const { return m_originalWidth; }
int SpriteRenderer::GetOriginalHeight() const { return m_originalHeight; }
int SpriteRenderer::GetHandle() const { return m_handle; }