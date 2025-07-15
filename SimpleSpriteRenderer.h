#pragma once
#include "UIRenderer.h"
#include "SpriteRenderer.h"
#include <string>

// �P���ȃX�v���C�g�`��́u�U�镑���v���J�v�Z���������N���X
class SimpleSpriteRenderer : public UIRenderer
{
public:
    explicit SimpleSpriteRenderer(const std::wstring& imagePath);

    // UIRenderer�C���^�[�t�F�[�X������
    void Draw(const UIElement* owner) const override;

private:
    // ���ۂ�DX���C�u�����̕`����s���N���X�����
    SpriteRenderer m_spriteRenderer;
};