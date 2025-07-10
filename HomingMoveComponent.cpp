#include "HomingMoveComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <DxLib.h>
#include <cassert>

HomingMoveComponent::HomingMoveComponent(float speed)
    : m_speed(speed), m_selfTransform(nullptr)
{
}

void HomingMoveComponent::Start()
{
    // 自身のTransformComponentを取得
    m_selfTransform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_selfTransform != nullptr && "HomingMoveComponent requires a TransformComponent.");
}

void HomingMoveComponent::SetTarget(std::shared_ptr<TransformComponent> target)
{
    // ターゲットを弱参照で保持
    m_targetTransform = target;
}

void HomingMoveComponent::Update(float deltaTime)
{
    // weak_ptrからshared_ptrを取得し、ターゲットが存在するか確認
    auto target = m_targetTransform.lock();

    if (!m_selfTransform || !target)
    {
        // 自身かターゲットがなければ速度をゼロにして停止
        if (m_selfTransform)
        {
            m_selfTransform->SetVelocity(VGet(0, 0, 0));
        }
        return;
    }

    VECTOR currentPos = m_selfTransform->GetPosition();
    VECTOR targetPos = target->GetPosition();

    // ターゲットへの方向ベクトルを計算し、正規化
    VECTOR dir = VSub(targetPos, currentPos);
    if (VSquareSize(dir) < 1e-6f)
    {
        // ほぼ同じ位置にいる場合は停止
        m_selfTransform->SetVelocity(VGet(0, 0, 0));
        return;
    }
    VECTOR normalizedDir = VNorm(dir);

    // 最終的な速度を計算し、自身のTransformComponentにセットする
    VECTOR velocity = VScale(normalizedDir, m_speed);
    m_selfTransform->SetVelocity(velocity);
}