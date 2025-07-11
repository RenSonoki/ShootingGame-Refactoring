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

    // --- �e�R���|�[�l���g���A�ŐV�̃A�[�L�e�N�`���ɉ����Đ����E�ݒ肵�A�A�^�b�` ---

    // 1. TransformComponent: ������Ɉʒu��ݒ�
    auto transform = std::make_shared<TransformComponent>();
    transform->SetPosition(pos);
    AddComponent(transform);

    // 2. RenderModelComponent: ���f���p�X���w�肷�邾��
    AddComponent(std::make_shared<RenderModelComponent>(modelPath));

    // ������ �������Ō�̏C���ӏ��ł� ������
    // 3. MoveComponent: �����Ȃ��Ő������A�Z�b�^�[�Őݒ肷��
    auto move = std::make_shared<MoveComponent>();
    move->SetSpeed(speed);
    move->SetDirection(dir);
    AddComponent(move);
    // ������ �����܂� ������

    // 4. LifetimeComponent: ������b���Őݒ�
    auto life = std::make_shared<LifetimeComponent>(lifetimeInSeconds);
    life->SetOnExpired([this]() {
        this->SetActive(false);
        });
    AddComponent(life);

    // 5. SphereCollisionComponent: ���a���w�肷�邾��
    auto collider = std::make_shared<SphereCollisionComponent>(0.5f);
    collider->SetOnCollision([this](Entity* other) {
        if (other && other->GetTag() == L"Enemy") {
            this->SetActive(false);
        }
        });
    AddComponent(collider);
}