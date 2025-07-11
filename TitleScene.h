#pragma once
#include "IScene.h"
#include <memory>

// �O���錾
class EntitySystem;
class UISystem;
class CameraSystem;
class Game;

// �Q�[���̃^�C�g�����
class TitleScene : public IScene
{
public:
    TitleScene();
    ~TitleScene();

	// IScene�̎���
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