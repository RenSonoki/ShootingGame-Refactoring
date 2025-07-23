#pragma once
#include <vector>
#include <memory>
#include <string>

class Entity; // �O���錾

// �V�[���ɑ��݂���S�Ắu�Q�[�����[���h�́v�G���e�B�e�B�̃��C�t�T�C�N�����Ǘ�����N���X
class EntitySystem
{
public:
    EntitySystem() = default;
    ~EntitySystem() = default;

    EntitySystem(const EntitySystem&) = delete;
    EntitySystem& operator=(const EntitySystem&) = delete;

    // �� �C���_: �\�z�ς݂̃G���e�B�e�B���󂯎��悤�ɃV�O�l�`����ύX
    void AddEntity(std::shared_ptr<Entity> entity);
    void RemoveEntity(std::shared_ptr<Entity> entity);
    const std::vector<std::shared_ptr<Entity>>& GetEntities() const;

    size_t GetEntityCount() const;

    void StartAll();
    void UpdateAll(float deltaTime);
    void DrawAll() const; // �� const ��ǉ�
    void Clear();

private:
    void ApplyPendingActions();

    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<Entity>> m_pendingAdd;
    // �� ���P��: �폜�Ώۂ̓|�C���^�ŏ\��
    std::vector<Entity*> m_pendingRemoval;

    bool m_isUpdating = false;
};