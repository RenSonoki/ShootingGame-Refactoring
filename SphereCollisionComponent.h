#pragma once
#include "ICollisionComponent.h" // �����������t�@�N�^�����O����ICollisionComponent
#include <memory>

class TransformComponent;

// ���̏Փ˃R���|�[�l���g
class SphereCollisionComponent : public ICollisionComponent
{
public:
    SphereCollisionComponent();
    virtual ~SphereCollisionComponent() = default;

    ComponentID GetID() const override;

    // --- ComponentBase�̃��C�t�T�C�N�����\�b�h ---
    void Start() override;
    // Update��ColliderManager���ꊇ�ŏ������邽�߁A�X�ɂ͕s�v
    void Update(float deltaTime) override {}

    // --- ICollisionComponent�C���^�[�t�F�[�X�̎��� ---
    CollisionShapeType GetShapeType() const override { return CollisionShapeType::Sphere; }
    VECTOR GetCenter() const override;

    // --- ���̃N���X�ŗL�̋@�\ ---
    float GetRadius() const;
    void SetRadius(float radius);

private:
    float m_radius;
    // TransformComponent�ւ̃|�C���^��weak_ptr�ɂ���ƁA�����S�ł�
    std::weak_ptr<TransformComponent> m_transform;
};