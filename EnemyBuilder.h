#pragma once
#include <string>
#include <memory>
#include "DxLib.h"

class EnemyEntity;

class EnemyBuilder
{
public:
    EnemyBuilder();

    EnemyBuilder& SetPosition(const VECTOR& position);
    EnemyBuilder& SetModel(const std::wstring& modelPath);
    EnemyBuilder& SetSpeed(float speed);
    EnemyBuilder& SetCollisionRadius(float radius);
    EnemyBuilder& SetInitialHealth(int maxHP);
    EnemyBuilder& SetScore(int score);

    // �� �C���_: �߂�l�� std::shared_ptr �ɕύX
    std::shared_ptr<EnemyEntity> Build() const;

private:
    VECTOR m_position;
    std::wstring m_modelPath;
    float m_speed;
    float m_collisionRadius;
    int m_maxHP;
    int m_score;
};