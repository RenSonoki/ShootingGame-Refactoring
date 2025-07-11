#include "UISystem.h"
#include "Entity.h"
#include "UIComponent.h"
#include "IUILogicUpdatable.h"
#include "IUIInteractable.h"
#include "DxLib.h"

void UISystem::RegisterEntity(const std::shared_ptr<Entity>& entity)
{
    if (entity && entity->GetComponent<UIComponent>())
    {
        m_entities.push_back(entity);
        m_isDirty = true; // ���X�g���ύX���ꂽ�̂ŁA�_�[�e�B�t���O�𗧂Ă�
    }
}

void UISystem::UnregisterEntity(const std::shared_ptr<Entity>& entity)
{
    if (!entity) return;
    std::erase_if(m_entities, [&](const std::weak_ptr<Entity>& wp)
        {
        return wp.expired() || wp.lock() == entity;
        });
    m_isDirty = true;
}

void UISystem::Update()
{
    // ���X�g�ɕύX������΁A�R���|�[�l���g�̃L���b�V�����X�V
    if (m_isDirty)
    {
        RefreshComponents();
    }

    // �L���b�V�����ꂽ�R���|�[�l���g�̃��W�b�N���X�V
    for (const auto& comp : m_cachedComponents)
    {
        if (comp && comp->IsActive() && comp->IsVisible())
        {
            if (auto updatable = std::dynamic_pointer_cast<IUILogicUpdatable>(comp))
            {
                updatable->UpdateLogic();
            }
            if (auto interactable = std::dynamic_pointer_cast<IUIInteractable>(comp))
            {
                interactable->UpdateInteraction();
            }
        }
    }
}

void UISystem::Draw(int targetScreen)
{
    // ���X�g�ɕύX������΁A�L���b�V���̍X�V�ƃ\�[�g���s��
    if (m_isDirty)
    {
        RefreshComponents();
    }

    // �\�[�g�ς݂̃L���b�V����`��
    for (const auto& comp : m_cachedComponents)
    {
        if (comp && comp->IsActive() && comp->IsVisible())
        {
            comp->Draw(targetScreen);
        }
    }
}

void UISystem::Clear()
{
    m_entities.clear();
    m_cachedComponents.clear();
    m_isDirty = true;
}

void UISystem::SetLayerDepth(int depth) { m_layerDepth = depth; }
int UISystem::GetLayerDepth() const { return m_layerDepth; }

void UISystem::RefreshComponents()
{
    m_cachedComponents.clear();

    // �����ȃG���e�B�e�B�����X�g���珜�����AUIComponent�����W
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
        [this](const std::weak_ptr<Entity>& wp)
        {
            if (wp.expired()) {
                return true; // �����؂�̃|�C���^�͏���
            }
            auto entity = wp.lock();
            // �G���e�B�e�B����UIComponent���擾���ăL���b�V���ɒǉ�
            // ��1�G���e�B�e�B1UIComponent��O��Ƃ���ȈՎ���
            if (auto uiComp = entity->GetComponent<UIComponent>())
            {
                m_cachedComponents.push_back(uiComp);
            }
            return false;
        }), m_entities.end());

    SortComponents();
    m_isDirty = false;
}

void UISystem::SortComponents()
{
    std::sort(m_cachedComponents.begin(), m_cachedComponents.end(),
        [](const std::shared_ptr<UIComponent>& a, const std::shared_ptr<UIComponent>& b)
        {
            if (!a) return false;
            if (!b) return true;
            return a->GetZOrder() < b->GetZOrder();
        });
}