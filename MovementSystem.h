#pragma once
#include <vector>
#include <memory>

// �O���錾
class Entity;

/**
 * @class MovementSystem
 * @brief TransformComponent�̑��x�Ɋ�Â��āA�G���e�B�e�B�̈ʒu���X�V����V�X�e��
 */
class MovementSystem
{
public:
    // EntitySystem���Ǘ�����S�G���e�B�e�B�̃��X�g���󂯎���ď������s��
    void Update(const std::vector<std::shared_ptr<Entity>>& entities, float deltaTime);
};