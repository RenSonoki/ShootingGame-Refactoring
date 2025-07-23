#include "CollisionCheckFunctions.h"
#include "SphereCollisionComponent.h"
#include "CapsuleCollisionComponent.h"
// #include "BoxCollisionComponent.h" // �{�b�N�X�֘A�̔������������ۂɕK�v
#include <cmath>
#include <algorithm>
#include <limits>

// --- �w���p�[�֐� ---

// �_P�������AB�ւ̍ŋߐړ_���v�Z����
static VECTOR ClosestPointOnLineSegment(const VECTOR& p, const VECTOR& a, const VECTOR& b)
{
    const VECTOR ab = VSub(b, a);
    const float abLenSq = VSquareSize(ab);
    if (abLenSq < 1e-12f) return a; // �������قړ_�̏ꍇ�̃G�b�W�P�[�X����

    // ab�x�N�g���ɑ΂���p-a�x�N�g���̎ˉe���v�Z���A�p�����[�^t�����߂�
    const float t = VDot(VSub(p, a), ab) / abLenSq;

    // t��0.0�`1.0�͈̔͂ɃN�����v���A������̓_�����߂�
    return VAdd(a, VScale(ab, std::clamp(t, 0.0f, 1.0f)));
}

// 2�̐����Ԃ̍ŋߐړ_�y�A���v�Z����w���p�[�֐�
static std::pair<VECTOR, VECTOR> ClosestPointsBetweenLineSegments(
    const VECTOR& p1, const VECTOR& p2, const VECTOR& q1, const VECTOR& q2)
{
    VECTOR d1 = VSub(p2, p1);
    VECTOR d2 = VSub(q2, q1);
    VECTOR r = VSub(p1, q1);
    float a = VDot(d1, d1), e = VDot(d2, d2), f = VDot(d2, r);
    float s = 0.0f, t = 0.0f;

    if (a <= 1e-6f && e <= 1e-6f) { return { p1, q1 }; }
    if (a <= 1e-6f) { t = std::clamp(f / e, 0.0f, 1.0f); }
    else {
        float c = VDot(d1, r);
        if (e <= 1e-6f) { s = std::clamp(-c / a, 0.0f, 1.0f); }
        else {
            float b = VDot(d1, d2);
            float denom = a * e - b * b;
            if (denom > 1e-6f) { s = std::clamp((b * f - c * e) / denom, 0.0f, 1.0f); }
            t = (b * s + f) / e;
            if (t < 0.0f) { t = 0.0f; s = std::clamp(-c / a, 0.0f, 1.0f); }
            else if (t > 1.0f) { t = 1.0f; s = std::clamp((b - c) / a, 0.0f, 1.0f); }
        }
    }
    return { VAdd(p1, VScale(d1, s)), VAdd(q1, VScale(d2, t)) };
}


// --- �Փ˔���֐��̎��� ---

// �� vs ��
bool CheckSphereToSphere(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo)
{
    const auto& sphereA = static_cast<const SphereCollisionComponent&>(a);
    const auto& sphereB = static_cast<const SphereCollisionComponent&>(b);

    VECTOR vecAB = VSub(sphereA.GetCenter(), sphereB.GetCenter());
    const float distSq = VSquareSize(vecAB);
    const float radiusSum = sphereA.GetRadius() + sphereB.GetRadius();

    if (distSq > radiusSum * radiusSum) return false; // �Փ˂��Ă��Ȃ�

    const float dist = sqrtf(distSq);
    outInfo.depth = radiusSum - dist; // �߂荞�ݗ�
    // �����o�������iB����A�ցj
    outInfo.normal = (dist > 1e-6f) ? VScale(vecAB, 1.0f / dist) : VGet(0, 1, 0);
    return true;
}

// �J�v�Z�� vs ��
bool CheckCapsuleToSphere(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo)
{
    const auto& capsule = static_cast<const CapsuleCollisionComponent&>(a);
    const auto& sphere = static_cast<const SphereCollisionComponent&>(b);

    // �J�v�Z���̒��S����ŁA���̒��S�ɍł��߂��_�����߂�
    auto capsuleSegment = capsule.GetWorldLineSegment();
    VECTOR closestPointOnSegment = ClosestPointOnLineSegment(sphere.GetCenter(), capsuleSegment.first, capsuleSegment.second);

    // ���̍ŋߐړ_�ƁA���̒��S�Ƃ̊ԂŁA�P���ȁu�� vs ���v�̔�����s��
    VECTOR vec = VSub(sphere.GetCenter(), closestPointOnSegment);
    float distSq = VSquareSize(vec);
    float totalRadius = capsule.GetRadius() + sphere.GetRadius();

    if (distSq > totalRadius * totalRadius) return false;

    float dist = sqrtf(distSq);
    outInfo.depth = totalRadius - dist;
    outInfo.normal = (dist > 1e-6f) ? VScale(vec, 1.0f / dist) : VGet(0, 1, 0);
    return true;
}

// �� vs �J�v�Z���́A���������ւ��ď�L�֐����ĂԂ���
bool CheckSphereToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo)
{
    if (CheckCapsuleToSphere(b, a, outInfo))
    {
        // �@���̌����𔽓]������̂�Y��Ȃ�
        outInfo.normal = VScale(outInfo.normal, -1.0f);
        return true;
    }
    return false;
}

// �J�v�Z�� vs �J�v�Z��
bool CheckCapsuleToCapsule(const ICollisionComponent& a, const ICollisionComponent& b, CollisionInfo& outInfo)
{
    const auto& capsuleA = static_cast<const CapsuleCollisionComponent&>(a);
    const auto& capsuleB = static_cast<const CapsuleCollisionComponent&>(b);

    // 2�̃J�v�Z���̒��S�����擾
    auto segmentA = capsuleA.GetWorldLineSegment();
    auto segmentB = capsuleB.GetWorldLineSegment();

    // 2�̐����Ԃ̍ŋߐړ_�y�A�����߂�
    auto closestPoints = ClosestPointsBetweenLineSegments(segmentA.first, segmentA.second, segmentB.first, segmentB.second);

    // �ŋߐړ_�Ԃ̋����Łu�� vs ���v�̔�����s��
    VECTOR vec = VSub(closestPoints.first, closestPoints.second);
    float distSq = VSquareSize(vec);
    float totalRadius = capsuleA.GetRadius() + capsuleB.GetRadius();

    if (distSq > totalRadius * totalRadius) return false;

    float dist = sqrtf(distSq);
    outInfo.depth = totalRadius - dist;
    outInfo.normal = (dist > 1e-6f) ? VScale(vec, 1.0f / dist) : VGet(0, 1, 0);
    return true;
}