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
    // �I�[�i�[����TransformComponent���擾���ăL���b�V��
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

    // ���͂��Ȃ��ꍇ�͉������Ȃ�
    if (VSquareSize(inputVec) < 0.0001f)
    {
        // �v���C���[���~�����邽�߂ɁA���x���[���ɂ���
        m_transform->SetVelocity(VGet(0, 0, 0));
        return;
    }

    // ���̓x�N�g���𐳋K���i�P�ʃx�N�g�����j���āA�΂߈ړ��������Ȃ�Ȃ��悤�ɂ���
    VECTOR moveDir = VNorm(inputVec);

    // �ŏI�I�ȑ��x���v�Z���ATransformComponent�ɃZ�b�g����
    // NOTE: ���͂Ǝ��ۂ̏����𕪗�
    VECTOR velocity = VScale(moveDir, m_moveSpeed);
    m_transform->SetVelocity(velocity);
}