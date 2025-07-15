#pragma once

// �O���錾
class Game;

// �V�[���̒��ۊ��N���X
// NOTE: State�p�^�[�����g�p���āA�Q�[���̏�Ԃ��Ǘ�
class IScene
{
public:
    virtual ~IScene() = default;

    virtual void OnEnter(Game& game) = 0;

    virtual void Update(float deltaTime, Game& game) = 0;

    virtual void OnExit(Game& game) = 0;

    virtual void Draw(const Game& game) const = 0;
};