#include "BoxCollisionComponent.h"
#include "SphereCollisionComponent.h"
#include "CapsuleCollisionComponent.h" // 将来の実装のためにインクルード
#include "Entity.h"
#include "TransformComponent.h"
#include <algorithm> // std::max, std::min
#include <cassert>


BoxCollisionComponent::BoxCollisionComponent(const VECTOR& size)
    : m_baseSize(size), m_transform(nullptr)
{
}

void BoxCollisionComponent::Start()
{
    // オーナーからTransformComponentを取得
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_transform != nullptr && "BoxCollisionComponent requires a TransformComponent.");
}

VECTOR BoxCollisionComponent::GetCenter() const
{
    return m_transform->GetPosition();
}

VECTOR BoxCollisionComponent::GetSize() const
{
    // Transformのスケールを基本サイズに乗算して、実質的なサイズを返す
    // DxLibのVECTORには乗算演算子がないため、成分ごとに計算
    VECTOR scale = m_transform->GetScale();
    return VGet(
        m_baseSize.x * scale.x,
        m_baseSize.y * scale.y,
        m_baseSize.z * scale.z
    );
}

void BoxCollisionComponent::SetBaseSize(const VECTOR& size)
{
    m_baseSize = size;
}


// --- Visitorパターンの実装 ---

bool BoxCollisionComponent::CheckCollision(const ICollisionComponent& other) const
{
    // ダブルディスパッチ：相手のAcceptに自分を渡す
    return other.Accept(*this);
}

bool BoxCollisionComponent::Accept(const ICollisionComponent& other) const
{
    // 相手のVisitに、具体的な型である自分(*this)を渡す
    return other.Visit(*this);
}


// --- 具体的な衝突判定ロジック ---

// Box vs Sphere
bool BoxCollisionComponent::Visit(const SphereCollisionComponent& sphere) const
{
    // 球の中心点
    VECTOR sphereCenter = sphere.GetCenter();
    // ボックスの中心点
    VECTOR boxCenter = GetCenter();
    // ボックスの半分のサイズ
    VECTOR boxHalfSize = VScale(GetSize(), 0.5f);

    // ボックスの各軸に対する最近接点を求める
    float closestX = std::clamp(sphereCenter.x, boxCenter.x - boxHalfSize.x, boxCenter.x + boxHalfSize.x);
    float closestY = std::clamp(sphereCenter.y, boxCenter.y - boxHalfSize.y, boxCenter.y + boxHalfSize.y);
    float closestZ = std::clamp(sphereCenter.z, boxCenter.z - boxHalfSize.z, boxCenter.z + boxHalfSize.z);

    VECTOR closestPointOnBox = VGet(closestX, closestY, closestZ);

    // 最近接点と球の中心との距離の2乗を計算
    float distSq = VSquareSize(VSub(sphereCenter, closestPointOnBox));

    // 距離の2乗が、球の半径の2乗以下なら衝突している
    float sphereRadius = sphere.GetRadius();
    return distSq <= (sphereRadius * sphereRadius);
}

// Box vs Box (AABB)
bool BoxCollisionComponent::Visit(const BoxCollisionComponent& otherBox) const
{
    // 自身のAABBの最小・最大座標を計算
    VECTOR myCenter = GetCenter();
    VECTOR myHalfSize = VScale(GetSize(), 0.5f);
    VECTOR myMin = VSub(myCenter, myHalfSize);
    VECTOR myMax = VAdd(myCenter, myHalfSize);

    // 相手のAABBの最小・最大座標を計算
    VECTOR otherCenter = otherBox.GetCenter();
    VECTOR otherHalfSize = VScale(otherBox.GetSize(), 0.5f);
    VECTOR otherMin = VSub(otherCenter, otherHalfSize);
    VECTOR otherMax = VAdd(otherCenter, otherHalfSize);

    // 各軸で重なりがないかチェック
    // 一つでも重なっていない軸があれば、衝突していない
    if (myMax.x < otherMin.x || myMin.x > otherMax.x) return false;
    if (myMax.y < otherMin.y || myMin.y > otherMax.y) return false;
    if (myMax.z < otherMin.z || myMin.z > otherMax.z) return false;

    // 全ての軸で重なりがあった場合、衝突している
    return true;
}

// Box vs Capsule
bool BoxCollisionComponent::Visit(const CapsuleCollisionComponent& capsule) const
{
    // Capsule側にSphere vs Box と Line vs Box の判定ロジックを実装するのが一般的
    // そのため、ここでは処理をCapsuleに委ねる
    return capsule.Visit(*this);
}