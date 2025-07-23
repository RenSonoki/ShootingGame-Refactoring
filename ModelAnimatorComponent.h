#pragma once
#include "ComponentBase.h"
#include <string>
#include <unordered_map>
#include <memory>

class RenderModelComponent;

// モデルアニメーションの制御を行うコンポーネント
class ModelAnimatorComponent : public ComponentBase
{
public:
    ModelAnimatorComponent();
    virtual ~ModelAnimatorComponent() = default;

    // --- ライフサイクルメソッド ---
    void Start() override;
    // Updateでの時間管理は不要になるため、削除しても良い
    void Update(float deltaTime) override {}
    ComponentID GetID() const override;

    // --- アニメーション設定 ---
    void PlayAnimation(int index, bool loop = true, float speed = 1.0f);
    void PlayAnimationByName(const std::wstring& name, bool loop = true, float speed = 1.0f);

    // --- 再生制御 ---
    void StopAnimation();
    bool IsPlaying() const;

private:
    // 連携するコンポーネントへのポインタはweak_ptrで安全に保持
    std::weak_ptr<RenderModelComponent> m_renderComponent;

    // 現在再生中のアニメーション情報
    int m_totalAnimNum = 0;
    int m_playHandle = -1;
    int m_currentAnimIndex = -1;

    // アニメーション名検索用のキャッシュ
    std::unordered_map<std::wstring, int> m_animNameToIndex;

    // ヘルパー関数
    void BuildAnimationCache();
    int FindAnimationIndexByName(const std::wstring& name) const;
};