#pragma once
#include <memory>
#include "IScene.h"

// �Q�[���S�̂̐�����s���N���X
class Game
{
private:
	// NOTE: ���L�������|�C���^�Ō��݂̃V�[�����Ǘ�
    std::unique_ptr<IScene> m_currentScene;

public:
    Game();

    void Update(float deltaTime);

    void Draw();

    void ChangeScene(std::unique_ptr<IScene> newScene);
};