#pragma once

#include "DrawComponent.h"
#include <memory>
#include <string>

// 前方宣言
class TransformComponent; 

// モデル描画を担当する DrawComponent
class RenderModelComponent : public DrawComponent
{
public:
    explicit RenderModelComponent(const std::wstring& modelPath);

    // 初期化処理
    void Start() override;

    // 描画処理
    void Draw() override;

    // モデルの差し替え
    void SetModel(const std::wstring& modelPath);

    // モデルハンドル取得
    int GetModelHandle() const;

private:
    int m_modelHandle = -1;
    std::wstring m_modelPath;

    // 依存するコンポーネントへのポインタ
    std::shared_ptr<TransformComponent> m_transform = nullptr;
};