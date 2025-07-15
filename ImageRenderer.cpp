#include "ImageRenderer.h"
#include "UIElement.h" // �I�[�i�[�̏����擾���邽�߂ɕK�v

ImageRenderer::ImageRenderer(const std::wstring& path)
{
    // ������SpriteRenderer�ɉ摜�̓ǂݍ��݂��˗�
    m_sprite.Load(path);
}

// �y�C���_�z������ const UIElement* owner �ɕύX
void ImageRenderer::Draw(const UIElement* owner) const
{
    // �I�[�i�[�����Ȃ��A�܂��͔�\���Ȃ�`�悵�Ȃ�
    if (!owner || !owner->IsVisible())
    {
        return;
    }

    // �I�[�i�[����Transform�����擾
    const Transform2D& transform = owner->GetTransform();

    // ������SpriteRenderer�ɁA�擾����Transform�Ǝ��g�����F��n���ĕ`����˗�
    m_sprite.Draw(transform, true, m_color);
}

void ImageRenderer::SetColor(unsigned int color)
{
    m_color = color;
}

unsigned int ImageRenderer::GetColor() const
{
    return m_color;
}

int ImageRenderer::GetOriginalWidth() const
{
    return m_sprite.GetOriginalWidth();
}

int ImageRenderer::GetOriginalHeight() const
{
    return m_sprite.GetOriginalHeight();
}