#include "Entity.h"
#include "ComponentBase.h"
#include "LogicComponent.h"
#include "DrawComponent.h"

// �ÓI�����o�ϐ��̏�����
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
    // �R���|�[�l���g�̌^�����L�[�ɂ��ă}�b�v�ɓo�^
    // typeid(*component) �ŁA�|�C���^���w����̎��ۂ̌^�����擾����
    m_components[typeid(*component)] = component;

    // �R���|�[�l���g�ɏ��L�҂ł��鎩�g��������
    component->SetOwner(this);

    // �œK���p���X�g�ւ̒ǉ�
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

    // ���ׂẴR���|�[�l���g��Start���Ăяo��
    for(auto const& [type, comp] : m_components)
    {
        comp->Start();
    }

    // ���ׂĂ̎q�G���e�B�e�B��Start���ċA�I�ɌĂяo��
    for (auto& child : m_children)
    {
        child->Start();
    }
}

void Entity::Update(float deltaTime)
{
    if (!m_active) return;

    // �A�N�e�B�u�ȃ��W�b�N�R���|�[�l���g���X�V
    for (auto& logic : m_logicComponents)
    {
        if (logic->IsActive())
        {
            logic->Update(deltaTime);
        }
    }

    // ���ׂĂ̎q�G���e�B�e�B���ċA�I�ɍX�V
    for (auto& child : m_children)
    {
        child->Update(deltaTime);
    }
}

void Entity::Draw()
{
    if (!m_active) return;

    // �A�N�e�B�u�ȕ`��R���|�[�l���g��`��
    for (auto& draw : m_drawComponents)
    {
        if (draw->IsActive())
        {
            draw->Draw();
        }
    }

    // ���ׂĂ̎q�G���e�B�e�B���ċA�I�ɕ`��
    for (auto& child : m_children)
    {
        child->Draw();
    }
}