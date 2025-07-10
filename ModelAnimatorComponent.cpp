#include "ModelAnimatorComponent.h"
#include "Entity.h"
#include "RenderModelComponent.h" // �A�g���邽�߂ɃC���N���[�h
#include <DxLib.h>
#include <cassert>

ModelAnimatorComponent::ModelAnimatorComponent() {}

void ModelAnimatorComponent::Start()
{
    // RenderModelComponent���烂�f���n���h�����擾
    auto renderComponent = GetOwner()->GetComponent<RenderModelComponent>();
    assert(renderComponent != nullptr && "ModelAnimatorComponent requires a RenderModelComponent.");

    m_modelHandle = renderComponent->GetModelHandle();
    assert(m_modelHandle != -1 && "Invalid model handle for animation.");

    // �A�j���[�V�������̃L���b�V�����\�z
	// ����ɂ��A�A�j���[�V����������C���f�b�N�X�������Ɍ����ł���悤�ɂȂ�
    BuildAnimationCache();
}

// deltaTime ���g���Ď��Ԃ�i�߂�
void ModelAnimatorComponent::Update(float deltaTime)
{
    if (!m_isPlaying || m_playHandle == -1 || m_modelHandle == -1) return;

    // ���݂̃A�j���[�V�������Ԃ��擾
    float currentTime = MV1GetAttachAnimTime(m_modelHandle, m_playHandle);

    // 1�b������̍Đ����x * �o�ߎ��� �ŁA���̃t���[���Ői�ނׂ����Ԃ��v�Z
    currentTime += m_speed * deltaTime;

    // �A�j���[�V�����̑����Ԃ��擾
    float totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_playHandle);

    if (currentTime >= totalTime)
    {
        if (m_loop)
        {
            // ���[�v�Đ��̏ꍇ�́A�����ԂŊ������]���V�������ԂƂ���
            currentTime = fmod(currentTime, totalTime);
        }
        else
        {
            Stop();
            // �Đ��I���Ȃ̂ŁA�ŏI�t���[���Ŏ~�߂�
            MV1SetAttachAnimTime(m_modelHandle, m_playHandle, totalTime);
            return;
        }
    }

    MV1SetAttachAnimTime(m_modelHandle, m_playHandle, currentTime);
}

void ModelAnimatorComponent::SetAnimation(int index, bool loop, float speed)
{
    if (m_modelHandle == -1 || index < 0) return;

    // ���ɍĐ����̃A�j���[�V����������΃f�^�b�`�i�t���O���j����
    if (m_playHandle != -1)
    {
        MV1DetachAnim(m_modelHandle, m_playHandle);
    }

    m_currentAnimIndex = index;
    m_loop = loop;
    m_speed = speed;

    // �V�����A�j���[�V�������A�^�b�`
    m_playHandle = MV1AttachAnim(m_modelHandle, m_currentAnimIndex, -1, FALSE); // ���[�v�͎蓮�Ő���
    MV1SetAttachAnimTime(m_modelHandle, m_playHandle, 0.0f);

    Play(); // �Đ��J�n
}

void ModelAnimatorComponent::SetAnimationByName(const std::wstring& name, bool loop, float speed)
{
    int index = FindAnimationIndexByName(name);
    if (index != -1)
    {
        SetAnimation(index, loop, speed);
    }
}

// �L���b�V�����\�z����w���p�[
void ModelAnimatorComponent::BuildAnimationCache()
{
    if (m_modelHandle == -1) return;

    m_animNameToIndex.clear();
    int animCount = MV1GetAnimNum(m_modelHandle);
    for (int i = 0; i < animCount; ++i)
    {
        const wchar_t* animName = MV1GetAnimName(m_modelHandle, i);
        if (animName)
        {
            m_animNameToIndex[animName] = i;
        }
    }
}

// �L���b�V�����g���č�������
int ModelAnimatorComponent::FindAnimationIndexByName(const std::wstring& name)
{
    auto it = m_animNameToIndex.find(name);
    if (it != m_animNameToIndex.end())
    {
        return it->second; // ��������
    }
    return -1; // ������Ȃ�����
}

void ModelAnimatorComponent::Play() { m_isPlaying = true; }
void ModelAnimatorComponent::Stop() { m_isPlaying = false; }
bool ModelAnimatorComponent::IsPlaying() const { return m_isPlaying; }