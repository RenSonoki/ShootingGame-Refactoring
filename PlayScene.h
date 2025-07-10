//#pragma once
//
//#include "IScene.h"
//#include "EntitySystem.h"
//#include "UIManager.h"
//#include "PlayerEntity.h"
//#include "EnemyPrototype.h"
//#include "BulletPrototype.h"
//#include "CameraSystem.h"
//#include <memory>
//#include <vector>
//
//// �v���C�V�[��
//class PlayScene : public IScene
//{
//private:
//    // �G���e�B�e�B�Ǘ�
//    EntitySystem m_entitySystem;
//    CameraSystem m_cameraSystem;
//    std::shared_ptr<PlayerEntity> m_player;
//
//    // �v���g�^�C�v
//    std::shared_ptr<EnemyPrototype> m_enemyPrototype;
//    std::shared_ptr<BulletPrototype> m_bulletPrototype;
//
//    // UI
//    std::unique_ptr<UIManager> m_uiManager;
//    std::shared_ptr<class UIText> m_scoreText;
//    std::shared_ptr<class UIText> m_hpText;
//
//    // �w�i�E�n��
//    int m_backgroundHandle = -1;
//    int m_groundTextureHandle = -1;
//    int m_statusBackgroundHandle = -1;
//
//    // ���f���n���h��
//    int m_playerModelHandle = -1;
//    int m_enemyModelHandle = -1;
//
//    // �X�R�A�Ǘ�
//    int m_score = 0;
//
//    // �G�����^�C�}�[
//    int m_enemySpawnTimer = 0;
//
//    // BGM��SE�i�C�Ӂj
//    int m_shootSEHandle = -1;
//    int m_bgmHandle = -1;
//
//public:
//    PlayScene();
//
//    // �V�[���J�n��
//    void OnEnter(Game& game) override;
//
//    // �V�[���I����
//    void OnExit(Game& game) override;
//
//    // �X�V����
//    void Update(Game& game) override;
//
//    // �`�揈��
//    void Draw() override;
//
//private:
//    // �G����
//    // void SpawnEnemy();
//
//    // �X�R�A�X�V
//    void AddScore(int value);
//};
