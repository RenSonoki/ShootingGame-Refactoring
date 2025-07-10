#pragma once

#include "Entity.h"
#include "DxLib.h"
#include <string>
#include <memory>

// 弾エンティティの設計図
class BulletEntity : public Entity
{
public:
    // 位置、方向、速度、寿命（秒）、モデルを指定して弾を生成
    BulletEntity(
        const VECTOR& pos,
        const VECTOR& dir,
        float speed,
        float lifetimeInSeconds,
        const std::wstring& modelPath);
};