#include "Game.h"
#include "IScene.h"       // IScene�̊��S�Ȓ�`���C���N���[�h
#include "TitleScene.h"   // ��̓I�ȃV�[���͂����ŃC���N���[�h

// �f�X�g���N�^���`�i���g�͋��OK�j
// ���̎�����cpp���ɂ��邱�ƂŁA�R���p�C����IScene�̃f�X�g���N�^��m�邱�Ƃ��ł���
Game::~Game() = default;

Game::Game()
{
    // �N�����Ƀ^�C�g���V�[���ɑJ��
    ChangeScene(std::make_unique<TitleScene>());
}

void Game::Update(float deltaTime)
{
    if (m_currentScene)
    {
        m_currentScene->Update(deltaTime, *this);
    }
}

void Game::Draw() const // const��
{
    if (m_currentScene)
    {
        // �O��̒�Ăɍ��킹�āAIScene::Draw �� const �� *this ��n��
        m_currentScene->Draw(*this);
    }
}

void Game::ChangeScene(std::unique_ptr<IScene> newScene)
{
    if (m_currentScene)
    {
        m_currentScene->OnExit(*this);
    }

	// NOTE: std::move���g�����ƂŁAnewScene�̏��L����m_currentScene�Ɉڂ�
    m_currentScene = std::move(newScene);

    if (m_currentScene)
    {
        m_currentScene->OnEnter(*this);
    }
}