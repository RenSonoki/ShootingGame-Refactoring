#pragma once

#include "ComponentBase.h"
#include <DxLib.h>
#include <memory>

// �O���錾
class TransformComponent;
class Entity;

/**
 * @class MoveComponent
 * @brief �G���e�B�e�B���������Ɏw�肳�ꂽ���x�ňړ�������R���|�[�l���g
 *
 * ���̃R���|�[�l���g�́A�I�[�i�[�G���e�B�e�B��TransformComponent�𑀍삵�āA
 * �p���I�Ɉړ������܂��B�ړ������Ƒ��x�͊O������ݒ�\�ł��B
 */
class MoveComponent : public ComponentBase
{
public:
    /**
     * @brief �R���X�g���N�^
     */
    MoveComponent();

    ComponentID GetID() const override;

    /**
     * @brief �����������B�I�[�i�[����K�v�ȃR���|�[�l���g���擾���܂��B
     * ���̃R���|�[�l���g��TransformComponent�Ɉˑ����܂��B
     */
    void Start() override;

    /**
     * @brief ���t���[���̍X�V�����B���x���v�Z���ATransformComponent�ɓK�p���܂��B
     * @param deltaTime �O�̃t���[������̌o�ߎ��ԁi�b�j
     */
    void Update(float deltaTime) override;

    /**
     * @brief �ړ�������ݒ肵�܂��B�x�N�g���͎����I�ɐ��K������܂��B
     * @param direction �V�����ړ������x�N�g��
     */
    void SetDirection(const VECTOR& direction);

    /**
     * @brief �ړ����x��ݒ肵�܂��B
     * @param speed �V�������x
     */
    void SetSpeed(float speed);

    /**
     * @brief ���݂̈ړ��������擾���܂��B
     * @return ���K�����ꂽ�ړ������x�N�g��
     */
    const VECTOR& GetDirection() const;

    /**
     * @brief ���݂̈ړ����x���擾���܂��B
     * @return ���x
     */
    float GetSpeed() const;

private:
    // --- �萔 ---
    static constexpr float DEFAULT_SPEED = 10.0f;
    static const VECTOR DEFAULT_DIRECTION;

    // --- �����o�ϐ� ---
    std::shared_ptr<TransformComponent> m_transform;
    VECTOR m_normalizedDirection; // ���K���ς݂̈ړ�����
    float m_speed;
};