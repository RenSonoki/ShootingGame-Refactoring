#include "PlayerControllerComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "ModelAnimatorComponent.h"
#include "BulletShooterComponent.h"
#include "DebugRenderer.h" // �f�o�b�O�`��p�̃w�b�_�[�t�@�C�����C���N���[�h
#include "PlayerState.h" // ��ԃN���X�̎������C���N���[�h
#include <cassert>

PlayerControllerComponent::PlayerControllerComponent()
    : m_moveSpeed(5.0f)
    , m_rotationSpeed(15.0f)
    , m_currentState(nullptr)
{
}

// �� �C���_: �f�X�g���N�^�́u��`�v�������Ɉړ�����
// ���̏ꏊ�ł� IPlayerState �����S�Ȍ^�Ȃ̂ŁAm_currentState �͈��S�ɔj���ł���
PlayerControllerComponent::~PlayerControllerComponent() = default;

void PlayerControllerComponent::Start()
{
    // ���g���A�^�b�`����Ă���G���e�B�e�B����A�A�g����R���|�[�l���g���擾���ăL���b�V��
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    m_animator = GetOwner()->GetComponent<ModelAnimatorComponent>();
    m_shooter = GetOwner()->GetComponent<BulletShooterComponent>();

    // �A�g����R���|�[�l���g���ݒ肳��Ă��邩�A�f�o�b�O���Ƀ`�F�b�N
    assert(!m_transform.expired() && "PlayerControllerComponent requires a TransformComponent.");
    assert(!m_animator.expired() && "PlayerControllerComponent requires a ModelAnimatorComponent.");
    assert(!m_shooter.expired() && "PlayerControllerComponent requires a BulletShooterComponent.");

    // �ŏ��̏�Ԃ��u�ҋ@��ԁv�ɐݒ肵�ĊJ�n
    ChangeState(std::make_unique<PlayerIdleState>());
}

void PlayerControllerComponent::Update(float deltaTime)
{
    // Update�̐Ӗ��́A���݂̏�ԃI�u�W�F�N�g��Update���Ăяo�����Ƃ���
    if (m_currentState)
    {
        m_currentState->Update(this, deltaTime);
    }

#if _DEBUG
    // �� �v���C���[�̈ʒu�ɗ΂̋���`��
    if (auto tr = GetTransform()) {
        DebugRenderer::GetInstance().AddSphere(tr->GetPosition(), 1.5f, GetColor(0, 255, 0));
    }
#endif
}

ComponentID PlayerControllerComponent::GetID() const
{
    // ComponentID��PlayerController�Ȃǂ�ǉ����Ă�������
    return ComponentID::PlayerController;
}

void PlayerControllerComponent::ChangeState(std::unique_ptr<IPlayerState> newState)
{
    // ���݂̏�Ԃ�����΁A���̏I���������Ăяo��
    if (m_currentState)
    {
        m_currentState->OnExit(this);
    }

    // �V������Ԃɐ؂�ւ���
    m_currentState = std::move(newState);

    // �V������Ԃ̊J�n�������Ăяo��
    if (m_currentState)
    {
        m_currentState->OnEnter(this);
    }
}

void PlayerControllerComponent::SetCamera(std::weak_ptr<CameraComponent> camera)
{
    m_camera = camera;
}

// --- �Q�b�^�[�̎��� ---
// State�N���X���I�[�i�[�̏������S�Ɏ擾���邽�߂Ɏg���܂�
TransformComponent* PlayerControllerComponent::GetTransform() const { return m_transform.lock().get(); }
CameraComponent* PlayerControllerComponent::GetCamera() const { return m_camera.lock().get(); }
ModelAnimatorComponent* PlayerControllerComponent::GetAnimator() const { return m_animator.lock().get(); }
BulletShooterComponent* PlayerControllerComponent::GetShooter() const { return m_shooter.lock().get(); }
float PlayerControllerComponent::GetMoveSpeed() const { return m_moveSpeed; }
float PlayerControllerComponent::GetRotationSpeed() const { return m_rotationSpeed; }