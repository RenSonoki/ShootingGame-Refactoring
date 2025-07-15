#include "PlayerControllerComponent.h"
#include "Entity.h"
#include "TransformComponent.h" // Quaternion���g���悤�ɏC���ς݂̂��̂��C���N���[�h
#include "CameraComponent.h"    // CameraComponent�̒�`���K�v
#include "Quaternion.h"         // ���������쐬����Quaternion.h���C���N���[�h
#include "DxLib.h"
#include <cassert>
#include <cmath>

PlayerControllerComponent::PlayerControllerComponent() = default;

void PlayerControllerComponent::Start()
{
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(!m_transform.expired() && "PlayerControllerComponent requires a TransformComponent.");
}

void PlayerControllerComponent::SetCamera(std::shared_ptr<CameraComponent> camera)
{
    m_camera = camera;
}

void PlayerControllerComponent::SetMoveSpeed(float speed) { m_moveSpeed = speed; }
void PlayerControllerComponent::SetRotationSpeed(float speed) { m_rotationSpeed = speed; }

void PlayerControllerComponent::Update(float deltaTime)
{
    auto transform = m_transform.lock();
    auto camera = m_camera.lock();
    if (!transform || !camera) return;

    // --- 1. ���͎�t ---
    VECTOR inputVec = VGet(0, 0, 0);
    if (CheckHitKey(KEY_INPUT_W)) { inputVec.z += 1.0f; }
    if (CheckHitKey(KEY_INPUT_S)) { inputVec.z -= 1.0f; }
    if (CheckHitKey(KEY_INPUT_A)) { inputVec.x -= 1.0f; }
    if (CheckHitKey(KEY_INPUT_D)) { inputVec.x += 1.0f; }

    // --- 2. �ړ������̌v�Z ---
    if (VSquareSize(inputVec) < 1e-6f)
    {
        transform->SetVelocity(VGet(0, 0, 0)); // ���͂��Ȃ���Β�~
        return;
    }

    auto cameraTransform = camera->GetOwner()->GetComponent<TransformComponent>();
    if (!cameraTransform) return;

    VECTOR cameraForward = cameraTransform->GetForward();
    VECTOR cameraRight = cameraTransform->GetRight();
    cameraForward.y = 0.0f;
    cameraRight.y = 0.0f;
    cameraForward = VNorm(cameraForward);
    cameraRight = VNorm(cameraRight);

    VECTOR moveDir = VAdd(VScale(cameraRight, inputVec.x), VScale(cameraForward, inputVec.z));
    moveDir = VNorm(moveDir);

    // --- 3. ���x�̐ݒ� ---
    VECTOR velocity = VScale(moveDir, m_moveSpeed);
    transform->SetVelocity(velocity);

    // --- 4. ���񏈗� ---
    // �y�C���_�z�����Quaternion�N���X���g�p
    Quaternion currentRot = transform->GetRotation();

    float targetAngle = atan2f(moveDir.x, moveDir.z);
    Quaternion targetRot = Quaternion::FromEulerAngles(0.0f, targetAngle, 0.0f);

    Quaternion newRot = Quaternion::Slerp(currentRot, targetRot, deltaTime * m_rotationSpeed);

    transform->SetRotation(newRot);
}