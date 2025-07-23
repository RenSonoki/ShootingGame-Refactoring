#pragma once
#include "UISystem.h" // UISystem�̑O���錾�ł͂Ȃ��A���S�Ȓ�`���K�v
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <algorithm>

// ������UI�V�X�e���i���C���[�j�𖼑O�ŊǗ����铝��}�l�[�W��
class UIManager
{
public:
    // UI���C���[��ǉ��E�o�^�i���L����UIManager�Ɉړ�����j
    void AddSystem(const std::string& name, std::unique_ptr<UISystem> system);

    // ���O�Ń��C���[���擾�i���L���͓n���Ȃ����߁A���|�C���^��Ԃ��j
    UISystem* GetSystem(const std::string& name) const;

    // �w�背�C���[���폜
    void RemoveSystem(const std::string& name);

    // �SUI���C���[��`��i���C���[�[�x���l���j
    void DrawAll(); // �������폜

    // �SUI���C���[���X�V
    void UpdateAll(float deltaTime);

    // �S���C���[���폜
    void Clear();

private:
    // �y�C���_�zstd::unique_ptr�ŏ��L���𖾊m��
    std::unordered_map<std::string, std::unique_ptr<UISystem>> m_systems;
};