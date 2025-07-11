#include "ThirdPersonCameraComponent.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "DxLib.h"
#include <cassert>

ThirdPersonCameraComponent::ThirdPersonCameraComponent(std::weak_ptr<TransformComponent> targetTransform)
    : m_targetTransform(targetTransform)
    , m_offset(VGet(0.0f, 5.0f, -10.0f)) // デフォルト：少し上、少し後ろ
{
}

void ThirdPersonCameraComponent::Start()
{
    // 自身がアタッチされているエンティティのCameraComponentを取得
    m_camera = GetOwner()->GetComponent<CameraComponent>();
    assert(m_camera != nullptr && "ThirdPersonCameraComponent requires a CameraComponent.");
}

void ThirdPersonCameraComponent::Update(float deltaTime)
{
    if (!m_camera) return;

    // weak_ptrからshared_ptrを取得（ターゲットが破棄されていないか確認）
    auto target = m_targetTransform.lock();
    if (!target)
    {
        // ターゲットがいない（シーンから削除されたなど）場合は何もしない
        return;
    }

    // --- カメラの位置と注視点を計算 ---

    // 1. ターゲット（プレイヤー）の位置を取得
    VECTOR targetPos = target->GetPosition();

    // 2. カメラの理想的な位置を計算
    //    (単純なオフセット。将来的にはターゲットの向きも考慮するとより良くなる)
    VECTOR idealCameraPos = VAdd(targetPos, m_offset);

    // 3. カメラの位置と注視点を設定する
    m_camera->SetPosition(idealCameraPos);
    m_camera->SetTarget(targetPos); // カメラは常にターゲットの中心を見る
}

void ThirdPersonCameraComponent::SetOffset(const VECTOR& offset)
{
    m_offset = offset;
}