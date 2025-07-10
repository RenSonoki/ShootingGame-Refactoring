#include "RenderModelComponent.h"
#include "ResourceManager.h"
#include "Entity.h" // GetOwner() と GetComponent() のために必要
#include "TransformComponent.h"
#include <DxLib.h>
#include <cassert>


RenderModelComponent::RenderModelComponent(const std::wstring& modelPath)
{
    m_modelPath = modelPath;
}

void RenderModelComponent::Start()
{
    // ResourceManager経由でのモデル読み込みをStartに移動
    if (!m_modelPath.empty())
    {
        // 汎用版ResourceManagerを想定
        m_modelHandle = ResourceManager::Instance().Get<ModelTag>(m_modelPath);
    }

    // オーナーエンティティから、依存するTransformComponentを取得してキャッシュする
    m_transform = GetOwner()->GetComponent<TransformComponent>();

    // 依存コンポーネントが見つからない場合はエラーを出す（デバッグ時に気づきやすいように）
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

    // DXライブラリの行列関数を使って、より正確な位置、回転、拡縮を反映させる
    MATRIX mat_scale, mat_rot, mat_trans, mat_world;

    // 拡縮、回転、平行移動の行列をそれぞれ作成
    mat_scale = MGetIdent(); // 今は拡縮は等倍
    mat_rot = MGetRotY(m_transform->GetRotation().y); // Y軸回転のみを例として
    mat_trans = MGetTranslate(m_transform->GetPosition());

    // ワールド行列を合成 (拡縮 -> 回転 -> 平行移動の順が一般的)
    mat_world = MMult(mat_scale, mat_rot);
    mat_world = MMult(mat_world, mat_trans);

    // ワールド行列をモデルに設定
    MV1SetMatrix(m_modelHandle, mat_world);

    // モデルを描画
    MV1DrawModel(m_modelHandle);
}