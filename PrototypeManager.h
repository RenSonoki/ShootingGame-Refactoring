#pragma once
#include "IEntityPrototype.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

// Prototype �p�^�[����p�����G���e�B�e�B�����Ǘ��N���X�iSingleton�j
class PrototypeManager
{
public:
    static PrototypeManager& Instance();

    // ���L�����ړ������邽�߁Aunique_ptr�Ńv���g�^�C�v���󂯎��
    void Register(const std::wstring& id, std::unique_ptr<IEntityPrototype> prototype);

    // �����i�ʏ�j
    std::shared_ptr<Entity> Create(const std::wstring& id) const;

    // �ʒu�t������
    std::shared_ptr<Entity> CreateAt(const std::wstring& id, const VECTOR& pos) const;

    // ���݊m�F
    bool Has(const std::wstring& id) const;

    // �o�^�ς� ID �ꗗ�擾
    std::vector<std::wstring> GetAllIDs() const;

    // �S�폜
    void Clear();

private:
    PrototypeManager() = default;
    PrototypeManager(const PrototypeManager&) = delete;
    PrototypeManager& operator=(const PrototypeManager&) = delete;

    // �y�C���zunique_ptr�Ńv���g�^�C�v��r���I�ɏ��L
    std::unordered_map<std::wstring, std::unique_ptr<IEntityPrototype>> m_prototypes;
};