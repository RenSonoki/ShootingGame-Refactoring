#pragma once
#include "UIElement.h"
#include <string>

// UI�p�̐ÓI�ȉ摜�v�f��\���N���X
class UIImage : public UIElement
{
public:
    explicit UIImage(const std::wstring& imagePath);
    virtual ~UIImage() = default;

    // Draw��Update�Ȃǂ̃��W�b�N�́A���N���X�ł���UIElement��
    // ������Renderer���i�ɈϏ����Ă���邽�߁A���̃N���X�Ɏ����͕s�v�B
};