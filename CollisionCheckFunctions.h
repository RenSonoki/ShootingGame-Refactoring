#pragma once
#include "CollisionSystemTypes.h" // CollisionInfo �� CollisionFunc �̒�`

// --- �Փ˔���֐��Q ---

// �� vs ��
bool CheckSphereToSphere(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);

// �� vs �J�v�Z��
bool CheckSphereToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);

// �J�v�Z�� vs �J�v�Z��
bool CheckCapsuleToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo);