#pragma once
#include "UIRenderer.h"
#include "SpriteRenderer.h"
#include <string>

// �{�^���́u�`��v�U�镑����S������N���X
class ButtonRenderer : public UIRenderer
{
public:
    ButtonRenderer(const std::wstring& normalPath,
        const std::wstring& hoverPath,
        const std::wstring& pressedPath);

    // UIRenderer�C���^�[�t�F�[�X�̎���
    void Draw(const UIElement* owner) const override;

    // UIButton�����g�̃T�C�Y��m�邽�߂ɁA�ʏ�摜�̃T�C�Y��Ԃ�
    VECTOR2 GetNormalSpriteSize() const;

private:
    SpriteRenderer m_rendererNormal;
    SpriteRenderer m_rendererHover;
    SpriteRenderer m_rendererPressed;
};