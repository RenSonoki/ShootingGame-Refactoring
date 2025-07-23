#include "GameManager.h"

GameManager& GameManager::GetInstance()
{
    // ���̊֐������߂ČĂ΂ꂽ���Ɉ�x�����C���X�^���X�����������
    static GameManager instance;
    return instance;
}

void GameManager::AddScore(int score)
{
    m_score += score;
}

void GameManager::Reset()
{
    m_score = 0;
}

int GameManager::GetScore() const
{
    return m_score;
}