#pragma once

#include "IScene.h"
#include <memory>
#include <vector>

// �O���錾
class EntitySystem;
class CameraSystem;
class UIManager;
class PlayerEntity;
class EnemyPrototype;
class BulletPrototype;
class UIText;
class Game;

// �Q�[���v���C�V�[��
class PlayScene : public IScene
{
public:
    PlayScene();
    ~PlayScene();

    void OnEnter(Game& game) override;
    void OnExit(Game& game) override;
    void Update(float deltaTime, Game& game) override;
    void Draw() override;

private:
    void SpawnEnemy();
    void AddScore(int value);
    void UpdateUI();

    // �V�X�e��
    std::unique_ptr<EntitySystem> m_entitySystem;
    std::unique_ptr<CameraSystem> m_cameraSystem;
    std::unique_ptr<UIManager> m_uiManager;

    // �G���e�B�e�B�ƃv���g�^�C�v
    std::shared_ptr<PlayerEntity> m_player;
    std::shared_ptr<EnemyPrototype> m_enemyPrototype;
    std::shared_ptr<BulletPrototype> m_bulletPrototype;

    // UI�v�f�ւ̎Q��
    std::shared_ptr<UIText> m_scoreText;
    std::shared_ptr<UIText> m_hpText;

    // ��ԕϐ�
    int m_score = 0;
    float m_enemySpawnTimer = 0.0f;

    // ���\�[�X�n���h��
    int m_bgmHandle = -1;
    int m_groundTextureHandle = -1;
};