#pragma once

#include "LogicComponent.h"
#include <string>
#include <unordered_map>

// モデルアニメーションの制御を行うコンポーネント
class ModelAnimatorComponent : public LogicComponent
{
public:
    ModelAnimatorComponent();

    // ライフサイクルメソッド
    void Start() override;
    void Update(float deltaTime) override;

    // アニメーション設定
    void SetAnimation(int index, bool loop = true, float speed = 1.0f);
    void SetAnimationByName(const std::wstring& name, bool loop = true, float speed = 1.0f);

    // 再生／停止
    void Play();
    void Stop();
    bool IsPlaying() const;

private:
    int m_modelHandle = -1;
    int m_playHandle = -1;
    int m_currentAnimIndex = -1;
    bool m_loop = true;
    float m_speed = 30.0f; // 1秒あたり30フレーム進む、のような意味合いに
    bool m_isPlaying = false;

    // アニメーション名検索用のキャッシュ
    std::unordered_map<std::wstring, int> m_animNameToIndex;

    // ヘルパー関数をStartの外に
    void BuildAnimationCache();
    int FindAnimationIndexByName(const std::wstring& name);
};