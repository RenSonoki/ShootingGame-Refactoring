#include "SimpleSpriteRenderer.h"
#include "UIElement.h" // �I�[�i�[��Transform�Ȃǂ��擾���邽�߂ɕK�v

SimpleSpriteRenderer::SimpleSpriteRenderer(const std::wstring& imagePath)
{
    // �R���X�g���N�^�ŁA�����SpriteRenderer�ɉ摜�����[�h������
    m_spriteRenderer.Load(imagePath);
}

void SimpleSpriteRenderer::Draw(const UIElement* owner) const
{
    if (!owner) return;

    // �I�[�i�[����Transform�����擾���A�����SpriteRenderer�ɕ`����Ϗ�
    m_spriteRenderer.Draw(owner->GetTransform());
}