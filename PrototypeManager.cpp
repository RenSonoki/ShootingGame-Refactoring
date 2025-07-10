#include "PrototypeManager.h"
#include <stdexcept>

PrototypeManager& PrototypeManager::Instance()
{
    static PrototypeManager instance;
    return instance;
}

void PrototypeManager::Register(const std::wstring& id, std::shared_ptr<IEntityPrototype> prototype)
{
    m_prototypes[id] = prototype;
}

std::shared_ptr<Entity> PrototypeManager::Create(const std::wstring& id) const
{
    auto it = m_prototypes.find(id);
    if (it != m_prototypes.end())
    {
        return it->second->Clone();
    }
    throw std::runtime_error("PrototypeManager::Create: Unknown prototype ID");
}

std::shared_ptr<Entity> PrototypeManager::CreateAt(const std::wstring& id, const VECTOR& pos) const
{
    auto it = m_prototypes.find(id);
    if (it != m_prototypes.end())
    {
        return it->second->CloneWithTransform(pos);
    }
    throw std::runtime_error("PrototypeManager::CreateAt: Unknown prototype ID");
}

bool PrototypeManager::Has(const std::wstring& id) const
{
    return m_prototypes.count(id) > 0;
}

std::vector<std::wstring> PrototypeManager::GetAllIDs() const
{
    std::vector<std::wstring> result;
    for (const auto& [id, _] : m_prototypes)
    {
        result.push_back(id);
    }
    return result;
}

void PrototypeManager::Clear()
{
    m_prototypes.clear();
}
