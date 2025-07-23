#pragma once
#include <string>
#include <memory>
#include "DxLib.h"

// �O���錾
class Entity;
class BulletEntity;
class TransformComponent;

class BulletPrototype
{
public:
    // �� �f�t�H���g�R���X�g���N�^�ɕύX
    BulletPrototype();

    // �� �Z�b�^�[���\�b�h��ǉ�
    void SetModel(const std::wstring& modelPath);
    void SetSpeed(float speed);
    void SetLifetime(float lifetime);

    // ���̐݌v�}����V�����e�𕡐�����
    std::shared_ptr<BulletEntity> Clone(const VECTOR& position, const VECTOR& direction) const;

private:
    std::wstring m_modelPath;
    float m_speed;
    float m_lifetime;
};