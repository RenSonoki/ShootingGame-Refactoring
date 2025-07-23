#include "PlayerState.h"
#include "PlayerControllerComponent.h"
#include "BulletShooterComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "ModelAnimatorComponent.h"
#include "Quaternion.h"
#include "Entity.h"
#include "DxLib.h"
#include <cmath>

// ---- �ҋ@��� (Idle) ----
void PlayerIdleState::OnEnter(PlayerControllerComponent* owner)
{
    // �ҋ@��Ԃɓ�������Aidle�A�j���[�V�������Đ�
    if (auto anim = owner->GetAnimator())
    {
        anim->PlayAnimationByName(L"idle", true);
    }
    // ���x���[���ɂ���
    if (auto tr = owner->GetTransform())
    {
        tr->SetVelocity({ 0,0,0 });
    }
}

void PlayerIdleState::Update(PlayerControllerComponent* owner, float deltaTime)
{
    if (GetMouseInput() & MOUSE_INPUT_LEFT) // �}�E�X�̍��N���b�N���`�F�b�N
    {
        if (auto shooter = owner->GetShooter())
        {
            shooter->RequestShoot();
        }
    }

    // �ړ����͂����������`�F�b�N
    if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D))
    {
        // ���͂�����΁u�ړ���ԁv�ɑJ��
        owner->ChangeState(std::make_unique<PlayerMoveState>());
    }
}

void PlayerIdleState::OnExit(PlayerControllerComponent* owner)
{
    // ���ɉ�������K�v�Ȃ�
}


// ---- �ړ���� (Move) ----
void PlayerMoveState::OnEnter(PlayerControllerComponent* owner)
{
    // �ړ���Ԃɓ�������Awalk�A�j���[�V�������Đ�
    if (auto anim = owner->GetAnimator())
    {
        anim->PlayAnimationByName(L"walk", true);
    }
}

void PlayerMoveState::Update(PlayerControllerComponent* owner, float deltaTime)
{
    auto transform = owner->GetTransform();
    auto camera = owner->GetCamera();
    if (!transform || !camera) return;

    auto cameraTransform = camera->GetOwner()->GetComponent<TransformComponent>();
    if (!cameraTransform) return;

    // --- �����̐��� (���̃��W�b�N�Ɠ���) ---
    VECTOR aimDirection = cameraTransform->GetForward();
    aimDirection.y = 0.0f;
    if (VSquareSize(aimDirection) > 1e-6f)
    {
        aimDirection = VNorm(aimDirection);
        float targetAngle = atan2f(aimDirection.x, aimDirection.z);
        Quaternion targetRot = Quaternion::FromEulerAngles(0.0f, targetAngle, 0.0f);
        Quaternion currentRot = transform->GetRotation();
        Quaternion newRot = Quaternion::Slerp(currentRot, targetRot, deltaTime * owner->GetRotationSpeed());
        transform->SetRotation(newRot);
    }

    // --- �ړ����� (���̃��W�b�N�Ɠ���) ---
    VECTOR inputVec = { 0,0,0 };
    if (CheckHitKey(KEY_INPUT_W)) { inputVec.z += 1.0f; }
    if (CheckHitKey(KEY_INPUT_S)) { inputVec.z -= 1.0f; }
    if (CheckHitKey(KEY_INPUT_A)) { inputVec.x -= 1.0f; }
    if (CheckHitKey(KEY_INPUT_D)) { inputVec.x += 1.0f; }

    // �� ���˃��W�b�N��ǉ�
    if (GetMouseInput() & MOUSE_INPUT_LEFT) // �}�E�X�̍��N���b�N���`�F�b�N
    {
        if (auto shooter = owner->GetShooter())
        {
            shooter->RequestShoot();
        }
    }

    // �� ��ԑJ�ڂ̃`�F�b�N
    if (VSquareSize(inputVec) < 1e-6f)
    {
        // ���͂��Ȃ��Ȃ�����u�ҋ@��ԁv�ɑJ��
        owner->ChangeState(std::make_unique<PlayerIdleState>());
        return; // �J�ڂ����̂ŁA���̃t���[���̈ȍ~�̏����͕s�v
    }

    // --- ���x�̐ݒ� (���̃��W�b�N�Ɠ���) ---
    VECTOR cameraForward = VNorm(VECTOR{ cameraTransform->GetForward().x, 0.0f, cameraTransform->GetForward().z });
    VECTOR cameraRight = VNorm(VECTOR{ cameraTransform->GetRight().x, 0.0f, cameraTransform->GetRight().z });
    VECTOR moveDir = VNorm(VAdd(VScale(cameraRight, inputVec.x), VScale(cameraForward, inputVec.z)));
    VECTOR velocity = VScale(moveDir, owner->GetMoveSpeed());
    transform->SetVelocity(velocity);
}

void PlayerMoveState::OnExit(PlayerControllerComponent* owner)
{
    // ��Ԃ𔲂��鎞�ɁA�O�̂��ߑ��x���[���ɂ��Ă���
    if (auto tr = owner->GetTransform())
    {
        tr->SetVelocity({ 0,0,0 });
    }
}