#include "MovementSystem.h"
#include "Entity.h"
#include "TransformComponent.h" // Transform�𒼐ڑ��삷�邽�߃C���N���[�h
#include <DxLib.h>

void MovementSystem::Update(const std::vector<std::shared_ptr<Entity>>& entities, float deltaTime)
{
    // �Ǘ�����Ă���S�ẴG���e�B�e�B�����[�v
    for (const auto& entity : entities)
    {
        // �G���e�B�e�B���A�N�e�B�u�ŁATransformComponent�������Ă��邩�`�F�b�N
        if (entity && entity->IsActive())
        {
            if (auto transform = entity->GetComponent<TransformComponent>())
            {
                // ���x���擾
                const VECTOR& vel = transform->GetVelocity();

                // ���x��0�łȂ���΁A�ʒu���X�V
                if (VSquareSize(vel) > 1e-9f)
                {
                    VECTOR pos = transform->GetPosition();
                    pos = VAdd(pos, VScale(vel, deltaTime));
                    transform->SetPosition(pos);
                }
            }
        }
    }
}