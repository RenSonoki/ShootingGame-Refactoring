#pragma once
#include "UIRenderer.h"

// �e�L�X�g�́u�`��v�U�镑�����J�v�Z���������N���X
class TextRenderer : public UIRenderer
{
public:
    // UIRenderer�C���^�[�t�F�[�X������
    void Draw(const UIElement* owner) const override;
};