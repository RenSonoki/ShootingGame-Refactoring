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

 /*   void Update();*/
    void Draw();

    // エラー解決のために一時記述
    void Update(float deltaTime); // deltaTime を引数に追加

    void ChangeScene(std::unique_ptr<IScene> newScene);
};