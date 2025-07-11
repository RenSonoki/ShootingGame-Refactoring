#include "ThirdPersonCameraComponent.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "DxLib.h"
#include <cassert>

ThirdPersonCameraComponent::ThirdPersonCameraComponent(std::weak_ptr<TransformComponent> targetTransform)
    : m_targetTransform(targetTransform)
    , m_offset(VGet(0.0f, 5.0f, -10.0f)) // �f�t�H���g�F������A�������
{
}

void ThirdPersonCameraComponent::Start()
{
    // ���g���A�^�b�`����Ă���G���e�B�e�B��CameraComponent���擾
    m_camera = GetOwner()->GetComponent<CameraComponent>();
    assert(m_camera != nullptr && "ThirdPersonCameraComponent requires a CameraComponent.");
}

void ThirdPersonCameraComponent::Update(float deltaTime)
{
    if (!m_camera) return;

    // weak_ptr����shared_ptr���擾�i�^�[�Q�b�g���j������Ă��Ȃ����m�F�j
    auto target = m_targetTransform.lock();
    if (!target)
    {
        // �^�[�Q�b�g�����Ȃ��i�V�[������폜���ꂽ�Ȃǁj�ꍇ�͉������Ȃ�
        return;
    }

    // --- �J�����̈ʒu�ƒ����_���v�Z ---

    // 1. �^�[�Q�b�g�i�v���C���[�j�̈ʒu���擾
    VECTOR targetPos = target->GetPosition();

    // 2. �J�����̗��z�I�Ȉʒu���v�Z
    //    (�P���ȃI�t�Z�b�g�B�����I�ɂ̓^�[�Q�b�g�̌������l������Ƃ��ǂ��Ȃ�)
    VECTOR idealCameraPos = VAdd(targetPos, m_offset);

    // 3. �J�����̈ʒu�ƒ����_��ݒ肷��
    m_camera->SetPosition(idealCameraPos);
    m_camera->SetTarget(targetPos); // �J�����͏�Ƀ^�[�Q�b�g�̒��S������
}

void ThirdPersonCameraComponent::SetOffset(const VECTOR& offset)
{
    m_offset = offset;
}