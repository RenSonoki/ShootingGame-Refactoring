#pragma once

#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <typeindex>
#include <algorithm>

// 前方宣言
class IComponent;
class ComponentBase;
class LogicComponent;
class DrawComponent;
class UIComponent;

// 
class Entity
{
public:
    Entity();
    virtual ~Entity() = default;

    // IDと状態管理
    int GetID() const;

	// アクティブ状態の取得と設定
    bool IsActive() const;
    void SetActive(bool value);

    // タグ機能
    void SetTag(const std::wstring& tag);
    const std::wstring& GetTag() const;

    // 親子構造（3Dシーン用）
    void SetParent(Entity* parent);
    Entity* GetParent() const;
    const std::vector<std::shared_ptr<Entity>>& GetChildren() const;
    void AddChild(std::shared_ptr<Entity> child);

    // コンポーネント管理
    void AddComponent(const std::shared_ptr<ComponentBase>& component);

    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    template<typename T>
    void RemoveComponent();

    // 特定の型のコンポーネントリストを直接取得する
    const std::vector<std::shared_ptr<UIComponent>>& GetUIComponents() const;

    // ライフサイクル
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Draw();

private:
    static int s_nextID;
    int m_entityID;
    bool m_active = true;
    bool m_started = false;

    Entity* m_parent = nullptr;
    std::vector<std::shared_ptr<Entity>> m_children;
    std::wstring m_tag;

    // 全コンポーネントを型で高速検索するためのマップ
    std::unordered_map<std::type_index, std::shared_ptr<ComponentBase>> m_components;

    // 型で事前分類されたリスト
    std::vector<std::shared_ptr<LogicComponent>> m_logicComponents;
    std::vector<std::shared_ptr<DrawComponent>> m_drawComponents;
    std::vector<std::shared_ptr<UIComponent>> m_uiComponents;
};

// --- テンプレートの定義 ---

template<typename T>
std::shared_ptr<T> Entity::GetComponent() const
{
    auto it = this->m_components.find(typeid(T));
    if (it != this->m_components.end())
    {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
}

template<typename T>
void Entity::RemoveComponent()
{
    auto it = this->m_components.find(typeid(T));
    if (it == this->m_components.end()) return;

    auto compToRemove = it->second;
    this->m_components.erase(it);

    // 各専門リストからも削除
    if (auto logic = std::dynamic_pointer_cast<LogicComponent>(compToRemove)) {
        std::erase(this->m_logicComponents, logic);
    }
    if (auto draw = std::dynamic_pointer_cast<DrawComponent>(compToRemove)) {
        std::erase(this->m_drawComponents, draw);
    }
    if (auto ui = std::dynamic_pointer_cast<UIComponent>(compToRemove)) {
        std::erase(this->m_uiComponents, ui);
    }
}