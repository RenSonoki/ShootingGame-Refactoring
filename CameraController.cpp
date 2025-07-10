#include "CameraController.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include <DxLib.h>
#include <cmath>

CameraController::CameraController(std::shared_ptr<CameraComponent> camera)
    // NOTE: std::move�́AC++11�ȍ~�œ������ꂽ�@�\�ŁA�I�u�W�F�N�g�̏��L�����ړ����邽�߂Ɏg�p����܂��B
    : m_camera(std::move(camera))
{
}

void CameraController::SetTarget(std::shared_ptr<TransformComponent> target)
{
    m_target = std::move(target);
}

void CameraController::SetMode(CameraMode mode)
{
    m_mode = mode;
}

CameraMode CameraController::GetMode() const
{
    return m_mode;
}

void CameraController::SetOffset(const VECTOR& offset)
{
    m_offset = offset;
}

void CameraController::SetLerpSpeed(float speed)
{
    m_lerpSpeed = speed;
}

VECTOR CameraController::Lerp(const VECTOR& from, const VECTOR& to, float t)
{
    // from ���� to �� t �̊��������i�񂾃x�N�g�����v�Z
    return VAdd(from, VScale(VSub(to, from), t));
}

void CameraController::Update(float deltaTime)
{
    // ����Ώۂ̃J������^�[�Q�b�g���Ȃ���Ή������Ȃ�
    if (!m_camera) return;

    // �^�[�Q�b�g���ݒ肳��Ă��Ȃ���Ό��_����ɂ���
    VECTOR targetPos = m_target ? m_target->GetPosition() : VGet(0, 0, 0);
    VECTOR desiredPos = targetPos; // �J�����̍ŏI�I�ȖڕW�ʒu

    // �J�������[�h�ɉ����ĖڕW�ʒu������
    switch (m_mode)
    {
    case CameraMode::ThirdPerson:
        desiredPos = VAdd(targetPos, m_offset);
        break;

    case CameraMode::FirstPerson:
        desiredPos = targetPos;
        break;

    case CameraMode::Free:
        return; // Free���[�h�ł͂��̃R���|�[�l���g�̓J�����𐧌䂵�Ȃ�
    }

    // �t���[�����[�g�Ɉˑ����Ȃ��A���炩�Ȉړ��̂��߂̕�ԗ����v�Z
    float t = 1.0f - expf(-m_lerpSpeed * deltaTime);

    // ���݂̃J�����ʒu����A�v�Z�����ڕW�ʒu�֊��炩�Ɉړ�������
    const VECTOR currentPos = m_camera->GetPosition();
    const VECTOR newPos = Lerp(currentPos, desiredPos, t);

    m_camera->SetPosition(newPos);
    m_camera->SetTarget(targetPos);
}