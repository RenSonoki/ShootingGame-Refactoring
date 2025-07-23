#include "UIManager.h"

// �y�C���_�z������unique_ptr�ɕύX���Astd::move�ŏ��L�����ڏ�
void UIManager::AddSystem(const std::string& name, std::unique_ptr<UISystem> system)
{
    if (system)
    {
        m_systems[name] = std::move(system);
    }
}

// �y�C���_�z�߂�l�𐶃|�C���^�ɕύX
UISystem* UIManager::GetSystem(const std::string& name) const
{
    auto it = m_systems.find(name);
    // .get()��unique_ptr���Ǘ����鐶�|�C���^���擾���ĕԂ�
    return (it != m_systems.end()) ? it->second.get() : nullptr;
}

void UIManager::RemoveSystem(const std::string& name)
{
    m_systems.erase(name);
}

void UIManager::DrawAll() // �y�C���_�z�������폜
{
    // 1. �`��Ώۂ̃V�X�e���i���|�C���^�j���ꎞ�I�ȃx�N�^�[�ɏW�߂�
    std::vector<UISystem*> systemsToDraw;
    systemsToDraw.reserve(m_systems.size());
    for (const auto& pair : m_systems)
    {
        if (pair.second)
        {
            systemsToDraw.push_back(pair.second.get());
        }
    }

    // 2. ���C���[�[�x�Ɋ�Â��ă\�[�g����
    std::sort(systemsToDraw.begin(), systemsToDraw.end(),
        [](const UISystem* a, const UISystem* b)
        {
            if (!a) return false;
            if (!b) return true;
            return a->GetLayerDepth() < b->GetLayerDepth();
        });

    // 3. �\�[�g���ꂽ�����ŕ`�悷��
    for (const auto* system : systemsToDraw)
    {
        system->Draw(); // UISystem��Draw()�ɂ͈����͕s�v
    }
}

void UIManager::UpdateAll(float deltaTime)
{
    for (const auto& pair : m_systems)
    {
        if (pair.second)
        {
            pair.second->Update(deltaTime);
        }
    }
}

void UIManager::Clear()
{
    m_systems.clear();
}