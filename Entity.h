#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "ComponentBase.h"

// Entity自身もshared_ptrで管理されることを想定し、
// 安全に自身のshared_ptrを取得できるようにする
class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity();
    virtual ~Entity() = default;

    // --- コンポーネント管理 ---

    // コンポーネントを型とコンストラクタ引数を指定して、Entity内部で生成・追加する
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args);

    // 高速なマップ検索でコンポーネントを取得する
    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    // 指定した型のコンポーネントを持っているか確認する
    template<typename T>
    bool HasComponent() const;

    // --- ライフサイクル ---
    void Start();
    void Update(float deltaTime);
    void Draw() const;

    // --- ゲッター/セッター ---
    int GetID() const;

    bool IsActive() const;
    void SetActive(bool value);

    const std::wstring& GetTag() const;
    void SetTag(const std::wstring& tag);

private:
    // EntityのユニークID生成用
    static int s_nextID;
    int m_entityID;

    bool m_active = true;
    bool m_started = false;
    std::wstring m_tag;

    // 全てのコンポーネントを保持するリスト（更新ループ用）
    std::vector<std::shared_ptr<IComponent>> m_components;

    // 高速検索用のマップ (ComponentID -> Component)
    std::unordered_map<ComponentID, std::shared_ptr<IComponent>> m_componentMap;
};

// --- テンプレート実装 ---
template<typename T, typename... Args>
std::shared_ptr<T> Entity::AddComponent(Args&&... args)
{
    // 指定された型のコンポーネントがすでに追加されていないかチェック（任意）
    // assert(!HasComponent<T>() && "Component type already exists.");

    // 新しいコンポーネントを生成
    // std::forwardで引数を完全に転送
    auto newComponent = std::make_shared<T>(std::forward<Args>(args)...);

    // IComponentへのポインタにキャスト
    auto componentBase = std::static_pointer_cast<IComponent>(newComponent);

    // 所有者を設定 (enable_shared_from_this を使って安全にポインタを渡す)
    componentBase->SetOwner(shared_from_this());

    // リストと高速検索用マップの両方に追加
    m_components.push_back(componentBase);
    m_componentMap[newComponent->GetID()] = componentBase;

    // もしEntityがすでにStart済みなら、新しいコンポーネントのStartも即座に呼ぶ
    if (m_started)
    {
        newComponent->Start();
    }

    return newComponent;
}

template<typename T>
std::shared_ptr<T> Entity::GetComponent() const
{
    // 各コンポーネントクラスで定義された静的IDを使ってマップを検索
    auto it = m_componentMap.find(T::ID);
    if (it != m_componentMap.end())
    {
        // 見つかったら、それを派生クラスの型(T)に安全にキャストして返す
        return std::static_pointer_cast<T>(it->second);
    }
    return nullptr;
}

template<typename T>
bool Entity::HasComponent() const
{
    // countを使えば、キーの存在を高速にチェックできる
    return m_componentMap.count(T::ID) > 0;
}