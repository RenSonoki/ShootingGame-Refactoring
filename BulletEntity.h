#pragma once

#include "Entity.h"
#include "DxLib.h"
#include <string>
#include <memory>

// �e�G���e�B�e�B�̐݌v�}
class BulletEntity : public Entity
{
public:
    // �ʒu�A�����A���x�A�����i�b�j�A���f�����w�肵�Ēe�𐶐�
    BulletEntity(
        const VECTOR& pos,
        const VECTOR& dir,
        float speed,
        float lifetimeInSeconds,
        const std::wstring& modelPath);
};