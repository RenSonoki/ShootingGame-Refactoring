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
    // �I�[�i�[����TransformComponent���擾
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_transform != nullptr && "MoveComponent requires a TransformComponent.");
}

void MoveComponent::SetDirection(const VECTOR& dir)
{
    // �����͏�ɐ��K���i����1�j���ĕێ�����
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
        // ���������Ȃ��Ȃ�A�O�̂��ߑ��x��0�ɂ��Ă���
        if (m_transform)
        {
            m_transform->SetVelocity(VGet(0, 0, 0));
        }
        return;
    }

    // ���g�̐Ӗ��́A���x�x�N�g�����v�Z����Transform�ɃZ�b�g���邱�Ƃ���
    VECTOR velocity = VScale(m_direction, m_speed);
    m_transform->SetVelocity(velocity);
}