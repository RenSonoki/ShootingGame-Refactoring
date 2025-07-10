#include "RenderModelComponent.h"
#include "ResourceManager.h"
#include "Entity.h" // GetOwner() �� GetComponent() �̂��߂ɕK�v
#include "TransformComponent.h"
#include <DxLib.h>
#include <cassert>


RenderModelComponent::RenderModelComponent(const std::wstring& modelPath)
{
    m_modelPath = modelPath;
}

void RenderModelComponent::Start()
{
    // ResourceManager�o�R�ł̃��f���ǂݍ��݂�Start�Ɉړ�
    if (!m_modelPath.empty())
    {
        // �ėp��ResourceManager��z��
        m_modelHandle = ResourceManager::Instance().Get<ModelTag>(m_modelPath);
    }

    // �I�[�i�[�G���e�B�e�B����A�ˑ�����TransformComponent���擾���ăL���b�V������
    m_transform = GetOwner()->GetComponent<TransformComponent>();

    // �ˑ��R���|�[�l���g��������Ȃ��ꍇ�̓G���[���o���i�f�o�b�O���ɋC�Â��₷���悤�Ɂj
    assert(m_transform != nullptr && "RenderModelComponent requires a TransformComponent on the same Entity.");
}

void RenderModelComponent::SetModel(const std::wstring& modelPath)
{
    m_modelPath = modelPath;
    m_modelHandle = ResourceManager::Instance().Get<ModelTag>(m_modelPath);
}

int RenderModelComponent::GetModelHandle() const
{
    return m_modelHandle;
}

void RenderModelComponent::Draw()
{
    if (m_modelHandle == -1 || !m_transform) return;

    // DX���C�u�����̍s��֐����g���āA��萳�m�Ȉʒu�A��]�A�g�k�𔽉f������
    MATRIX mat_scale, mat_rot, mat_trans, mat_world;

    // �g�k�A��]�A���s�ړ��̍s������ꂼ��쐬
    mat_scale = MGetIdent(); // ���͊g�k�͓��{
    mat_rot = MGetRotY(m_transform->GetRotation().y); // Y����]�݂̂��Ƃ���
    mat_trans = MGetTranslate(m_transform->GetPosition());

    // ���[���h�s������� (�g�k -> ��] -> ���s�ړ��̏�����ʓI)
    mat_world = MMult(mat_scale, mat_rot);
    mat_world = MMult(mat_world, mat_trans);

    // ���[���h�s������f���ɐݒ�
    MV1SetMatrix(m_modelHandle, mat_world);

    // ���f����`��
    MV1DrawModel(m_modelHandle);
}