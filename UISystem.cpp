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
        m_isDirty = true; // リストが変更されたので、ダーティフラグを立てる
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
    // リストに変更があれば、コンポーネントのキャッシュを更新
    if (m_isDirty)
    {
        RefreshComponents();
    }

    // キャッシュされたコンポーネントのロジックを更新
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
    // リストに変更があれば、キャッシュの更新とソートを行う
    if (m_isDirty)
    {
        RefreshComponents();
    }

    // ソート済みのキャッシュを描画
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

    // 無効なエンティティをリストから除去しつつ、UIComponentを収集
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
        [this](const std::weak_ptr<Entity>& wp)
        {
            if (wp.expired()) {
                return true; // 期限切れのポインタは除去
            }
            auto entity = wp.lock();
            // エンティティからUIComponentを取得してキャッシュに追加
            // ※1エンティティ1UIComponentを前提とする簡易実装
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