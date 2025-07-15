#pragma once
#include <memory>

// �O���錾
class IScene;

// �Q�[���S�̂̐�����s���N���X
class Game
{
private:
    // NOTE: ���L�������|�C���^�Ō��݂̃V�[�����Ǘ�
    std::unique_ptr<IScene> m_currentScene;

public:
    Game();
    ~Game(); // NOTE: unique_ptr���O���錾���ꂽ�^�����S�ɔj�����邽�߂Ƀf�X�g���N�^��錾

    void Update(float deltaTime);
    void Draw() const;

    // NOTE: �����̏��L����move�Ŏ󂯎��
    void ChangeScene(std::unique_ptr<IScene> newScene);
};