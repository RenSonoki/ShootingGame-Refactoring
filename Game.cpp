#include "Game.h"
#include "IScene.h"       // ISceneの完全な定義をインクルード
#include "TitleScene.h"   // 具体的なシーンはここでインクルード

// デストラクタを定義（中身は空でOK）
// この実装がcpp側にあることで、コンパイラはISceneのデストラクタを知ることができる
Game::~Game() = default;

Game::Game()
{
    // 起動時にタイトルシーンに遷移
    ChangeScene(std::make_unique<TitleScene>());
}

void Game::Update(float deltaTime)
{
    if (m_currentScene)
    {
        m_currentScene->Update(deltaTime, *this);
    }
}

void Game::Draw() const // const化
{
    if (m_currentScene)
    {
        // 前回の提案に合わせて、IScene::Draw に const な *this を渡す
        m_currentScene->Draw(*this);
    }
}

void Game::ChangeScene(std::unique_ptr<IScene> newScene)
{
    if (m_currentScene)
    {
        m_currentScene->OnExit(*this);
    }

	// NOTE: std::moveを使うことで、newSceneの所有権をm_currentSceneに移す
    m_currentScene = std::move(newScene);

    if (m_currentScene)
    {
        m_currentScene->OnEnter(*this);
    }
}