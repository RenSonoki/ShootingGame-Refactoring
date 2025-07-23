#include "UIElement.h"
#include "UIRenderer.h"
#include "UIInteractor.h"
#include "UIAnimator.h"      // �� �C���_: UIAnimator�̒�`��ǂݍ���
#include "Transform2D.h"     // Transform2D��VECTOR2�̒�`�ɕK�v

// �� �C���_: �R���X�g���N�^�́u��`�v�������Ɉړ�
UIElement::UIElement() = default;

// �� �C���_: �f�X�g���N�^�́u��`�v�������Ɉړ�
// ���̎��_�ł́AUIAnimator�Ȃǂ̌^�́u���S�Ȍ^�v�ɂȂ��Ă��邽�߁A
// unique_ptr�͈��S�ɃI�u�W�F�N�g��j���ł���B
UIElement::~UIElement() = default;

void UIElement::SetVisible(bool visible) { m_isVisible = visible; }
bool UIElement::IsVisible() const { return m_isVisible; }

Transform2D& UIElement::GetTransform() { return m_transform; }
const Transform2D& UIElement::GetTransform() const { return m_transform; }

// �� �C���_: deltaTime �������Ƃ��Ď󂯎��悤�ɕύX
void UIElement::UpdateLogic(float deltaTime)
{
    // �A�j���[�^�[���ݒ肳��Ă���΁A�A�j���[�V�������W�b�N���X�V
    if (m_animator)
    {
        // �����Ŏ󂯎����deltaTime��n��
        m_animator->Update(this, m_transform, deltaTime);
    }
}

void UIElement::UpdateInteraction()
{
    if (m_isVisible && m_interactor)
    {
        m_interactor->UpdateInteraction(this);
    }
}

void UIElement::Draw() const
{
    if (m_isVisible && m_renderer)
    {
        m_renderer->Draw(this);
    }
}

const std::string& UIElement::GetName() const { return m_name; }
void UIElement::SetName(const std::string& name) { m_name = name; }

void UIElement::SetZOrder(int order) { m_zOrder = order; }
int UIElement::GetZOrder() const { return m_zOrder; }

VECTOR2 UIElement::GetBoundingSize() const
{
    // �f�t�H���g����
    return { 0.0f, 0.0f };
}

bool UIElement::HasRenderer() const
{
    // m_renderer (unique_ptr) ��nullptr�łȂ���΁A�`��@�\�������Ă���Ɣ��f���܂�
    return m_renderer != nullptr;
}

void UIElement::SetRenderer(std::unique_ptr<UIRenderer> renderer) { m_renderer = std::move(renderer); }
void UIElement::SetInteractor(std::unique_ptr<UIInteractor> interactor) { m_interactor = std::move(interactor); }
void UIElement::SetAnimator(std::unique_ptr<UIAnimator> animator) { m_animator = std::move(animator); }