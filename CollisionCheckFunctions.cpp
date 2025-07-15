#include "CollisionCheckFunctions.h"
#include "SphereCollisionComponent.h"
//#include "BoxCollisionComponent.h"
#include "CapsuleCollisionComponent.h"
#include <cmath>
#include <algorithm>
#include <limits>

// --- ヘルパー関数 ---
static VECTOR ClosestPointOnLineSegment(const VECTOR& p, const VECTOR& a, const VECTOR& b)
{
    VECTOR ab = VSub(b, a);
    // VSquareSizeが0に近い場合、除算でNaNが発生するのを防ぐ
    float abLenSq = VSquareSize(ab);
    if (abLenSq < 1e-12f) return a;

    float t = VDot(VSub(p, a), ab) / abLenSq;
    t = std::clamp(t, 0.0f, 1.0f);
    return VAdd(a, VScale(ab, t));
}
// (ClosestPointsBetweenLineSegments も同様にここに配置)

// --- 衝突判定関数の実装 ---

// 球 vs 球
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

// カプセル vs 球
bool CheckSphereToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo)
{
    // CheckSphereToCapsuleはCheckCapsuleToSphereと同じなので、ここでは一方に処理を委譲
    return CheckCapsuleToSphere(b, a, outInfo);
}


// OBB(回転する箱)や、カプセルとボックスの判定は非常に複雑なため、
// 専門的な実装が必要になります。ここではスタブ（空実装）としておきます。
bool CheckCapsuleToCapsule(const ICollisionComponent&, const ICollisionComponent&, CollisionInfo&) { return false; }