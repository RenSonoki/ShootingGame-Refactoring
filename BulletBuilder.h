#pragma once
#include "DxLib.h"
#include <string>
#include <memory>

// �O���錾
class BulletEntity;

// BulletEntity�̍\�z����ɍs���r���_�[�N���X
class BulletBuilder
{
public:
    BulletBuilder();

    // ���\�b�h�`�F�[���Őݒ���q������悤�ɁA���g�̎Q�Ƃ�Ԃ�
    BulletBuilder& SetPosition(const VECTOR& pos);
    BulletBuilder& SetDirection(const VECTOR& dir);
    BulletBuilder& SetSpeed(float speed);
    BulletBuilder& SetLifetime(float lifetime);
    BulletBuilder& SetModel(const std::wstring& modelPath);
    BulletBuilder& SetCollisionRadius(float radius);

    // �ŏI�I�ɐݒ������BulletEntity���\�z���ĕԂ�
    std::shared_ptr<BulletEntity> Build() const;

private:
    // �\�z�ɕK�v�ȃp�����[�^��ێ�
    VECTOR m_pos;
    VECTOR m_dir;
    float m_speed;
    float m_lifetime;
    std::wstring m_modelPath;
    float m_collisionRadius;
};