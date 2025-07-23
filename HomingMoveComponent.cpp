#include "HomingMoveComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <DxLib.h>
#include <cassert>

HomingMoveComponent::HomingMoveComponent()
    : m_selfTransform(nullptr)
    , m_targetTransform() // weak_ptr�̓f�t�H���g�R���X�g���N�^�ŋ�ɂȂ�
    , m_speed(DEFAULT_SPEED)
{
}

ComponentID HomingMoveComponent::GetID() const
{
    return ComponentID::Homing;
}

void HomingMoveComponent::Start()
{
    // ���g��TransformComponent�͕p�ɂɎg�����߁A�ŏ��ɃL���b�V�����Ă����܂��B
    m_selfTransform = GetOwner()->GetComponent<TransformComponent>();
    assert(m_selfTransform != nullptr && "HomingMoveComponent requires a TransformComponent on its owner.");
}

void HomingMoveComponent::SetTarget(std::shared_ptr<TransformComponent> target)
{
    // �^�[�Q�b�g����Q��(weak_ptr)�ŕێ����邱�ƂŁA
    // �z�Q�Ƃ�h���A�^�[�Q�b�g���j�����ꂽ���Ƃ����S�Ɍ��m�ł��܂��B
    m_targetTransform = target;
}

void HomingMoveComponent::SetSpeed(float speed)
{
    m_speed = speed;
}

float HomingMoveComponent::GetSpeed() const
{
    return m_speed;
}

void HomingMoveComponent::Update(float deltaTime)
{
    // weak_ptr����shared_ptr���擾���A�^�[�Q�b�g���L�����m�F���܂��B
    // ���̃X�R�[�v�𔲂���ƁA���b�N�����|�C���^�͎����I�ɉ������܂��B
    auto target = m_targetTransform.lock();

    // ���g�A�܂��̓^�[�Q�b�g�����݂��Ȃ��ꍇ�́A���̏�Œ�~���܂��B
    if (!m_selfTransform || !target)
    {
        if (m_selfTransform)
        {
            m_selfTransform->SetVelocity(VGet(0.0f, 0.0f, 0.0f));
        }
        return;
    }

    // ���g�ƃ^�[�Q�b�g�̍��W���擾���܂��B
    const VECTOR currentPos = m_selfTransform->GetPosition();
    const VECTOR targetPos = target->GetPosition();

    // �^�[�Q�b�g�ւ̕����x�N�g�����v�Z���܂��B
    const VECTOR dir = VSub(targetPos, currentPos);

    // ���ɋ߂������ɂ���ꍇ�́A�U����h�����߂ɒ�~���܂��B
    // VSize()�̕������v�Z������邽�߁A������2��Ŕ�r����̂������I�ł��B
    if (VSquareSize(dir) < 1e-6f) // 1e-6f�͏\���ɏ������l�̗�
    {
        m_selfTransform->SetVelocity(VGet(0.0f, 0.0f, 0.0f));
        return;
    }

    // �����x�N�g���𐳋K���i������1�Ɂj���܂��B
    const VECTOR normalizedDir = VNorm(dir);

    // �ŏI�I�ȑ��x�x�N�g�����v�Z���ATransformComponent�ɐݒ肵�܂��B
    const VECTOR velocity = VScale(normalizedDir, m_speed);
    m_selfTransform->SetVelocity(velocity);
}