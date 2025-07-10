#pragma once

#include "ICollisionComponent.h"
#include <memory>
#include <utility> // for std::pair
#include <DxLib.h>

// �O���錾
class TransformComponent;

// �J�v�Z���`��̃R���C�_�[�R���|�[�l���g
class CapsuleCollisionComponent : public ICollisionComponent
{
public:
    // �J�v�Z���̔��a�ƁA���S���̒����i�����j���w�肵�č쐬
    explicit CapsuleCollisionComponent(float radius, float height);

    // ���C�t�T�C�N�����\�b�h
    void Start() override;
    void Update(float deltaTime) override {}

    // Visitor�p�^�[���֘A���\�b�h
    bool CheckCollision(const ICollisionComponent& other) const override;
    bool Accept(const ICollisionComponent& other) const override;
    bool Visit(const SphereCollisionComponent& sphere) const override;
    bool Visit(const BoxCollisionComponent& box) const override;
    bool Visit(const CapsuleCollisionComponent& capsule) const override;

    // �`����
    VECTOR GetCenter() const override;
    float GetRadius() const;
    float GetHeight() const;

    // �J�v�Z���̒��S���i�����j�̎n�_�ƏI�_�����[���h���W�Ŏ擾
    std::pair<VECTOR, VECTOR> GetLineSegment() const;

    void SetBaseRadius(float radius);
    void SetBaseHeight(float height);

    CollisionShapeType GetShapeType() const override { return CollisionShapeType::Capsule; }

private:
    float m_baseRadius; // �X�P�[���K�p�O�̊�{���a
    float m_baseHeight; // �X�P�[���K�p�O�̊�{����
    std::shared_ptr<TransformComponent> m_transform;
};