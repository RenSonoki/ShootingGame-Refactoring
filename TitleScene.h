#pragma once
#include "IScene.h"
#include <memory>

// 前方宣言
class EntitySystem;
class UISystem;
class CameraSystem;
class Game;

// ゲームのタイトル画面
class TitleScene : public IScene
{
public:
    TitleScene();
    ~TitleScene();

	// ISceneの実装
    void OnEnter(Game& game) override;
    void OnExit(Game& game) override;
    void Update(float deltaTime, Game& game) override;
    void Draw() override;

private:

    std::unique_ptr<EntitySystem> m_entitySystem;
    std::unique_ptr<UISystem> m_uiSystem;
    std::unique_ptr<CameraSystem> m_cameraSystem;

    bool m_isStartRequested = false;
    int m_bgmHandle = -1;
    int m_decideSEHandle = -1;
};