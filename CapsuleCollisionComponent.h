#pragma once
#include "ICollisionComponent.h"
#include <memory>
#include <utility> // for std::pair

class TransformComponent;

// �J�v�Z���`��̃R���C�_�[�R���|�[�l���g�i���t�@�N�^�����O��j
class CapsuleCollisionComponent : public ICollisionComponent
{
public:
    explicit CapsuleCollisionComponent(float radius, float height);
    virtual ~CapsuleCollisionComponent() = default;

    ComponentID GetID() const override;

    // --- ���C�t�T�C�N�����\�b�h ---
    void Start() override;
    void Update(float deltaTime) override {}

    // --- ICollisionComponent�C���^�[�t�F�[�X�̎��� ---
    CollisionShapeType GetShapeType() const override { return CollisionShapeType::Capsule; }
    VECTOR GetCenter() const override;

    // --- ���̃N���X�ŗL�̋@�\ ---
    float GetRadius() const;
    float GetHeight() const;

    // ���[���h��Ԃł̃J�v�Z���̒��S���i�����j���擾����
    std::pair<VECTOR, VECTOR> GetWorldLineSegment() const;

    void SetBaseRadius(float radius);
    void SetBaseHeight(float height);

private:
    float m_baseRadius;
    float m_baseHeight;
    std::weak_ptr<TransformComponent> m_transform;
};