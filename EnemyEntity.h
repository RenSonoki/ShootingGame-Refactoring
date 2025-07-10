#pragma once

#include "Entity.h"
#include <memory>
#include <functional>
#include <string> // wstringのため
#include <DxLib.h>

class TransformComponent;

// 敵キャラクターの設計図となるエンティティクラス
class EnemyEntity : public Entity
{
public:
    // 生成に必要な情報をコンストラクタで受け取る
    EnemyEntity
    (
        const VECTOR& position,
        const std::wstring& modelPath,
        float speed,
        float collisionRadius
    );

    // ターゲットのセットは、生成後に外部から行う
    void SetTarget(std::shared_ptr<TransformComponent> target);

    void SetScore(int score);
    void SetOnDestroyCallback(std::function<void(int)> callback);

private:
    int m_score = 100;
    std::function<void(int)> m_onDestroyCallback;
};