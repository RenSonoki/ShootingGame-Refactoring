#pragma once
#include "UIElement.h" // �V�������N���X
#include <vector>
#include <memory>

// UI�v�f���K�w�I�ɃO���[�v�����邽�߂̃p�l���N���X
// ���g��UIElement�ł���A�q�Ƃ��ĕ�����UIElement�����L�ł���
class UIPanel : public UIElement
{
public:
    UIPanel();
    virtual ~UIPanel() = default;

    // �q�v�f��ǉ�����i���L�����p�l���Ɉڂ�j
    void AddChild(std::unique_ptr<UIElement> child);

    // --- UIElement�̉��z�֐����I�[�o�[���C�h ---

    // ���g�ƁA�S�Ă̎q�v�f�̃��W�b�N���X�V����
    void UpdateLogic() override;

    // ���g�ƁA�S�Ă̎q�v�f��`�悷��
    void Draw() override;

    // ���g�ƁA�S�Ă̎q�v�f�̕\����Ԃ��ꊇ�Ő؂�ւ���
    void SetVisible(bool visible) override;

protected:
    // �p�l�������L����q�v�f�̃��X�g
    std::vector<std::unique_ptr<UIElement>> m_children;
};