#include "UIElement.h"
#include "UIRenderer.h"
#include "UIInteractor.h"

void UIElement::SetVisible(bool visible) { m_isVisible = visible; }
bool UIElement::IsVisible() const { return m_isVisible; }

Transform2D& UIElement::GetTransform() { return m_transform; }
const Transform2D& UIElement::GetTransform() const { return m_transform; }

void UIElement::UpdateLogic()
{
    // ����A���W�b�N�X�V�p�̕��i��ǉ������ꍇ�A�����ŌĂяo��
}

void UIElement::UpdateInteraction()
{
    if (m_isVisible && m_interactor)
    {
        // Interactor�ɁA�I�[�i�[�ł��鎩�g(this)�ւ̃|�C���^��n��
        m_interactor->UpdateInteraction(this);
    }
}

void UIElement::Draw()
{
    if (m_isVisible && m_renderer)
    {
        // �y�C���_�zRenderer�ɁA�I�[�i�[�ł��鎩�g(this)�ւ̃|�C���^��n��
        m_renderer->Draw(this);
    }
}

const std::string& UIElement::GetName() const { return m_name; }
void UIElement::SetName(const std::string& name) { m_name = name; }

void UIElement::SetRenderer(std::unique_ptr<UIRenderer> renderer) { m_renderer = std::move(renderer); }
void UIElement::SetInteractor(std::unique_ptr<UIInteractor> interactor) { m_interactor = std::move(interactor); }