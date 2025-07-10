#include "BulletPrototype.h"
#include "BulletEntity.h" // 正しいBulletEntityのヘッダ

BulletPrototype::BulletPrototype(const std::wstring& modelPath,float speed,float lifetimeInSeconds)
    : m_modelPath(modelPath)
    , m_speed(speed)
    , m_lifetimeInSeconds(lifetimeInSeconds)
{
}

// これがメインで使うクローンメソッド
std::shared_ptr<Entity> BulletPrototype::Clone(const VECTOR& position, const VECTOR& direction) const
{
    return std::make_shared<BulletEntity>(position, direction, m_speed, m_lifetimeInSeconds, m_modelPath);
}

// --- 以下はIEntityPrototypeインターフェースを実装するためのおまけ ---

std::shared_ptr<Entity> BulletPrototype::Clone() const
{
    // デフォルト位置、Z+方向で生成
    return Clone({ 0,0,0 }, { 0,0,1 });
}

std::shared_ptr<Entity> BulletPrototype::CloneWithTransform(const VECTOR& position) const
{
    // 指定位置、Z+方向で生成
    return Clone(position, { 0,0,1 });
}


std::wstring BulletPrototype::GetName() const
{
    return L"Standard Bullet";
}

std::wstring BulletPrototype::GetCategory() const
{
    return L"Projectile";
}

void BulletPrototype::SetSpeed(float speed) { m_speed = speed; }
void BulletPrototype::SetLifetime(float lifetimeInSeconds) { m_lifetimeInSeconds = lifetimeInSeconds; }