#include "ModelAnimatorComponent.h"
#include "Entity.h"
#include "RenderModelComponent.h" // 連携するためにインクルード
#include <DxLib.h>
#include <cassert>

ModelAnimatorComponent::ModelAnimatorComponent() {}

void ModelAnimatorComponent::Start()
{
    // RenderModelComponentからモデルハンドルを取得
    auto renderComponent = GetOwner()->GetComponent<RenderModelComponent>();
    assert(renderComponent != nullptr && "ModelAnimatorComponent requires a RenderModelComponent.");

    m_modelHandle = renderComponent->GetModelHandle();
    assert(m_modelHandle != -1 && "Invalid model handle for animation.");

    // アニメーション名のキャッシュを構築
	// これにより、アニメーション名からインデックスを高速に検索できるようになる
    BuildAnimationCache();
}

// deltaTime を使って時間を進める
void ModelAnimatorComponent::Update(float deltaTime)
{
    if (!m_isPlaying || m_playHandle == -1 || m_modelHandle == -1) return;

    // 現在のアニメーション時間を取得
    float currentTime = MV1GetAttachAnimTime(m_modelHandle, m_playHandle);

    // 1秒あたりの再生速度 * 経過時間 で、このフレームで進むべき時間を計算
    currentTime += m_speed * deltaTime;

    // アニメーションの総時間を取得
    float totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_playHandle);

    if (currentTime >= totalTime)
    {
        if (m_loop)
        {
            // ループ再生の場合は、総時間で割った余りを新しい時間とする
            currentTime = fmod(currentTime, totalTime);
        }
        else
        {
            Stop();
            // 再生終了なので、最終フレームで止める
            MV1SetAttachAnimTime(m_modelHandle, m_playHandle, totalTime);
            return;
        }
    }

    MV1SetAttachAnimTime(m_modelHandle, m_playHandle, currentTime);
}

void ModelAnimatorComponent::SetAnimation(int index, bool loop, float speed)
{
    if (m_modelHandle == -1 || index < 0) return;

    // 既に再生中のアニメーションがあればデタッチ（付け外し）する
    if (m_playHandle != -1)
    {
        MV1DetachAnim(m_modelHandle, m_playHandle);
    }

    m_currentAnimIndex = index;
    m_loop = loop;
    m_speed = speed;

    // 新しいアニメーションをアタッチ
    m_playHandle = MV1AttachAnim(m_modelHandle, m_currentAnimIndex, -1, FALSE); // ループは手動で制御
    MV1SetAttachAnimTime(m_modelHandle, m_playHandle, 0.0f);

    Play(); // 再生開始
}

void ModelAnimatorComponent::SetAnimationByName(const std::wstring& name, bool loop, float speed)
{
    int index = FindAnimationIndexByName(name);
    if (index != -1)
    {
        SetAnimation(index, loop, speed);
    }
}

// キャッシュを構築するヘルパー
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

// キャッシュを使って高速検索
int ModelAnimatorComponent::FindAnimationIndexByName(const std::wstring& name)
{
    auto it = m_animNameToIndex.find(name);
    if (it != m_animNameToIndex.end())
    {
        return it->second; // 見つかった
    }
    return -1; // 見つからなかった
}

void ModelAnimatorComponent::Play() { m_isPlaying = true; }
void ModelAnimatorComponent::Stop() { m_isPlaying = false; }
bool ModelAnimatorComponent::IsPlaying() const { return m_isPlaying; }