#include "CapsuleCollisionComponent.h"
#include "SphereCollisionComponent.h"
#include "BoxCollisionComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <algorithm>
#include <cassert>

// 点Pから線分ABへの最近接点を計算する
static VECTOR ClosestPointOnLineSegment(const VECTOR& p, const VECTOR& a, const VECTOR& b)
{
    VECTOR ab = VSub(b, a);
    float t = VDot(VSub(p, a), ab) / VSquareSize(ab);
    t = std::clamp(t, 0.0f, 1.0f); // tを0-1の範囲に収める
    return VAdd(a, VScale(ab, t));
}

// 2つの線分（P1->P2 と Q1->Q2）間の最近接点ペアを計算する
static std::pair<VECTOR, VECTOR> ClosestPointsBetweenLineSegments(
    const VECTOR& p1, const VECTOR& p2, const VECTOR& q1, const VECTOR& q2)
{
    VECTOR d1 = VSub(p2, p1);
    VECTOR d2 = VSub(q2, q1);
    VECTOR r = VSub(p1, q1);
    float a = VDot(d1, d1);
    float e = VDot(d2, d2);
    float f = VDot(d2, r);

    float s = 0.0f, t = 0.0f;

    if (a <= 1e-6f && e <= 1e-6f) { // 両方が点の場合
        return { p1, q1 };
    }
    if (a <= 1e-6f) { // 最初の線分が点の場合
        t = std::clamp(f / e, 0.0f, 1.0f);
    }
    else {
        float c = VDot(d1, r);
        if (e <= 1e-6f) { // 2番目の線分が点の場合
            s = std::clamp(-c / a, 0.0f, 1.0f);
        }
        else {
            float b = VDot(d1, d2);
            float denom = a * e - b * b;
            if (denom != 0.0f) {
                s = std::clamp((b * f - c * e) / denom, 0.0f, 1.0f);
            }
            t = (b * s + f) / e;
            if (t < 0.0f) { t = 0.0f; s = std::clamp(-c / a, 0.0f, 1.0f); }
            else if (t > 1.0f) { t = 1.0f; s = std::clamp((b - c) / a, 0.0f, 1.0f); }
        }
    }
    VECTOR closestPoint1 = VAdd(p1, VScale(d1, s));
    VECTOR closestPoint2 = VAdd(q1, VScale(d2, t));
    return { closestPoint1, closestPoint2 };
}


CapsuleCollisionComponent::CapsuleCollisionComponent(float radius, float height)
    : m_baseRadius(radius), m_baseHeight(height), m_transform(nullptr)
{
}

void CapsuleCollisionComponent::Start()
{
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_transform != nullptr && "CapsuleCollisionComponent requires a TransformComponent.");
}

VECTOR CapsuleCollisionComponent::GetCenter() const
{
    return m_transform->GetPosition();
}

float CapsuleCollisionComponent::GetRadius() const
{
    VECTOR scale = m_transform->GetScale();
    float maxScale = (std::max)(scale.x, (std::max)(scale.y, scale.z));
    return m_baseRadius * maxScale;
}

float CapsuleCollisionComponent::GetHeight() const
{
    // 高さはY軸スケールを反映
    return m_baseHeight * m_transform->GetScale().y;
}

void CapsuleCollisionComponent::SetBaseRadius(float radius) { m_baseRadius = radius; }
void CapsuleCollisionComponent::SetBaseHeight(float height) { m_baseHeight = height; }

std::pair<VECTOR, VECTOR> CapsuleCollisionComponent::GetLineSegment() const
{
    VECTOR center = GetCenter();
    float halfHeight = GetHeight() / 2.0f;
    // Y軸に沿った線分と仮定
    VECTOR start = VGet(center.x, center.y - halfHeight, center.z);
    VECTOR end = VGet(center.x, center.y + halfHeight, center.z);
    // TODO: Transformの回転を反映させる
    return { start, end };
}

// --- Visitorパターンの実装 ---

bool CapsuleCollisionComponent::CheckCollision(const ICollisionComponent& other) const
{
    return other.Accept(*this);
}

bool CapsuleCollisionComponent::Accept(const ICollisionComponent& other) const
{
    return other.Visit(*this);
}

// --- 具体的な衝突判定ロジック ---

bool CapsuleCollisionComponent::Visit(const SphereCollisionComponent& sphere) const
{
    auto mySegment = GetLineSegment();
    VECTOR closestPointOnCapsuleSegment = ClosestPointOnLineSegment(sphere.GetCenter(), mySegment.first, mySegment.second);

    float totalRadius = GetRadius() + sphere.GetRadius();
    return VSquareSize(VSub(sphere.GetCenter(), closestPointOnCapsuleSegment)) <= (totalRadius * totalRadius);
}

bool CapsuleCollisionComponent::Visit(const BoxCollisionComponent& box) const
{
    // この判定は非常に複雑なので、Box側に処理を委ねる
    // Box側は、Box vs Sphere と Box vs Line の複合判定などを実装する必要がある
    // ここでは単純化のため、Boxがカプセルの中心点を含むかで判定（不正確）
    VECTOR boxMin = VSub(box.GetCenter(), VScale(box.GetSize(), 0.5f));
    VECTOR boxMax = VAdd(box.GetCenter(), VScale(box.GetSize(), 0.5f));
    auto segment = GetLineSegment();
    // 実際にはもっと複雑な判定が必要
    return false;
}

bool CapsuleCollisionComponent::Visit(const CapsuleCollisionComponent& otherCapsule) const
{
    auto mySegment = GetLineSegment();
    auto otherSegment = otherCapsule.GetLineSegment();

    auto closestPoints = ClosestPointsBetweenLineSegments(mySegment.first, mySegment.second, otherSegment.first, otherSegment.second);

    float totalRadius = GetRadius() + otherCapsule.GetRadius();
    return VSquareSize(VSub(closestPoints.first, closestPoints.second)) <= (totalRadius * totalRadius);
}