#pragma once

#include <string>
#include <memory>
#include <functional>
#include "DxLib.h"

// 前方宣言
class EnemyEntity;
class TransformComponent;

// 敵のテンプレート（設計図）
class EnemyPrototype
{
public:
    EnemyPrototype();

    // プロトタイプの設定用メソッド
    void SetModelPath(const std::wstring& path);
    void SetSpeed(float speed);
    void SetCollisionRadius(float radius);
    void SetScore(int score);
    void SetOnDestroyCallback(std::function<void(int)> callback);

    // この設計図から、新しい敵エンティティを複製（クローン）する
    std::shared_ptr<EnemyEntity> Clone(const VECTOR& spawnPos, std::shared_ptr<TransformComponent> targetTransform) const;

private:
    std::wstring m_modelPath;
    float m_speed = 5.0f;
    float m_radius = 1.5f;
    int m_score = 100;
    std::function<void(int)> m_onDestroyCallback;
};