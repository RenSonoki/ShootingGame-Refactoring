#pragma once
#include "ICollisionComponent.h"
#include "CollisionSystemTypes.h"
#include <vector>
#include <memory>
#include <map>

class ColliderManager
{
public:
    // �V���O���g���C���X�^���X���擾
    static ColliderManager& GetInstance();

    // �O���b�h��Ԃ̏�����
    void Init(float worldWidth, float worldDepth, float cellSize);

    // �R���C�_�[�̓o�^/����
    void Register(const std::shared_ptr<ICollisionComponent>& collider);
    void Unregister(const std::shared_ptr<ICollisionComponent>& collider);

    // �`��y�A�ɑΉ�����Փ˔���֐���o�^
    void RegisterCollisionCheck(CollisionPair pair, CollisionFunc func);

    // ���t���[���̏Փ˔��菈��
    void CheckAllCollisions();

    // �Ǘ����̑S�����N���A
    void Clear();

private:
    // �V���O���g���p�^�[���̒��
    ColliderManager() = default;
    ~ColliderManager() = default;
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;

    // �w���p�[�֐�
    void ApplyPendingRemovals();
    void UpdateGrid();
    int GetGridIndex(const VECTOR& position) const;
    void ResolveCollision(ICollisionComponent& a, ICollisionComponent& b, const CollisionInfo& info);

    // �����o�[�ϐ�
    std::vector<std::shared_ptr<ICollisionComponent>> m_colliders;
    std::vector<std::shared_ptr<ICollisionComponent>> m_pendingRemoval;
    std::map<int, std::vector<std::shared_ptr<ICollisionComponent>>> m_grid;
    std::map<CollisionPair, CollisionFunc> m_collisionCheckers;

    float m_cellSize;
    int m_gridCols;
    int m_gridRows;
};