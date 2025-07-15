#pragma once
#include <string>
#include "Transform2D.h"
#include "Color.h"

// �u�����h���[�h��萔�Ƃ��Ē�`
namespace BlendMode
{
    constexpr int None = 0;       // DX_BLENDMODE_NOBLEND
    constexpr int Alpha = 2;      // DX_BLENDMODE_ALPHA
    constexpr int Add = 1;        // DX_BLENDMODE_ADD
    constexpr int Subtract = 3;   // DX_BLENDMODE_SUB
    // �K�v�ɉ����đ��̃u�����h���[�h���ǉ�
}

class SpriteRenderer
{
public:
    SpriteRenderer() = default;
    explicit SpriteRenderer(const std::wstring& path);
    virtual ~SpriteRenderer() = default;

    void Load(const std::wstring& path);

    // �f�t�H���g�������}�W�b�N�i���o�[����Ӗ��̂���萔�ɕύX
    void Draw(
        const Transform2D& transform,
        bool visible = true,
        unsigned int color = ColorUtil::White,
        int blendMode = BlendMode::Alpha, // �萔���g�p
        int blendParam = 255
    ) const;

    int GetOriginalWidth() const;
    int GetOriginalHeight() const;
    int GetHandle() const;

private:
    int m_handle = -1;
    int m_originalWidth = 0;
    int m_originalHeight = 0;
};