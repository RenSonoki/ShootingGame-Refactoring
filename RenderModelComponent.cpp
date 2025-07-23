#include "RenderModelComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <DxLib.h>
#include <cassert>

// �� �C���_: �f�t�H���g�R���X�g���N�^�̎���
RenderModelComponent::RenderModelComponent()
    : m_modelPath(L"")
    , m_modelHandle(-1)
{
}

// �� �C���_: �f�X�g���N�^�Ń��f����������A���������[�N��h��
RenderModelComponent::~RenderModelComponent()
{
    if (m_modelHandle != -1)
    {
        MV1DeleteModel(m_modelHandle);
        m_modelHandle = -1;
    }
}

void RenderModelComponent::Start()
{
    // Start�̐Ӗ��́A���̃R���|�[�l���g�ւ̎Q�Ƃ��������邱��
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(!m_transform.expired() && "RenderModelComponent requires a TransformComponent.");
}

ComponentID RenderModelComponent::GetID() const
{
    return ComponentID::ModelRenderer;
}

bool RenderModelComponent::SetModel(const std::wstring& modelPath)
{
    // ���ɕʂ̃��f����ǂݍ���ł���΁A��ɉ������
    if (m_modelHandle != -1)
    {
        MV1DeleteModel(m_modelHandle);
    }

    m_modelPath = modelPath;
    // DxLib�̋@�\�Ń��f����ǂݍ��݁A�n���h����ێ�
    m_modelHandle = MV1LoadModel(modelPath.c_str());

    return m_modelHandle != -1;
}

int RenderModelComponent::GetModelHandle() const
{
    return m_modelHandle;
}

void RenderModelComponent::Draw() const
{
    auto transform = m_transform.lock();
    if (m_modelHandle == -1 || !transform)
    {
        return;
    }

    // ���[���h�s��̌v�Z��TransformComponent�Ɋ��S�ɔC����
    MATRIX worldMat = transform->GetWorldMatrix();
    MV1SetMatrix(m_modelHandle, worldMat);
    MV1DrawModel(m_modelHandle);
}