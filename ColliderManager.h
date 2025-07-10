#pragma once

#include "ICollisionComponent.h"
#include <vector>
#include <memory>

// �V���O���g���Ƃ��āA�o�^���ꂽ�S�ẴR���C�_�[���Ǘ�����N���X
class ColliderManager
{
public:
    static ColliderManager& Instance();

    // AddCollider���폜���A�o�^/�����ɓ���
    void Register(const std::shared_ptr<ICollisionComponent>& collider);
    void Unregister(const std::shared_ptr<ICollisionComponent>& collider);

    void CheckAllCollisions();
    void Clear();

private:
    std::vector<std::shared_ptr<ICollisionComponent>> m_colliders;

    // �x���폜�̂��߂́u�폜�҂����X�g�v��ǉ�
    std::vector<std::shared_ptr<ICollisionComponent>> m_pendingRemoval;

    ColliderManager() = default;
    ~ColliderManager() = default;
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;

    // ���ۂ̍폜�������s���w���p�[�֐�
    void ApplyPendingRemovals();
};