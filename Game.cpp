#include "Game.h"
#include "ResourceManager.h"
#include "TitleScene.h" // �� cpp���Ō���I�� include

Game::Game()
{
    // �N�����Ƀ^�C�g���V�[����\��
    // ChangeScene(std::make_unique<TitleScene>());
}

//void Game::Update()
//{
//    if (m_currentScene)
//        m_currentScene->Update(*this);
//}


void Game::Update(float deltaTime) // �������ύX
{
    if (m_currentScene)
        m_currentScene->Update(deltaTime, *this); // deltaTime ���n��
}

void Game::Draw()
{
    if (m_currentScene)
        m_currentScene->Draw();
}

void Game::ChangeScene(std::unique_ptr<IScene> newScene)
{
    if (m_currentScene)
        m_currentScene->OnExit(*this);

    m_currentScene = std::move(newScene);

    if (m_currentScene)
        m_currentScene->OnEnter(*this);
}