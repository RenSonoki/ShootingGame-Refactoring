#pragma once
#include <memory>
#include "IScene.h"

// ゲーム全体の制御を行うクラス
class Game
{
private:
	// NOTE: 所有権を持つポインタで現在のシーンを管理
    std::unique_ptr<IScene> m_currentScene;

public:
    Game();

    void Update(float deltaTime);

    void Draw();

    void ChangeScene(std::unique_ptr<IScene> newScene);
};