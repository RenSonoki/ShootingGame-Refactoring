#pragma once
#include "UIRenderer.h"     // ����������`����UIRenderer�C���^�[�t�F�[�X
#include "SpriteRenderer.h"   // ���Ȃ���������`�惆�[�e�B���e�B
#include "Color.h"      // ���Ȃ���������F���[�e�B���e�B
#include <string>

// �摜�`��Ƃ����u�U�镑���v����̓I�Ɏ�������N���X
class ImageRenderer : public UIRenderer
{
public:
    // �R���X�g���N�^�ŉ摜�̃p�X���󂯎��
    explicit ImageRenderer(const std::wstring& path);
    virtual ~ImageRenderer() = default;

    // --- UIRenderer�C���^�[�t�F�[�X�̖񑩎������� ---
    // �y�C���_�z������ const UIElement* owner �ɕύX
    void Draw(const UIElement* owner) const override;

    // --- ���̐U�镑���ŗL�̑��� ---
    void SetColor(unsigned int color);
    unsigned int GetColor() const;
    int GetOriginalWidth() const;
    int GetOriginalHeight() const;

private:
    // SpriteRenderer�𕔕i�Ƃ��ď��L�i�R���|�W�V�����j
    SpriteRenderer m_sprite;

    // ���̐U�镑���ŗL�̃f�[�^
    unsigned int m_color = ColorUtil::White;
};