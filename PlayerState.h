#pragma once
#include <memory>

// �O���錾
class PlayerControllerComponent;
class ModelAnimatorComponent;
class TransformComponent;

/**
 * @interface IPlayerState
 * @brief �v���C���[�̑S�Ắu��ԁv�N���X���p������C���^�[�t�F�[�X
 */
class IPlayerState
{
public:
    virtual ~IPlayerState() = default;

    // ���̏�ԂɂȂ����u�ԂɌĂ΂��
    virtual void OnEnter(PlayerControllerComponent* owner) = 0;
    // ���̏�Ԃ̊ԁA���t���[���Ă΂��
    virtual void Update(PlayerControllerComponent* owner, float deltaTime) = 0;
    // ���̏�Ԃ���ʂ̏�ԂɈڂ�u�ԂɌĂ΂��
    virtual void OnExit(PlayerControllerComponent* owner) = 0;
};


/**
 * @class PlayerIdleState
 * @brief �ҋ@���
 */
class PlayerIdleState : public IPlayerState
{
public:
    void OnEnter(PlayerControllerComponent* owner) override;
    void Update(PlayerControllerComponent* owner, float deltaTime) override;
    void OnExit(PlayerControllerComponent* owner) override;
};


/**
 * @class PlayerMoveState
 * @brief �ړ����
 */
class PlayerMoveState : public IPlayerState
{
public:
    void OnEnter(PlayerControllerComponent* owner) override;
    void Update(PlayerControllerComponent* owner, float deltaTime) override;
    void OnExit(PlayerControllerComponent* owner) override;
};