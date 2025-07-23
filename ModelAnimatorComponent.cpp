#include "ModelAnimatorComponent.h"
#include "Entity.h"
#include "RenderModelComponent.h"
#include <DxLib.h>
#include <cassert>

ModelAnimatorComponent::ModelAnimatorComponent() = default;

void ModelAnimatorComponent::Start()
{
    // �A�g����RenderModelComponent�ւ̎Q�Ƃ��擾
    m_renderComponent = GetOwner()->GetComponent<RenderModelComponent>();
    assert(!m_renderComponent.expired() && "ModelAnimatorComponent requires a RenderModelComponent.");

    // �A�j���[�V�������̃L���b�V�����\�z
    BuildAnimationCache();
}

ComponentID ModelAnimatorComponent::GetID() const
{
    // ComponentID��Animator�Ȃǂ�ǉ����Ă�������
    return ComponentID::Animator;
}

void ModelAnimatorComponent::PlayAnimation(int index, bool loop, float speed)
{
    auto renderComp = m_renderComponent.lock();
    if (!renderComp || index < 0 || index >= m_totalAnimNum) return;

    const int modelHandle = renderComp->GetModelHandle();
    if (modelHandle == -1) return;

    // ���ɍĐ����̃A�j���[�V����������΃f�^�b�`����
    if (m_playHandle != -1)
    {
        MV1DetachAnim(modelHandle, m_playHandle);
    }

    m_currentAnimIndex = index;

    // DX���C�u�����̋@�\�Ń��[�v�ƍĐ����Ԃ�ݒ�
    // ��3�����Ƀ��[�v�t���O��n��
    m_playHandle = MV1AttachAnim(modelHandle, m_currentAnimIndex, -1, loop ? TRUE : FALSE);
    // �Đ����x��ݒ�i1.0���W�����x�j
    MV1SetAttachAnimBlendRate(modelHandle, m_playHandle, speed);
}

void ModelAnimatorComponent::PlayAnimationByName(const std::wstring& name, bool loop, float speed)
{
    int index = FindAnimationIndexByName(name);
    if (index != -1)
    {
        PlayAnimation(index, loop, speed);
    }
}

void ModelAnimatorComponent::StopAnimation()
{
    auto renderComp = m_renderComponent.lock();
    if (!renderComp || m_playHandle == -1) return;

    const int modelHandle = renderComp->GetModelHandle();
    if (modelHandle != -1)
    {
        MV1DetachAnim(modelHandle, m_playHandle);
    }
    m_playHandle = -1;
    m_currentAnimIndex = -1;
}

bool ModelAnimatorComponent::IsPlaying() const
{
    // �Đ��n���h�����L�����ǂ����ōĐ���Ԃ𔻒f
    return m_playHandle != -1;
}

void ModelAnimatorComponent::BuildAnimationCache()
{
    auto renderComp = m_renderComponent.lock();
    if (!renderComp) return;

    const int modelHandle = renderComp->GetModelHandle();
    if (modelHandle == -1) return;

    m_animNameToIndex.clear();
    m_totalAnimNum = MV1GetAnimNum(modelHandle);
    for (int i = 0; i < m_totalAnimNum; ++i)
    {
        const wchar_t* animName = MV1GetAnimName(modelHandle, i);
        if (animName)
        {
            m_animNameToIndex[animName] = i;
        }
    }
}

int ModelAnimatorComponent::FindAnimationIndexByName(const std::wstring& name) const
{
    auto it = m_animNameToIndex.find(name);
    return (it != m_animNameToIndex.end()) ? it->second : -1;
}