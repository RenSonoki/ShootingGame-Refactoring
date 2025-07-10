#pragma once

#include "Entity.h"
#include <memory>
#include <functional>
#include <string> // wstring�̂���
#include <DxLib.h>

class TransformComponent;

// �G�L�����N�^�[�̐݌v�}�ƂȂ�G���e�B�e�B�N���X
class EnemyEntity : public Entity
{
public:
    // �����ɕK�v�ȏ����R���X�g���N�^�Ŏ󂯎��
    EnemyEntity
    (
        const VECTOR& position,
        const std::wstring& modelPath,
        float speed,
        float collisionRadius
    );

    // �^�[�Q�b�g�̃Z�b�g�́A������ɊO������s��
    void SetTarget(std::shared_ptr<TransformComponent> target);

    void SetScore(int score);
    void SetOnDestroyCallback(std::function<void(int)> callback);

private:
    int m_score = 100;
    std::function<void(int)> m_onDestroyCallback;
};