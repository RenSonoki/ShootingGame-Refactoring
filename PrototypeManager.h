#pragma once// �C���ς�

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include "IEntityPrototype.h"

// Prototype �p�^�[����p�����G���e�B�e�B�����Ǘ��N���X�iSingleton�j
class PrototypeManager
{
public:
    static PrototypeManager& Instance();

    // �v���g�^�C�v�o�^�iID: wstring�j
    void Register(const std::wstring& id, std::shared_ptr<IEntityPrototype> prototype);

    // �����i�ʏ�j��FClone()
    std::shared_ptr<Entity> Create(const std::wstring& id) const;

    // �ʒu�t�������i��F�e��G�̏����X�|�[���ʒu�j
    std::shared_ptr<Entity> CreateAt(const std::wstring& id, const VECTOR& pos) const;

    // ���݊m�F�i���S�ȃ`�F�b�N�Ɏg�p�j
    bool Has(const std::wstring& id) const;

    // �o�^�ς� ID �ꗗ�擾�iUI�p�Ȃǁj
    std::vector<std::wstring> GetAllIDs() const;

    // �S�폜�i�V�[�����Z�b�g���Ȃǁj
    void Clear();

private:
    PrototypeManager() = default;
    PrototypeManager(const PrototypeManager&) = delete;
    PrototypeManager& operator=(const PrototypeManager&) = delete;

    std::unordered_map<std::wstring, std::shared_ptr<IEntityPrototype>> m_prototypes;
};