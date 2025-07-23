#pragma once

#include "ComponentBase.h"
#include <memory>

// �O���錾
class TransformComponent;

/**
 * @class HomingMoveComponent
 * @brief ����̑Ώۂ�ǔ����Ĉړ�����R���|�[�l���g
 */
class HomingMoveComponent : public ComponentBase
{
public:
    /**
     * @brief �R���X�g���N�^
     */
    HomingMoveComponent();

    ComponentID GetID() const override;

    /**
     * @brief �����������B���g��TransformComponent���擾���܂��B
     */
    void Start() override;

    /**
     * @brief ���t���[���̍X�V�B�^�[�Q�b�g�̕����������A���x���X�V���܂��B
     * @param deltaTime �O�̃t���[������̌o�ߎ��ԁi�b�j
     */
    void Update(float deltaTime) override;

    /**
     * @brief �ǔ��Ώۂ�TransformComponent��ݒ肵�܂��B
     * @param target �ǔ��������G���e�B�e�B��TransformComponent
     */
    void SetTarget(std::shared_ptr<TransformComponent> target);

    /**
     * @brief �ǔ����x��ݒ肵�܂��B
     * @param speed �ǔ����x
     */
    void SetSpeed(float speed);

    /**
     * @brief ���݂̒ǔ����x���擾���܂��B
     * @return �ǔ����x
     */
    float GetSpeed() const;

private:
    // --- �萔 ---
    static constexpr float DEFAULT_SPEED = 50.0f;

    // --- �����o�ϐ� ---
    std::shared_ptr<TransformComponent> m_selfTransform;
    std::weak_ptr<TransformComponent> m_targetTransform;
    float m_speed;
};