#pragma once
#include <string>
#include <memory>

// �O���錾
class PlayerEntity;
class EntitySystem;
class BulletPrototype;

class PlayerBuilder
{
public:
    PlayerBuilder();

    // ���\�b�h�`�F�[���Őݒ���q������悤�ɁA���g�̎Q�Ƃ�Ԃ�
    PlayerBuilder& SetModel(const std::wstring& modelPath);
    PlayerBuilder& SetShooterInfo(std::shared_ptr<BulletPrototype> prototype, EntitySystem* entitySystem);
    PlayerBuilder& SetInitialHealth(int maxHP, float invincibilitySec);
    PlayerBuilder& SetCollisionRadius(float radius);

    // �ŏI�I�ɐݒ������PlayerEntity���\�z���ĕԂ�
    std::shared_ptr<PlayerEntity> Build() const;

private:
    // �\�z�ɕK�v�ȃp�����[�^��ێ�
    std::wstring m_modelPath;
    std::shared_ptr<BulletPrototype> m_bulletPrototype;
    EntitySystem* m_entitySystem;
    int m_maxHP;
    float m_initialInvincibility;
    float m_collisionRadius;
};