#include "UISystem.h"
#include "UIElement.h"
#include "UIPanel.h" // CollectRenderables�Ŏg������
#include <algorithm>
#include <DxLib.h>

// �R���X�g���N�^�ƃf�X�g���N�^�������Œ�`
UISystem::UISystem() = default;
UISystem::~UISystem() = default;

void UISystem::AddElement(std::unique_ptr<UIElement> element)
{
    if (element)
    {
        m_rootElements.push_back(std::move(element));
    }
}

void UISystem::Update(float deltaTime)
{
    for (const auto& element : m_rootElements)
    {
        if (element && element->IsVisible())
        {
            element->UpdateLogic(deltaTime);
            element->UpdateInteraction();
        }
    }
}

void UISystem::Draw() const
{
    // 1. �`��Ώۂ����X�g�ɏW�߂� (�ύX�Ȃ�)
    std::vector<UIElement*> renderList;
    renderList.reserve(m_rootElements.size() * 2); // ���O�ɑ��߂Ɋm��
    for (const auto& element : m_rootElements)
    {
        if (element && element->IsVisible())
        {
            CollectRenderables(element.get(), renderList);
        }
    }
    // 2. Z�I�[�_�[�Ń\�[�g (�ύX�Ȃ�)
    std::sort(renderList.begin(), renderList.end(),
        [](const UIElement* a, const UIElement* b) {
            return a->GetZOrder() < b->GetZOrder();
        });

    // ������ �������B��̕`��ݒ�̊Ǘ��ꏊ ������

    // 3. UI�`��̊J�n�O�ɁA�`��ݒ�����Z�b�g���ݒ�
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    SetUseZBufferFlag(FALSE);
    SetWriteZBufferFlag(FALSE);

    // 4. �\�[�g���ꂽ�����ŁA�SUI��`��
    for (const auto* element : renderList)
    {
        element->Draw();
    }

    // 5. UI�`��̏I����ɁA�`��ݒ���f�t�H���g�ɖ߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    SetUseZBufferFlag(TRUE);
    SetWriteZBufferFlag(TRUE);
}

void UISystem::Clear()
{
    m_rootElements.clear();
}

void UISystem::SetLayerDepth(int depth) { m_layerDepth = depth; }
int UISystem::GetLayerDepth() const { return m_layerDepth; }

// private
void UISystem::CollectRenderables(UIElement* element, std::vector<UIElement*>& renderList) const
{
    if (!element || !element->IsVisible()) return;

    // �`��@�\�����v�f�iRenderer���Z�b�g����Ă���Ȃǁj�݂̂����X�g�ɒǉ�
    if (element->HasRenderer())
    {
        renderList.push_back(element);
    }

    // �����v�f���p�l���Ȃ�A���̎q�v�f���ċA�I�Ɏ��W
    if (auto panel = dynamic_cast<UIPanel*>(element))
    {
        for (const auto& child : panel->GetChildren())
        {
            CollectRenderables(child.get(), renderList);
        }
    }
}