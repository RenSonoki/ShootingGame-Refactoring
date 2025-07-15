#pragma once
#include "ComponentBase.h"
#include <memory>

// ‘O•ûéŒ¾
class TransformComponent;
class CameraComponent;

class PlayerControllerComponent : public ComponentBase
{
public:
    PlayerControllerComponent();
    virtual ~PlayerControllerComponent() = default;

    void Start() override;
    void Update(float deltaTime) override;

    void SetCamera(std::shared_ptr<CameraComponent> camera);
    void SetMoveSpeed(float speed);
    void SetRotationSpeed(float speed);

private:
    std::weak_ptr<TransformComponent> m_transform;
    std::weak_ptr<CameraComponent> m_camera;

    float m_moveSpeed = 5.0f;
    float m_rotationSpeed = 10.0f; // ù‰ñ‘¬“x
};