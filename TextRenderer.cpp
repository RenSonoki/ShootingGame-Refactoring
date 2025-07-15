#include "TextRenderer.h"
#include "UIText.h" // �I�[�i�[��UIText�ɃL���X�g���ăe�L�X�g�����擾���邽��
#include "DxLib.h"

// RAII�����p���ăt�H���g�T�C�Y�ݒ���Ǘ�����w���p�[�N���X
class ScopedFontSize
{
private:
    int m_oldFontSize;
public:
    // �R���X�g���N�^�ŐV�����t�H���g�T�C�Y��ݒ�
    explicit ScopedFontSize(int newSize)
    {
        m_oldFontSize = GetFontSize(); // ���݂̃t�H���g�T�C�Y���L��
        SetFontSize(newSize);          // �V�����T�C�Y�ɕύX
    }
    // �f�X�g���N�^�ŋL�����Ă������Â��t�H���g�T�C�Y�ɖ߂�
    ~ScopedFontSize()
    {
        SetFontSize(m_oldFontSize);
    }
    // �R�s�[�ƃ��[�u���֎~
    ScopedFontSize(const ScopedFontSize&) = delete;
    ScopedFontSize& operator=(const ScopedFontSize&) = delete;
};


void TextRenderer::Draw(const UIElement* owner) const
{
    // �I�[�i�[��UIText�Ƀ_�E���L���X�g
    const auto* textElement = static_cast<const UIText*>(owner);
    if (!textElement) return;

    // RAII�N���X���g���A���̊֐��̃X�R�[�v���ł̂݃t�H���g�T�C�Y��ύX����
    const ScopedFontSize scopedFont(textElement->GetFontSizePx());

    // �`��ɕK�v�ȏ����I�[�i�[����擾
    const auto& transform = textElement->GetTransform();
    const auto& text = textElement->GetText();
    const unsigned int color = textElement->GetColor();
    const VECTOR2 pos = transform.GetPosition();

    // DX���C�u�����̕`��֐����Ăяo��
    DrawString(static_cast<int>(pos.x), static_cast<int>(pos.y), text.c_str(), color);
}