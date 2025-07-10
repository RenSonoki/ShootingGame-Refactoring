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

 /*   void Update();*/
    void Draw();

    // �G���[�����̂��߂Ɉꎞ�L�q
    void Update(float deltaTime); // deltaTime �������ɒǉ�

    void ChangeScene(std::unique_ptr<IScene> newScene);
};