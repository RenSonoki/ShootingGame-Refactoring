#pragma once

#include "LogicComponent.h"
#include <memory>
#include <DxLib.h>

// �O���錾
class TransformComponent; 

// �������ɑ��x�ňړ�������R���|�[�l���g
class MoveComponent : public LogicComponent
{
public:
    MoveComponent();

    void Start() override;
    void Update(float deltaTime) override;

    void SetDirection(const VECTOR& dir);
    void SetSpeed(float speed);

private:
    std::shared_ptr<TransformComponent> m_transform;
    VECTOR m_direction = VGet(0, 0, 1); // �f�t�H���g��Z��������
    float m_speed = 10.0f;
};