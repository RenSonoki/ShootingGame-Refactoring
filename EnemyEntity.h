#pragma once
#include "Entity.h"
#include <memory>
#include <functional>

class TransformComponent;

class EnemyEntity : public Entity
{
public:
    EnemyEntity(); // �� �f�t�H���g�R���X�g���N�^�ɕύX

    void SetTarget(std::shared_ptr<TransformComponent> target);
    void SetScore(int score);
    void SetOnDestroyCallback(std::function<void(int)> callback);

    // �� �Q�b�^�[��ǉ����Ă��ǂ�
    int GetScore() const;

private:
    int m_score = 100;
    std::function<void(int)> m_onDestroyCallback;
};