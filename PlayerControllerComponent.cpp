#include "PlayerControllerComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "DxLib.h"
#include <cassert>

PlayerControllerComponent::PlayerControllerComponent()
    : m_transform(nullptr)
{
}

void PlayerControllerComponent::Start()
{
    // オーナーからTransformComponentを取得してキャッシュ
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_transform != nullptr && "PlayerControllerComponent requires a TransformComponent.");
}

void PlayerControllerComponent::SetMoveSpeed(float speed)
{
    m_moveSpeed = speed;
}

float PlayerControllerComponent::GetMoveSpeed() const
{
    return m_moveSpeed;
}

void PlayerControllerComponent::Update(float deltaTime)
{
    if (!m_transform) return;

    VECTOR inputVec = VGet(0, 0, 0);

    if (CheckHitKey(KEY_INPUT_W)) { inputVec.z += 1.0f; }
    if (CheckHitKey(KEY_INPUT_S)) { inputVec.z -= 1.0f; }
    if (CheckHitKey(KEY_INPUT_A)) { inputVec.x -= 1.0f; }
    if (CheckHitKey(KEY_INPUT_D)) { inputVec.x += 1.0f; }

    // 入力がない場合は何もしない
    if (VSquareSize(inputVec) < 0.0001f)
    {
        // プレイヤーを停止させるために、速度をゼロにする
        m_transform->SetVelocity(VGet(0, 0, 0));
        return;
    }

    // 入力ベクトルを正規化（単位ベクトル化）して、斜め移動が速くならないようにする
    VECTOR moveDir = VNorm(inputVec);

    // 最終的な速度を計算し、TransformComponentにセットする
    // NOTE: 入力と実際の処理を分離
    VECTOR velocity = VScale(moveDir, m_moveSpeed);
    m_transform->SetVelocity(velocity);
}