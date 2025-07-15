#pragma once
#include "ICollisionComponent.h"
#include "CollisionSystemTypes.h" // �쐬�������L�w�b�_
#include <vector>
#include <memory>
#include <map>

class ColliderManager
{
public:
    static ColliderManager& Instance();

    void Init(float worldWidth, float worldDepth, float cellSize);

    void Register(const std::shared_ptr<ICollisionComponent>& collider);
    void Unregister(const std::shared_ptr<ICollisionComponent>& collider);
    void RegisterCollisionCheck(CollisionPair pair, CollisionFunc func);

    void CheckAllCollisions();
    void Clear();

private:
    // --- �����o�[�ϐ� ---
    // �S�ẴR���C�_�[��ێ�����}�X�^�[���X�g
    std::vector<std::shared_ptr<ICollisionComponent>> m_colliders;

    // ��ԕ����p�̃O���b�h (�L�[��GridIndex, �l�͂��̃Z�����̃R���C�_�[���X�g)
    std::map<int, std::vector<std::shared_ptr<ICollisionComponent>>> m_grid;

    // �Փ˔���֐��̃��b�N�A�b�v�e�[�u��
    std::map<CollisionPair, CollisionFunc> m_collisionCheckers;

    // �x���폜�p�̃��X�g
    std::vector<std::shared_ptr<ICollisionComponent>> m_pendingRemoval;

    // �O���b�h�̃p�����[�^
    float m_worldWidth;
    float m_worldDepth;
    float m_cellSize;
    int m_gridCols;

    // --- �V���O���g���̂���@ ---
    ColliderManager() = default;
    ~ColliderManager() = default;
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;

    // --- �v���C�x�[�g�ȃw���p�[�֐� ---
    void ApplyPendingRemovals();
    void UpdateGrid();
    int GetGridIndex(const VECTOR& position) const;
};