#include "CollisionCheckFunctions.h"
#include "SphereCollisionComponent.h"
//#include "BoxCollisionComponent.h"
#include "CapsuleCollisionComponent.h"
#include <cmath>
#include <algorithm>
#include <limits>

// --- �w���p�[�֐� ---
static VECTOR ClosestPointOnLineSegment(const VECTOR& p, const VECTOR& a, const VECTOR& b)
{
    VECTOR ab = VSub(b, a);
    // VSquareSize��0�ɋ߂��ꍇ�A���Z��NaN����������̂�h��
    float abLenSq = VSquareSize(ab);
    if (abLenSq < 1e-12f) return a;

    float t = VDot(VSub(p, a), ab) / abLenSq;
    t = std::clamp(t, 0.0f, 1.0f);
    return VAdd(a, VScale(ab, t));
}
// (ClosestPointsBetweenLineSegments �����l�ɂ����ɔz�u)

// --- �Փ˔���֐��̎��� ---

// �� vs ��
bool CheckSphereToSphere(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo)
{
    const auto& sphereA = static_cast<const SphereCollisionComponent&>(a);
    const auto& sphereB = static_cast<const SphereCollisionComponent&>(b);

    VECTOR vecAB = VSub(sphereA.GetCenter(), sphereB.GetCenter());
    const float distSq = VSquareSize(vecAB);
    const float radiusSum = sphereA.GetRadius() + sphereB.GetRadius();

    if (distSq > radiusSum * radiusSum) return false;

    const float dist = sqrtf(distSq);
    outInfo.depth = radiusSum - dist;
    outInfo.normal = (dist > 1e-6f) ? VScale(vecAB, 1.0f / dist) : VGet(0, 1, 0);
    return true;
}

// �J�v�Z�� vs ��
bool CheckSphereToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo)
{
    // CheckSphereToCapsule��CheckCapsuleToSphere�Ɠ����Ȃ̂ŁA�����ł͈���ɏ������Ϗ�
    return CheckCapsuleToSphere(b, a, outInfo);
}


// OBB(��]���锠)��A�J�v�Z���ƃ{�b�N�X�̔���͔��ɕ��G�Ȃ��߁A
// ���I�Ȏ������K�v�ɂȂ�܂��B�����ł̓X�^�u�i������j�Ƃ��Ă����܂��B
bool CheckCapsuleToCapsule(const ICollisionComponent&, const ICollisionComponent&, CollisionInfo&) { return false; }