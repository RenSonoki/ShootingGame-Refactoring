#pragma once

#include <vector>
#include <memory>
#include <unordered_set> // vector�̑����unordered_set���g�p
#include "Entity.h"

// �V�[���ɑ��݂���S�ẴG���e�B�e�B�̃��C�t�T�C�N���i�����A�X�V�A�`��A�j���j���Ǘ�����N���X
class EntitySystem
{
public:
    EntitySystem() = default;
    ~EntitySystem() = default;

    void AddEntity(std::shared_ptr<Entity> entity);
    void RemoveEntity(std::shared_ptr<Entity> entity);

    void Start();
    void Update(float deltaTime);
    void Draw();
    void Clear();

    const std::vector<std::shared_ptr<Entity>>& GetEntities() const;
    
private:
    std::vector<std::shared_ptr<Entity>> m_entities;

    // �폜�҂����X�g��unordered_set�ɕύX
    std::unordered_set<std::shared_ptr<Entity>> m_pendingRemoval;

    bool m_started = false;
};