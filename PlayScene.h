#pragma once
#include "IScene.h"
#include <memory>
#include <Windows.h>

// --- �O���錾 ---
// ���̃V�[�������p�����v�ȃN���X��O���錾���Ă������ƂŁA
// �w�b�_�[�t�@�C���Ԃ̕s�v�ȃC���N���[�h�����炵�A�R���p�C�����Ԃ�Z�k���܂��B
class EntitySystem;
class MovementSystem;
class CameraSystem;
class UIManager;
class PlayerEntity;
class EnemySpawner;
class Game;
class UIText;

/**
 * @class PlayScene
 * @brief �Q�[���v���C���̏�Ԃ��Ǘ�����V�[���N���X�B
 * @details ���̃N���X�́A�e��V�X�e���⃍�W�b�N���N���X�����L���A
 * �����ɏ������ϔC����u����ēv�̂悤�Ȗ�����S���܂��B
 */
class PlayScene : public IScene
{
public:
    PlayScene();
    ~PlayScene() override;

    // IScene�C���^�[�t�F�[�X�̎���
    void OnEnter(Game& game) override;
    void OnExit(Game& game) override;
    void Update(float deltaTime, Game& game) override;
    void Draw(const Game& game) const override;

private:
    // UI�̕\�����e���X�V����w���p�[�֐�
    void UpdateUI();

    // --- ���̃V�[�������L����V�X�e���Q ---
    std::unique_ptr<EntitySystem> m_entitySystem;     // �Q�[�����I�u�W�F�N�g(Entity)�̃��C�t�T�C�N�����Ǘ�
    std::unique_ptr<MovementSystem> m_movementSystem;   // �������Z�i�ړ������j����ɒS��
    std::unique_ptr<CameraSystem> m_cameraSystem;     // �J�����̊Ǘ��Ɛݒ�K�p��S��
    std::unique_ptr<UIManager> m_uiManager;          // UI���C���[(UISystem)�̊Ǘ���S��

    // --- ���W�b�N���N���X ---
    std::unique_ptr<EnemySpawner> m_enemySpawner;     // �G�̏o�����W�b�N����ɒS��

    // --- ��v�ȃI�u�W�F�N�g�ւ̎Q�� ---
    std::shared_ptr<PlayerEntity> m_player; // �v���C���[�ւ̎Q��

    // UI�v�f�ւ̃|�C���^�iUI�̕\���X�V�Ɏg���j
    UIText* m_scoreText = nullptr;
    UIText* m_hpText = nullptr;

    // --- ���\�[�X�n���h�� ---
    int m_bgmHandle = -1;
};