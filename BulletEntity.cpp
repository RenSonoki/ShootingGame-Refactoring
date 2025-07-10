#include "BulletEntity.h"
#include "TransformComponent.h"
#include "RenderModelComponent.h"
#include "MoveComponent.h"
#include "LifetimeComponent.h"
#include "SphereCollisionComponent.h"

BulletEntity::BulletEntity(
        const VECTOR& pos, 
        const VECTOR& dir, 
        float speed, 
        float lifetimeInSeconds, 
        const std::wstring& modelPath
    )
{
    SetTag(L"Bullet");

    // --- �e�R���|�[�l���g�𐶐����A�A�^�b�`���Ă��� ---
    // �ŐV�̐݌v�ł́A�R���|�[�l���g�Ԃ̈ˑ��֌W���蓮�Ōq���K�v�͂Ȃ�

    // 1. TransformComponent: �ʒu������ݒ�
    auto transform = std::make_shared<TransformComponent>();
    transform->SetPosition(pos);
    AddComponent(transform);

    // 2. RenderModelComponent: ���f���p�X���w�肷�邾��
    AddComponent(std::make_shared<RenderModelComponent>(modelPath));

    // 3. MoveComponent: ���x�ƕ�����ݒ�
    auto move = std::make_shared<MoveComponent>(speed);
    move->SetDirection(dir);
    AddComponent(move);

    // 4. LifetimeComponent: ������b���Őݒ�
    auto life = std::make_shared<LifetimeComponent>(lifetimeInSeconds);
    life->SetOnExpired([this]()
        {
        // �������s������A���g���A�N�e�B�u�ɂ���
        this->SetActive(false);
        });
    AddComponent(life);

    // 5. SphereCollisionComponent: ���a���w�肷�邾��
    auto collider = std::make_shared<SphereCollisionComponent>(0.5f);
    collider->SetOnCollision([this](Entity* other)
        {
        // �Փ˂�������̃^�O�� "Enemy" ��������...
        if (other && other->GetTag() == L"Enemy")
        {
            // ���g���A�N�e�B�u�ɂ���i���ł�����j
            this->SetActive(false);
        }
        });
    AddComponent(collider);
}