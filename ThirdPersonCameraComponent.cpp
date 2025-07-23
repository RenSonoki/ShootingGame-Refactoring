#include "ThirdPersonCameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "Quaternion.h"
#include "DebugRenderer.h"
#include <cassert>
#include <algorithm> // std::clamp
#include <cmath>     // std::exp

// �� ������const�Q�ƂɕύX
static MATRIX CreateMatrixFromForwardVector(const VECTOR& forward, const VECTOR& up)
{
    VECTOR z_axis = VNorm(forward);
    VECTOR x_axis = VNorm(VCross(up, z_axis));
    VECTOR y_axis = VCross(z_axis, x_axis);

    MATRIX m = MGetIdent();
    m.m[0][0] = x_axis.x; m.m[0][1] = x_axis.y; m.m[0][2] = x_axis.z;
    m.m[1][0] = y_axis.x; m.m[1][1] = y_axis.y; m.m[1][2] = y_axis.z;
    m.m[2][0] = z_axis.x; m.m[2][1] = z_axis.y; m.m[2][2] = z_axis.z;
    return m;
}

ThirdPersonCameraComponent::ThirdPersonCameraComponent()
    : // �� �C���_: �^�[�Q�b�g�Ƃ̋������A�Ⴆ��100��200�Ƃ������傫�Ȓl�ɂ��Ă݂�
    m_idealDistance(200.0f)
    , m_targetOffset(VGet(0, 50.0f, 50.0f)) // �� �I�t�Z�b�g�����f���̑傫���ɍ��킹�� (��: �g��30)
    , m_rotationSpeed(2.0f)
    , m_lerpSpeed(15.0f)
    , m_yaw(0.0f)
    , m_pitch(0.2f)
{
}

ComponentID ThirdPersonCameraComponent::GetID() const
{
    // ComponentID��ThirdPersonCamera�Ȃǂ�ǉ����Ă�������
    return ComponentID::ThirdPersonCamera;
}


void ThirdPersonCameraComponent::Start()
{
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    m_camera = GetOwner()->GetComponent<CameraComponent>();
    assert(!m_transform.expired() && "ThirdPersonCameraComponent requires a TransformComponent.");
    assert(!m_camera.expired() && "ThirdPersonCameraComponent requires a CameraComponent.");
}

void ThirdPersonCameraComponent::SetTarget(std::weak_ptr<TransformComponent> target) { m_target = target; }
void ThirdPersonCameraComponent::SetDistance(float distance) { m_idealDistance = distance; }
void ThirdPersonCameraComponent::SetOffset(const VECTOR& offset) { m_targetOffset = offset; }


void ThirdPersonCameraComponent::Update(float deltaTime)
{
    auto transform = m_transform.lock();
    auto target = m_target.lock();
    if (!transform || !target) return;

    // --- 1. ���͂ɂ��J�����̉�] ---
    // (InputManager�Ȃǂ���}�E�X�̈ړ��������擾����)
    // float mouseDeltaX = InputManager::GetInstance().GetMouseDeltaX();
    // m_yaw += mouseDeltaX * m_rotationSpeed * deltaTime; // �� deltaTime���l��
    m_pitch = std::clamp(m_pitch, -0.5f, 1.5f);

    // --- 2. �J�����̗��z�I�Ȉʒu���v�Z ---
    Quaternion rotation = Quaternion::FromEulerAngles(m_pitch, m_yaw, 0.0f);
    VECTOR direction = VTransform(VGet(0, 0, -1), rotation.ToMatrix());
    VECTOR idealPosition = VAdd(target->GetPosition(), VScale(direction, m_idealDistance));

    // --- 3. ��Q���`�F�b�N ---
    VECTOR finalPosition = idealPosition;
    // Physics::Raycast(...) �̂悤�ȏ����������ɓ���

    // --- 4. �J������Transform�����炩�ɍX�V ---
    // �� �C���_: �t���[�����[�g�Ɉˑ����Ȃ����肵��Lerp�i���`��ԁj
    VECTOR currentPos = transform->GetPosition();
    float factor = 1.0f - std::exp(-m_lerpSpeed * deltaTime);
    transform->SetPosition(VAdd(currentPos, VScale(VSub(finalPosition, currentPos), factor)));

    // �����̍X�V (��Ƀ^�[�Q�b�g�̒����_������)
    VECTOR lookAtTarget = VAdd(target->GetPosition(), m_targetOffset);
    VECTOR lookDir = VSub(lookAtTarget, transform->GetPosition());

#if _DEBUG
    // �� �f�o�b�O�`������N�G�X�g
    // �J�����̈ʒu�ɐ�����`��
    DebugRenderer::GetInstance().AddSphere(transform->GetPosition(), 1.0f, GetColor(0, 0, 255));
    // �J�������璍���_�։��F������`��
    DebugRenderer::GetInstance().AddLine(transform->GetPosition(), lookAtTarget, GetColor(255, 255, 0));
#endif

    if (VSquareSize(lookDir) > 1e-6f)
    {
        MATRIX lookAtMatrix = CreateMatrixFromForwardVector(lookDir, VGet(0, 1, 0));
        Quaternion targetRot = Quaternion::FromMatrix(lookAtMatrix);
        Quaternion currentRot = transform->GetRotation();

        // �� �C���_: Slerp�̕�ԗ����t���[�����[�g����Ɨ�������
        float rotFactor = 1.0f - std::exp(-m_lerpSpeed * 1.5f * deltaTime);
        Quaternion newRot = Quaternion::Slerp(currentRot, targetRot, rotFactor);

        transform->SetRotation(newRot);
    }
}