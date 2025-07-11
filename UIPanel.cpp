#include "UIPanel.h"

UIPanel::UIPanel() = default;

void UIPanel::AddChild(const std::shared_ptr<UIComponent>& child)
{
    if (child)
    {
        // �q�R���|�[�l���g�ɂ��A���̃p�l���Ɠ����I�[�i�[�G���e�B�e�B��ݒ肷��
        // ����ɂ��A�q�R���|�[�l���g��UISystem�ɐ������F�������
        m_children.push_back(child);
    }
}

const std::vector<std::shared_ptr<UIComponent>>& UIPanel::GetChildren() const
{
    return m_children;
}

void UIPanel::Draw(int targetScreen)
{
    if (!IsVisible())
    {
        return;
    }

    // �p�l�����g���`�悷��ׂ����̂�����΁A�����ɋL�q���܂��B
    // �i��F�p�l���̔w�i�摜��`�悷��Ȃǁj
    //
    // �q�v�f�̕`��́AUISystem��Z�\�[�g���Đ������s���Ă���邽�߁A
    // �����Ŏq�v�f��Draw()���Ăяo���K�v�͂���܂���B
    // ����ɂ��AUI�v�f����d�ɕ`�悳������h���܂��B
}

void UIPanel::SetVisible(bool visible)
{
    // �܂��A�������g��Visible��Ԃ����N���X�̃��\�b�h�Őݒ�
    UIComponent::SetVisible(visible);

    // ���ɁA�Ǘ����Ă��邷�ׂĂ̎q�v�f��Visible��Ԃ��ꊇ�ŕύX����
    for (const auto& child : m_children)
    {
        if (child)
        {
            child->SetVisible(visible);
        }
    }
}