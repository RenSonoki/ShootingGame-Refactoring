#pragma once
#include <memory>

// 前方宣言
class IScene;

// ゲーム全体の制御を行うクラス
class Game
{
private:
    // NOTE: 所有権を持つポインタで現在のシーンを管理
    std::unique_ptr<IScene> m_currentScene;

public:
    Game();
    ~Game(); // NOTE: unique_ptrが前方宣言された型を安全に破棄するためにデストラクタを宣言

    void Update(float deltaTime);
    void Draw() const;

    // NOTE: 引数の所有権をmoveで受け取る
    void ChangeScene(std::unique_ptr<IScene> newScene);
};