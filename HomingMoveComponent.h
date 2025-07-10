#pragma once

#include "LogicComponent.h"
#include <memory>

class TransformComponent;

// ����̑Ώۂ֌������Ĉړ�����R���|�[�l���g
class HomingMoveComponent : public LogicComponent
{
public:
    explicit HomingMoveComponent(float speed);

    void Start() override;
    void Update(float deltaTime) override;

    // �ǔ��Ώۂ̐ݒ�
    void SetTarget(std::shared_ptr<TransformComponent> target);

private:
    std::shared_ptr<TransformComponent> m_selfTransform;

    // �^�[�Q�b�g�͎�Q��(weak_ptr)�Ŏ��̂������S
    std::weak_ptr<TransformComponent> m_targetTransform;
    float m_speed = 1.0f;
};