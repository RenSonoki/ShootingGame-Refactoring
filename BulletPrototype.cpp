#include "BulletPrototype.h"
#include "BulletBuilder.h" // Builder���g���č\�z����

// �� �f�t�H���g�R���X�g���N�^�̎���
BulletPrototype::BulletPrototype()
    : m_modelPath(L"")
    , m_speed(100.0f)
    , m_lifetime(3.0f)
{
}

// �� �Z�b�^�[�̎���
void BulletPrototype::SetModel(const std::wstring& modelPath) { m_modelPath = modelPath; }
void BulletPrototype::SetSpeed(float speed) { m_speed = speed; }
void BulletPrototype::SetLifetime(float lifetime) { m_lifetime = lifetime; }

// Clone���\�b�h��Builder���g��
std::shared_ptr<BulletEntity> BulletPrototype::Clone(const VECTOR& position, const VECTOR& direction) const
{
    BulletBuilder builder;
    auto bullet = builder.SetPosition(position)
        .SetDirection(direction)
        .SetModel(m_modelPath)
        .SetSpeed(m_speed)
        .SetLifetime(m_lifetime)
        .Build();

    return bullet;
}