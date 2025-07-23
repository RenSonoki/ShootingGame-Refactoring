#pragma once
#include "IScene.h"
#include <memory>

// �O���錾
class EntitySystem; // �� EntitySystem��ǉ�
class UISystem;
class CameraSystem;
class Game;

/**
 * @class TitleScene
 * @brief �Q�[���̃^�C�g���V�[���BUI�ƃJ�����̊Ǘ����s���B
 */
class TitleScene : public IScene
{
public:
    TitleScene();
    ~TitleScene() override;

    // IScene�C���^�[�t�F�[�X�̎���
    void OnEnter(Game& game) override;
    void OnExit(Game& game) override;
    void Update(float deltaTime, Game& game) override;
    void Draw(const Game& game) const override;

private:
    // ���̃V�[�������L����V�X�e���Q
    std::unique_ptr<EntitySystem> m_entitySystem; // �� EntitySystem��ǉ�
    std::unique_ptr<UISystem> m_uiSystem;
    std::unique_ptr<CameraSystem> m_cameraSystem;

    // �V�[���ŗL�̏��
    bool m_isStartRequested;

    // ���\�[�X�n���h��
    int m_bgmHandle;
    int m_decideSEHandle;
};