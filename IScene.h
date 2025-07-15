#pragma once

// 前方宣言
class Game;

// シーンの抽象基底クラス
// NOTE: Stateパターンを使用して、ゲームの状態を管理
class IScene
{
public:
    virtual ~IScene() = default;

    virtual void OnEnter(Game& game) = 0;

    virtual void Update(float deltaTime, Game& game) = 0;

    virtual void OnExit(Game& game) = 0;

    virtual void Draw(const Game& game) const = 0;
};