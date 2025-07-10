#include "Entity.h"
#include "ComponentBase.h"
#include "LogicComponent.h"
#include "DrawComponent.h"

// 静的メンバ変数の初期化
int Entity::s_nextID = 0;

Entity::Entity()
    : m_entityID(s_nextID++), m_tag(L"")
{
}

Entity::~Entity()
{
}

int Entity::GetID() const { return m_entityID; }
bool Entity::IsActive() const { return m_active; }
void Entity::SetActive(bool value) { m_active = value; }

void Entity::SetTag(const std::wstring& tag) { m_tag = tag; }
const std::wstring& Entity::GetTag() const { return m_tag; }

void Entity::SetParent(Entity* parent) { m_parent = parent; }
Entity* Entity::GetParent() const { return m_parent; }

const std::vector<std::shared_ptr<Entity>>& Entity::GetChildren() const { return m_children; }

void Entity::AddChild(std::shared_ptr<Entity> child)
{
    child->SetParent(this);
    m_children.push_back(child);
}

void Entity::AddComponent(const std::shared_ptr<ComponentBase>& component)
{
    // コンポーネントの型情報をキーにしてマップに登録
    // typeid(*component) で、ポインタが指す先の実際の型情報を取得する
    m_components[typeid(*component)] = component;

    // コンポーネントに所有者である自身を教える
    component->SetOwner(this);

    // 最適化用リストへの追加
    if (auto logic = std::dynamic_pointer_cast<LogicComponent>(component))
    {
        m_logicComponents.push_back(logic);
    }
    if (auto draw = std::dynamic_pointer_cast<DrawComponent>(component))
    {
        m_drawComponents.push_back(draw);
    }
}

void Entity::Start()
{
    if (m_started || !m_active) return;
    m_started = true;

    // すべてのコンポーネントのStartを呼び出す
    for(auto const& [type, comp] : m_components)
    {
        comp->Start();
    }

    // すべての子エンティティのStartを再帰的に呼び出す
    for (auto& child : m_children)
    {
        child->Start();
    }
}

void Entity::Update(float deltaTime)
{
    if (!m_active) return;

    // アクティブなロジックコンポーネントを更新
    for (auto& logic : m_logicComponents)
    {
        if (logic->IsActive())
        {
            logic->Update(deltaTime);
        }
    }

    // すべての子エンティティを再帰的に更新
    for (auto& child : m_children)
    {
        child->Update(deltaTime);
    }
}

void Entity::Draw()
{
    if (!m_active) return;

    // アクティブな描画コンポーネントを描画
    for (auto& draw : m_drawComponents)
    {
        if (draw->IsActive())
        {
            draw->Draw();
        }
    }

    // すべての子エンティティを再帰的に描画
    for (auto& child : m_children)
    {
        child->Draw();
    }
}