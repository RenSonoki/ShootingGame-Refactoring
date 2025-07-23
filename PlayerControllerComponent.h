#pragma once
#include "ComponentBase.h"
#include <memory>

// �O���錾
class TransformComponent;
class CameraComponent;
class ModelAnimatorComponent;
class IPlayerState;
class BulletShooterComponent;

/**
 * @class PlayerControllerComponent
 * @brief �v���C���[�̏�Ԃ��Ǘ����A��Ԃɉ����������̎��s���ϔC����R���|�[�l���g
 */
class PlayerControllerComponent : public ComponentBase
{
public:
    PlayerControllerComponent();
    virtual ~PlayerControllerComponent();

    // --- ���C�t�T�C�N�����\�b�h ---
    void Start() override;
    void Update(float deltaTime) override;
    ComponentID GetID() const override;

    /**
     * @brief �v���C���[�̏�Ԃ�V������ԂɑJ�ڂ����܂�
     * @param newState �V������ԃI�u�W�F�N�g
     */
    void ChangeState(std::unique_ptr<IPlayerState> newState);

    /**
     * @brief �O���i��FGameScene�j����J������ݒ肵�܂�
     * @param camera ���C���J������CameraComponent
     */
    void SetCamera(std::weak_ptr<CameraComponent> camera);

    // --- ��ԃN���X�iState�j����e������擾���邽�߂̃Q�b�^�[ ---
    TransformComponent* GetTransform() const;
    CameraComponent* GetCamera() const;
    ModelAnimatorComponent* GetAnimator() const;
    BulletShooterComponent* GetShooter() const;
    float GetMoveSpeed() const;
    float GetRotationSpeed() const;

private:
    // �A�g����R���|�[�l���g�ւ̃|�C���^
    std::weak_ptr<TransformComponent> m_transform;
    std::weak_ptr<CameraComponent> m_camera;
    std::weak_ptr<ModelAnimatorComponent> m_animator;
    std::weak_ptr<BulletShooterComponent> m_shooter;

    // ���݂̏�Ԃ�ێ�����|�C���^
    std::unique_ptr<IPlayerState> m_currentState;

    // �p�����[�^
    float m_moveSpeed;
    float m_rotationSpeed;
};