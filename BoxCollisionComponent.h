#pragma once

#include "ICollisionComponent.h"
#include <memory>
#include <DxLib.h> // VECTOR�̂���

// �O���錾
class TransformComponent;

// �{�b�N�X�iAABB�j�`��̃R���C�_�[�R���|�[�l���g
class BoxCollisionComponent : public ICollisionComponent
{
public:
    // �{�b�N�X�̃T�C�Y�i���A�����A���s���j���w�肵�č쐬
    explicit BoxCollisionComponent(const VECTOR& size);

    // ���C�t�T�C�N�����\�b�h
    void Start() override;
    void Update(float deltaTime) override {} // �������Ȃ�

    // Visitor�p�^�[���֘A���\�b�h
    bool CheckCollision(const ICollisionComponent& other) const override;
    bool Accept(const ICollisionComponent& other) const override;
    bool Visit(const SphereCollisionComponent& sphere) const override;
    bool Visit(const BoxCollisionComponent& box) const override;
    bool Visit(const CapsuleCollisionComponent& capsule) const override;

    // �`����
    VECTOR GetCenter() const override;
    VECTOR GetSize() const; // �X�P�[���𔽉f���������I�ȃT�C�Y
    void SetBaseSize(const VECTOR& size);

    CollisionShapeType GetShapeType() const override { return CollisionShapeType::Box; }

private:
    VECTOR m_baseSize; // �X�P�[���K�p�O�̊�{�T�C�Y
    std::shared_ptr<TransformComponent> m_transform;
};