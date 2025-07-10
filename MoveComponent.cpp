#include "MoveComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <DxLib.h>
#include <cassert>

MoveComponent::MoveComponent()
    : m_transform(nullptr)
{
}

void MoveComponent::Start()
{
    // オーナーからTransformComponentを取得
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_transform != nullptr && "MoveComponent requires a TransformComponent.");
}

void MoveComponent::SetDirection(const VECTOR& dir)
{
    // 方向は常に正規化（長さ1）して保持する
    m_direction = VNorm(dir);
}

void MoveComponent::SetSpeed(float speed)
{
    m_speed = speed;
}

void MoveComponent::Update(float deltaTime)
{
    if (!m_transform || m_speed == 0.0f)
    {
        // もし動かないなら、念のため速度を0にしておく
        if (m_transform)
        {
            m_transform->SetVelocity(VGet(0, 0, 0));
        }
        return;
    }

    // 自身の責務は、速度ベクトルを計算してTransformにセットすることだけ
    VECTOR velocity = VScale(m_direction, m_speed);
    m_transform->SetVelocity(velocity);
}