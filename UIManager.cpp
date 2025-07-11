#include "UIManager.h"

void UIManager::AddSystem(const std::string& name, const std::shared_ptr<UISystem>& system)
{
    if (system)
    {
        m_systems[name] = system;
    }
}

std::shared_ptr<UISystem> UIManager::GetSystem(const std::string& name) const
{
    auto it = m_systems.find(name);
    return (it != m_systems.end()) ? it->second : nullptr;
}

void UIManager::RemoveSystem(const std::string& name)
{
    m_systems.erase(name);
}

void UIManager::DrawAll(int targetScreen)
{
    // 1. �`��Ώۂ̃V�X�e�����ꎞ�I�ȃx�N�^�[�ɏW�߂�
    std::vector<std::shared_ptr<UISystem>> systemsToDraw;
    systemsToDraw.reserve(m_systems.size());
    for (const auto& pair : m_systems)
    {
        if (pair.second)
        {
            systemsToDraw.push_back(pair.second);
        }
    }

    // 2. ���C���[�[�x�Ɋ�Â��ă\�[�g����
    std::sort(systemsToDraw.begin(), systemsToDraw.end(),
        [](const std::shared_ptr<UISystem>& a, const std::shared_ptr<UISystem>& b)
        {
            // nullptr�`�F�b�N�ň��S�������߂�
            if (!a) return false;
            if (!b) return true;
            return a->GetLayerDepth() < b->GetLayerDepth();
        });

    // 3. �\�[�g���ꂽ�����ŕ`�悷��
    for (const auto& system : systemsToDraw)
    {
        system->Draw(targetScreen);
    }
}

void UIManager::UpdateAll()
{
    for (const auto& pair : m_systems)
    {
        const auto& system = pair.second;
        if (system)
        {
            system->Update();
        }
    }
}

void UIManager::Clear()
{
    m_systems.clear();
}