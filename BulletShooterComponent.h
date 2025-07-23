#pragma once
#include "ComponentBase.h" // �� ���N���X��ύX
#include <memory>
#include <functional>

// �O���錾
class TransformComponent;
class EntitySystem;
class BulletPrototype;
class Entity;

/**
 * @class BulletShooterComponent
 * @brief �e�̔��˂ƃN�[���_�E���𐧌䂷��R���|�[�l���g
 */
class BulletShooterComponent : public ComponentBase
{
public:
    // �� �C���_: �f�t�H���g�R���X�g���N�^�ɕύX
    BulletShooterComponent();
    virtual ~BulletShooterComponent() = default;

    ComponentID GetID() const override;

    void Start() override;
    void Update(float deltaTime) override;

    /**
     * @brief ���̃V���[�^�[���g�p����݌v�}�ƁA�e��ǉ�����V�X�e����ݒ肵�܂�
     * @param prototype �e�̐݌v�}
     * @param entitySystem �e�̒ǉ���ƂȂ�V�X�e��
     */
    void Setup(std::shared_ptr<BulletPrototype> prototype, EntitySystem* entitySystem);

    // ���˃��N�G�X�g
    void RequestShoot();

    // �N�[���_�E�����Ԃ�b���Őݒ�
    void SetCooldown(float seconds);

    // ���ݔ��ˉ\���i�N�[���_�E�����I����Ă��邩�j
    bool CanShoot() const;

private:
    void Shoot(); // �����I�Ȕ��ˏ���

    std::shared_ptr<TransformComponent> m_transform;
    EntitySystem* m_entitySystem;
    std::shared_ptr<BulletPrototype> m_prototype;

    float m_cooldownTime;
    float m_timer;
    bool m_isShootRequested;
};