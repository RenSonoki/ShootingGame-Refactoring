#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <algorithm>
#include "UISystem.h"

// ������ UI �V�X�e���i���C���[�j�𖼑O�ŊǗ����铝��}�l�[�W��
class UIManager
{
public:
    // UI���C���[�iUISystem�j��ǉ��E�o�^
    void AddSystem(const std::string& name, const std::shared_ptr<UISystem>& system);

    // ���O�Ń��C���[���擾
    std::shared_ptr<UISystem> GetSystem(const std::string& name) const;

    // �w�背�C���[���폜
    void RemoveSystem(const std::string& name);

    // �SUI���C���[��`��i���C���[�[�x���l���j
    void DrawAll(int targetScreen = -1);

    // �SUI���C���[���X�V
    void UpdateAll();

    // �S���C���[���폜�i�V�[���J�ڎ��Ȃǁj
    void Clear();

private:
    std::unordered_map<std::string, std::shared_ptr<UISystem>> m_systems;
};