#pragma once

#include "LogicComponent.h"
#include <memory>

class TransformComponent;
class EntitySystem;
class BulletPrototype;

// �e�̔��˂ƃN�[���_�E���𐧌䂷��R���|�[�l���g
class BulletShooterComponent : public LogicComponent
{
public:
    // ���g��Transform�͓n�����A�O���̃V�X�e����݌v�}���󂯎��
    BulletShooterComponent(EntitySystem* entitySystem, std::shared_ptr<BulletPrototype> prototype);

    void Start() override;
    void Update(float deltaTime) override;

    // ���˃��N�G�X�g
    void RequestShoot();

    // �N�[���_�E�����Ԃ�b���Őݒ�
    void SetCooldown(float seconds);

private:
    void Shoot(); // �����I�Ȕ��ˏ���

    std::shared_ptr<TransformComponent> m_transform;
    EntitySystem* m_entitySystem;
    std::shared_ptr<BulletPrototype> m_prototype;

    // �^�C�}�[�ƃN�[���_�E����b��(float)�ŊǗ�
    float m_cooldownTime = 0.3f; // �f�t�H���g��0.3�b
    float m_timer = 0.0f;
    bool m_isShootRequested = false;
};