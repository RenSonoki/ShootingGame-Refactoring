#pragma once
#include "CollisionSystemTypes.h" // CollisionInfo �� CollisionFunc �̒�`

// --- �Փ˔���֐��Q ---

// �� vs ��
bool CheckSphereToSphere(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);

// �� vs �{�b�N�X(AABB)
//bool CheckSphereToBox(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);

// �� vs �J�v�Z��
bool CheckSphereToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);

// �{�b�N�X(AABB) vs �{�b�N�X(AABB)
//bool CheckBoxToBox(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);

// �{�b�N�X(AABB) vs �J�v�Z��
//bool CheckBoxToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);

// �J�v�Z�� vs �J�v�Z��
bool CheckCapsuleToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);