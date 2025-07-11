#pragma once

#include <string>
#include <memory>
#include <functional>
#include "DxLib.h"

// �O���錾
class EnemyEntity;
class TransformComponent;

// �G�̃e���v���[�g�i�݌v�}�j
class EnemyPrototype
{
public:
    EnemyPrototype();

    // �v���g�^�C�v�̐ݒ�p���\�b�h
    void SetModelPath(const std::wstring& path);
    void SetSpeed(float speed);
    void SetCollisionRadius(float radius);
    void SetScore(int score);
    void SetOnDestroyCallback(std::function<void(int)> callback);

    // ���̐݌v�}����A�V�����G�G���e�B�e�B�𕡐��i�N���[���j����
    std::shared_ptr<EnemyEntity> Clone(const VECTOR& spawnPos, std::shared_ptr<TransformComponent> targetTransform) const;

private:
    std::wstring m_modelPath;
    float m_speed = 5.0f;
    float m_radius = 1.5f;
    int m_score = 100;
    std::function<void(int)> m_onDestroyCallback;
};