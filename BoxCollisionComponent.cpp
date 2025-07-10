#include "BoxCollisionComponent.h"
#include "SphereCollisionComponent.h"
#include "CapsuleCollisionComponent.h" // �����̎����̂��߂ɃC���N���[�h
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
    // �I�[�i�[����TransformComponent���擾
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_transform != nullptr && "BoxCollisionComponent requires a TransformComponent.");
}

VECTOR BoxCollisionComponent::GetCenter() const
{
    return m_transform->GetPosition();
}

VECTOR BoxCollisionComponent::GetSize() const
{
    // Transform�̃X�P�[������{�T�C�Y�ɏ�Z���āA�����I�ȃT�C�Y��Ԃ�
    // DxLib��VECTOR�ɂ͏�Z���Z�q���Ȃ����߁A�������ƂɌv�Z
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


// --- Visitor�p�^�[���̎��� ---

bool BoxCollisionComponent::CheckCollision(const ICollisionComponent& other) const
{
    // �_�u���f�B�X�p�b�`�F�����Accept�Ɏ�����n��
    return other.Accept(*this);
}

bool BoxCollisionComponent::Accept(const ICollisionComponent& other) const
{
    // �����Visit�ɁA��̓I�Ȍ^�ł��鎩��(*this)��n��
    return other.Visit(*this);
}


// --- ��̓I�ȏՓ˔��胍�W�b�N ---

// Box vs Sphere
bool BoxCollisionComponent::Visit(const SphereCollisionComponent& sphere) const
{
    // ���̒��S�_
    VECTOR sphereCenter = sphere.GetCenter();
    // �{�b�N�X�̒��S�_
    VECTOR boxCenter = GetCenter();
    // �{�b�N�X�̔����̃T�C�Y
    VECTOR boxHalfSize = VScale(GetSize(), 0.5f);

    // �{�b�N�X�̊e���ɑ΂���ŋߐړ_�����߂�
    float closestX = std::clamp(sphereCenter.x, boxCenter.x - boxHalfSize.x, boxCenter.x + boxHalfSize.x);
    float closestY = std::clamp(sphereCenter.y, boxCenter.y - boxHalfSize.y, boxCenter.y + boxHalfSize.y);
    float closestZ = std::clamp(sphereCenter.z, boxCenter.z - boxHalfSize.z, boxCenter.z + boxHalfSize.z);

    VECTOR closestPointOnBox = VGet(closestX, closestY, closestZ);

    // �ŋߐړ_�Ƌ��̒��S�Ƃ̋�����2����v�Z
    float distSq = VSquareSize(VSub(sphereCenter, closestPointOnBox));

    // ������2�悪�A���̔��a��2��ȉ��Ȃ�Փ˂��Ă���
    float sphereRadius = sphere.GetRadius();
    return distSq <= (sphereRadius * sphereRadius);
}

// Box vs Box (AABB)
bool BoxCollisionComponent::Visit(const BoxCollisionComponent& otherBox) const
{
    // ���g��AABB�̍ŏ��E�ő���W���v�Z
    VECTOR myCenter = GetCenter();
    VECTOR myHalfSize = VScale(GetSize(), 0.5f);
    VECTOR myMin = VSub(myCenter, myHalfSize);
    VECTOR myMax = VAdd(myCenter, myHalfSize);

    // �����AABB�̍ŏ��E�ő���W���v�Z
    VECTOR otherCenter = otherBox.GetCenter();
    VECTOR otherHalfSize = VScale(otherBox.GetSize(), 0.5f);
    VECTOR otherMin = VSub(otherCenter, otherHalfSize);
    VECTOR otherMax = VAdd(otherCenter, otherHalfSize);

    // �e���ŏd�Ȃ肪�Ȃ����`�F�b�N
    // ��ł��d�Ȃ��Ă��Ȃ���������΁A�Փ˂��Ă��Ȃ�
    if (myMax.x < otherMin.x || myMin.x > otherMax.x) return false;
    if (myMax.y < otherMin.y || myMin.y > otherMax.y) return false;
    if (myMax.z < otherMin.z || myMin.z > otherMax.z) return false;

    // �S�Ă̎��ŏd�Ȃ肪�������ꍇ�A�Փ˂��Ă���
    return true;
}

// Box vs Capsule
bool BoxCollisionComponent::Visit(const CapsuleCollisionComponent& capsule) const
{
    // Capsule����Sphere vs Box �� Line vs Box �̔��胍�W�b�N����������̂���ʓI
    // ���̂��߁A�����ł͏�����Capsule�Ɉς˂�
    return capsule.Visit(*this);
}