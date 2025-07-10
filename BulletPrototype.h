#pragma once

#include "IEntityPrototype.h"
#include <string>
#include <memory>
#include "DxLib.h" // VECTORのため

// 弾エンティティのプロトタイプ（設計図）
class BulletPrototype : public IEntityPrototype
{
public:
    BulletPrototype(const std::wstring& modelPath, float speed, float lifetimeInSeconds);

    // Prototypeインターフェースの実装
    // Cloneのシグネチャを、より実用的なものに変更
    std::shared_ptr<Entity> Clone(const VECTOR& position, const VECTOR& direction) const;

    // IEntityPrototypeの仮想関数をオーバーライドするために残すが、あまり使わない
    std::shared_ptr<Entity> Clone() const override;
    std::shared_ptr<Entity> CloneWithTransform(const VECTOR& position) const override;

    std::wstring GetName() const override;
    std::wstring GetCategory() const override;

    // (ゲッター/セッターは変更なし、ただしlifetimeの型はfloatに)
    void SetSpeed(float speed);
    void SetLifetime(float lifetimeInSeconds);
    // ...

private:
    std::wstring m_modelPath;
    float m_speed;
    float m_lifetimeInSeconds;
};