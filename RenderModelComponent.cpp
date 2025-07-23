#include "RenderModelComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <DxLib.h>
#include <cassert>

// ★ 修正点: デフォルトコンストラクタの実装
RenderModelComponent::RenderModelComponent()
    : m_modelPath(L"")
    , m_modelHandle(-1)
{
}

// ★ 修正点: デストラクタでモデルを解放し、メモリリークを防ぐ
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
    // Startの責務は、他のコンポーネントへの参照を解決すること
    m_transform = GetOwner()->GetComponent<TransformComponent>();
    assert(!m_transform.expired() && "RenderModelComponent requires a TransformComponent.");
}

ComponentID RenderModelComponent::GetID() const
{
    return ComponentID::ModelRenderer;
}

bool RenderModelComponent::SetModel(const std::wstring& modelPath)
{
    // 既に別のモデルを読み込んでいれば、先に解放する
    if (m_modelHandle != -1)
    {
        MV1DeleteModel(m_modelHandle);
    }

    m_modelPath = modelPath;
    // DxLibの機能でモデルを読み込み、ハンドルを保持
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

    // ワールド行列の計算はTransformComponentに完全に任せる
    MATRIX worldMat = transform->GetWorldMatrix();
    MV1SetMatrix(m_modelHandle, worldMat);
    MV1DrawModel(m_modelHandle);
}