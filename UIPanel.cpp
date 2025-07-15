#include "UIPanel.h"

UIPanel::UIPanel() = default;

void UIPanel::AddChild(std::unique_ptr<UIElement> child)
{
    if (child)
    {
        // unique_ptr�̏��L�����x�N�^�[�Ɉړ�������
        m_children.push_back(std::move(child));
    }
}

void UIPanel::UpdateLogic()
{
    // ���g���A�N�e�B�u�łȂ���΁A�q�v�f���X�V���Ȃ�
    if (!IsVisible()) return;

    // �܂��A�������g�̃��W�b�N���X�V�i���N���X�̏������Ăԁj
    UIElement::UpdateLogic();

    // ���ɁA�Ǘ����Ă��邷�ׂĂ̎q�v�f�̃��W�b�N���X�V����
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->UpdateLogic();
            child->UpdateInteraction(); // �C���^���N�V�������X�V
        }
    }
}

void UIPanel::Draw()
{
    // ���g����\���Ȃ�A�q�v�f���`�悵�Ȃ�
    if (!IsVisible()) return;

    // �܂��A�������g�̕`����s���i�p�l���̔w�i�Ȃǁj
    // �i���N���X��Draw�́A���g�ɐݒ肳�ꂽRenderer���Ăяo���j
    UIElement::Draw();

    // ���ɁA�Ǘ����Ă��邷�ׂĂ̎q�v�f���`�悷��
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->Draw();
        }
    }
}

void UIPanel::SetVisible(bool visible)
{
    // �܂��A�������g��Visible��Ԃ�ݒ�
    UIElement::SetVisible(visible);

    // ���ɁA�Ǘ����Ă��邷�ׂĂ̎q�v�f��Visible��Ԃ��ꊇ�ŕύX����
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->SetVisible(visible);
        }
    }
}