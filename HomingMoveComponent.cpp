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
    // ���g��TransformComponent���擾
    m_selfTransform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_selfTransform != nullptr && "HomingMoveComponent requires a TransformComponent.");
}

void HomingMoveComponent::SetTarget(std::shared_ptr<TransformComponent> target)
{
    // �^�[�Q�b�g����Q�Ƃŕێ�
    m_targetTransform = target;
}

void HomingMoveComponent::Update(float deltaTime)
{
    // weak_ptr����shared_ptr���擾���A�^�[�Q�b�g�����݂��邩�m�F
    auto target = m_targetTransform.lock();

    if (!m_selfTransform || !target)
    {
        // ���g���^�[�Q�b�g���Ȃ���Α��x���[���ɂ��Ē�~
        if (m_selfTransform)
        {
            m_selfTransform->SetVelocity(VGet(0, 0, 0));
        }
        return;
    }

    VECTOR currentPos = m_selfTransform->GetPosition();
    VECTOR targetPos = target->GetPosition();

    // �^�[�Q�b�g�ւ̕����x�N�g�����v�Z���A���K��
    VECTOR dir = VSub(targetPos, currentPos);
    if (VSquareSize(dir) < 1e-6f)
    {
        // �قړ����ʒu�ɂ���ꍇ�͒�~
        m_selfTransform->SetVelocity(VGet(0, 0, 0));
        return;
    }
    VECTOR normalizedDir = VNorm(dir);

    // �ŏI�I�ȑ��x���v�Z���A���g��TransformComponent�ɃZ�b�g����
    VECTOR velocity = VScale(normalizedDir, m_speed);
    m_selfTransform->SetVelocity(velocity);
}