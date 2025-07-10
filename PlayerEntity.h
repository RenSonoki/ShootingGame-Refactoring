#pragma once

#include "Entity.h"
#include <memory>
#include <string>

// �O���錾
class TransformComponent;
class HealthComponent;
class BulletShooterComponent;
class BulletPrototype;
class EntitySystem;

// �v���C���[�L�����N�^�[�̐݌v�}�ƂȂ�G���e�B�e�B�N���X
class PlayerEntity : public Entity
{
public:
    // �����ɕK�v�ȏ����R���X�g���N�^�Ŏ󂯎��
    PlayerEntity(const std::wstring& modelPath,
        EntitySystem* entitySystem,                          // �e�𐶐����邽�߂ɕK�v
        std::shared_ptr<BulletPrototype> bulletPrototype);

    // GetComponent<T>()�𒼐ڌĂяo���悤�ɕύX
    std::shared_ptr<TransformComponent> GetTransform() const;
    std::shared_ptr<HealthComponent> GetHealth() const;
    std::shared_ptr<BulletShooterComponent> GetShooter() const;

    int GetHP() const;
    bool IsAlive() const;
};