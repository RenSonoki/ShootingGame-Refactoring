#include "BulletPrototype.h"
#include "BulletEntity.h" // ������BulletEntity�̃w�b�_

BulletPrototype::BulletPrototype(const std::wstring& modelPath,float speed,float lifetimeInSeconds)
    : m_modelPath(modelPath)
    , m_speed(speed)
    , m_lifetimeInSeconds(lifetimeInSeconds)
{
}

// ���ꂪ���C���Ŏg���N���[�����\�b�h
std::shared_ptr<Entity> BulletPrototype::Clone(const VECTOR& position, const VECTOR& direction) const
{
    return std::make_shared<BulletEntity>(position, direction, m_speed, m_lifetimeInSeconds, m_modelPath);
}

// --- �ȉ���IEntityPrototype�C���^�[�t�F�[�X���������邽�߂̂��܂� ---

std::shared_ptr<Entity> BulletPrototype::Clone() const
{
    // �f�t�H���g�ʒu�AZ+�����Ő���
    return Clone({ 0,0,0 }, { 0,0,1 });
}

std::shared_ptr<Entity> BulletPrototype::CloneWithTransform(const VECTOR& position) const
{
    // �w��ʒu�AZ+�����Ő���
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