#include "UIPanel.h"
#include "UIElement.h" // UIElement �̒�`���C���N���[�h
#include <algorithm> // std::sort �̂��߂ɃC���N���[�h

UIPanel::UIPanel() = default;

// �� �C���_: �f�X�g���N�^�́u��`�v�������Ɉړ�����
// ���̏ꏊ�ł� UIElement �̊��S�Ȓ�`�������Ă��邽�߁A
// m_children ������ unique_ptr �͈��S�ɒ��g��j���ł���B
UIPanel::~UIPanel() = default;

void UIPanel::AddChild(std::unique_ptr<UIElement> child)
{
    if (child)
    {
        m_children.push_back(std::move(child));
        m_isZOrderDirty = true; // �� ���P��: �q�v�f���ǉ����ꂽ�̂ōă\�[�g���K�v
    }
}

const std::vector<std::unique_ptr<UIElement>>& UIPanel::GetChildren() const
{
    return m_children;
}

// �� �C���_: deltaTime������ǉ�
void UIPanel::UpdateLogic(float deltaTime)
{
    if (!IsVisible()) return;

    // �܂��������g�̃��W�b�N���X�V
    UIElement::UpdateLogic(deltaTime);

    // ���Ɏq�v�f�̃��W�b�N���X�V
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->UpdateLogic(deltaTime);
        }
    }
}

// �� �ǉ�: Interaction�X�V�̐Ӗ���������ɕ���
void UIPanel::UpdateInteraction()
{
    if (!IsVisible()) return;

    // �܂��������g�̃C���^���N�V�������X�V
    UIElement::UpdateInteraction();

    // ���Ɏq�v�f�̃C���^���N�V�������X�V
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->UpdateInteraction();
        }
    }
}


void UIPanel::Draw() const
{
    if (!IsVisible()) return;

    // �܂��������g��`��i�p�l���ɔw�i�F�Ȃǂ�����ꍇ�j
    UIElement::Draw();

    // �� ���P��: Z�I�[�_�[�Ń\�[�g���ĕ`�悷��
    // const_cast���g���Ă��܂����A����̓����o�[�ϐ��̃t���O���X�V���邽�߂����ŁA
    // �I�u�W�F�N�g�̊O�����猩����Ԃ͕ύX���Ȃ����߁A�_���I�ɂ�const����ۂ��Ă��܂��B
    if (m_isZOrderDirty)
    {
        auto& children_ref = const_cast<std::vector<std::unique_ptr<UIElement>>&>(m_children);
        std::sort(children_ref.begin(), children_ref.end(),
            [](const std::unique_ptr<UIElement>& a, const std::unique_ptr<UIElement>& b) {
                return a->GetZOrder() < b->GetZOrder();
            });
        const_cast<UIPanel*>(this)->m_isZOrderDirty = false;
    }

    // Z�I�[�_�[���Ɏq�v�f��`��
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
    // ���g�̉�����ݒ�
    UIElement::SetVisible(visible);

    // ���ׂĂ̎q�v�f�̉������ċA�I�ɐݒ�
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->SetVisible(visible);
        }
    }
}