#pragma once

#include <string>
#include "Transform2D.h" // �`�掞�̍��W���Ƃ��ė��p

// �X�v���C�g�`��ɓ��������A�ė��p�\�Ȕėp���[�e�B���e�B�N���X
class SpriteRenderer
{
public:
    SpriteRenderer() = default;
    explicit SpriteRenderer(const std::wstring& path);
    virtual ~SpriteRenderer() = default;

    // �摜�����[�h����iResourceManager�o�R�j
    void Load(const std::wstring& path);

    // �w�肳�ꂽTransform���Ɋ�Â��ĕ`�悷��
    void Draw(const Transform2D& transform, bool visible = true) const;

    // �摜�̌��T�C�Y���擾
    int GetOriginalWidth() const;
    int GetOriginalHeight() const;

    // DX���C�u�����̃O���t�B�b�N�n���h�����擾
    int GetHandle() const;

private:
    int m_handle = -1;
    int m_originalWidth = 0;
    int m_originalHeight = 0;
};