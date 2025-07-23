#pragma once
#include "Entity.h"
#include <memory>

// �O���錾
class TransformComponent;
class HealthComponent;
class BulletShooterComponent;

class PlayerEntity : public Entity
{
public:
    PlayerEntity();

    // �֗��ȃQ�b�^�[�͂��̂܂܎c���܂�
    std::shared_ptr<TransformComponent> GetTransform() const;
    std::shared_ptr<HealthComponent> GetHealth() const;
    std::shared_ptr<BulletShooterComponent> GetShooter() const;

    int GetHP() const;
    bool IsAlive() const;
    bool IsDead() const;
};