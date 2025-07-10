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

// Entity(GameObject)を作成するためのクラス
class Entity
{
public:
    Entity();
    virtual ~Entity();

    int GetID() const;

    bool IsActive() const;
    void SetActive(bool value);

    void SetTag(const std::wstring& tag);
    const std::wstring& GetTag() const;

    void SetParent(Entity* parent);
    Entity* GetParent() const;

    const std::vector<std::shared_ptr<Entity>>& GetChildren() const;
    void AddChild(std::shared_ptr<Entity> child);

    void AddComponent(const std::shared_ptr<ComponentBase>& component);

    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    template<typename T>
    void RemoveComponent();

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
	std::unordered_map<std::type_index, std::shared_ptr<ComponentBase>> m_components;   // 直接探索出来るようにunordered_mapを使用
    std::vector<std::shared_ptr<LogicComponent>> m_logicComponents;
    std::vector<std::shared_ptr<DrawComponent>> m_drawComponents;
    std::wstring m_tag;
};

// --- コンポーネントの追加メソッドの実装 ---

template<typename T>
std::shared_ptr<T> Entity::GetComponent() const
{
    auto it = m_components.find(typeid(T));
    if (it != m_components.end())
    {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
}

// --- コンポーネントの削除メソッドの実装 ---

template<typename T>
void Entity::RemoveComponent()
{
    auto it = m_components.find(typeid(T));
    if (it == m_components.end())
    {
        return;
    }

    auto compToRemove = it->second;
    m_components.erase(it);

    if (auto logic = std::dynamic_pointer_cast<LogicComponent>(compToRemove))
    {
        std::erase(m_logicComponents, logic);
    }
    if (auto draw = std::dynamic_pointer_cast<DrawComponent>(compToRemove))
    {
        std::erase(m_drawComponents, draw);
    }
}