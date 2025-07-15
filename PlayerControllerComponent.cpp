#include "PlayerControllerComponent.h"
#include "Entity.h"
#include "TransformComponent.h" // Quaternionを使うように修正済みのものをインクルード
#include "CameraComponent.h"    // CameraComponentの定義が必要
#include "Quaternion.h"         // 私たちが作成したQuaternion.hをインクルード
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

    // --- 1. 入力受付 ---
    VECTOR inputVec = VGet(0, 0, 0);
    if (CheckHitKey(KEY_INPUT_W)) { inputVec.z += 1.0f; }
    if (CheckHitKey(KEY_INPUT_S)) { inputVec.z -= 1.0f; }
    if (CheckHitKey(KEY_INPUT_A)) { inputVec.x -= 1.0f; }
    if (CheckHitKey(KEY_INPUT_D)) { inputVec.x += 1.0f; }

    // --- 2. 移動方向の計算 ---
    if (VSquareSize(inputVec) < 1e-6f)
    {
        transform->SetVelocity(VGet(0, 0, 0)); // 入力がなければ停止
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

    // --- 3. 速度の設定 ---
    VECTOR velocity = VScale(moveDir, m_moveSpeed);
    transform->SetVelocity(velocity);

    // --- 4. 旋回処理 ---
    // 【修正点】自作のQuaternionクラスを使用
    Quaternion currentRot = transform->GetRotation();

    float targetAngle = atan2f(moveDir.x, moveDir.z);
    Quaternion targetRot = Quaternion::FromEulerAngles(0.0f, targetAngle, 0.0f);

    Quaternion newRot = Quaternion::Slerp(currentRot, targetRot, deltaTime * m_rotationSpeed);

    transform->SetRotation(newRot);
}