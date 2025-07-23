#include "Entity.h"
#include "IComponent.h"

// �ÓI�����o�ϐ��̎��̂��`
int Entity::s_nextID = 0;

Entity::Entity() : m_entityID(s_nextID++)
{
}

// --- �Q�b�^�[/�Z�b�^�[ ---
int Entity::GetID() const { return m_entityID; }
bool Entity::IsActive() const { return m_active; }
void Entity::SetActive(bool value) { m_active = value; }
const std::wstring& Entity::GetTag() const { return m_tag; }
void Entity::SetTag(const std::wstring& tag) { m_tag = tag; }

// --- ���C�t�T�C�N�� ---
void Entity::Start()
{
    if (m_started || !m_active) return;
    m_started = true;

    for (const auto& comp : m_components)
    {
        if (comp->IsActive())
        {
            comp->Start();
        }
    }
}

void Entity::Update(float deltaTime)
{
    if (!m_active) return;

    for (const auto& comp : m_components)
    {
        if (comp->IsActive())
        {
            comp->Update(deltaTime);
        }
    }
}

void Entity::Draw() const
{
    if (!m_active) return;

    for (const auto& comp : m_components)
    {
        if (comp->IsActive())
        {
            comp->Draw();
        }
    }
}