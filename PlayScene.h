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
//// プレイシーン
//class PlayScene : public IScene
//{
//private:
//    // エンティティ管理
//    EntitySystem m_entitySystem;
//    CameraSystem m_cameraSystem;
//    std::shared_ptr<PlayerEntity> m_player;
//
//    // プロトタイプ
//    std::shared_ptr<EnemyPrototype> m_enemyPrototype;
//    std::shared_ptr<BulletPrototype> m_bulletPrototype;
//
//    // UI
//    std::unique_ptr<UIManager> m_uiManager;
//    std::shared_ptr<class UIText> m_scoreText;
//    std::shared_ptr<class UIText> m_hpText;
//
//    // 背景・地面
//    int m_backgroundHandle = -1;
//    int m_groundTextureHandle = -1;
//    int m_statusBackgroundHandle = -1;
//
//    // モデルハンドル
//    int m_playerModelHandle = -1;
//    int m_enemyModelHandle = -1;
//
//    // スコア管理
//    int m_score = 0;
//
//    // 敵生成タイマー
//    int m_enemySpawnTimer = 0;
//
//    // BGMやSE（任意）
//    int m_shootSEHandle = -1;
//    int m_bgmHandle = -1;
//
//public:
//    PlayScene();
//
//    // シーン開始時
//    void OnEnter(Game& game) override;
//
//    // シーン終了時
//    void OnExit(Game& game) override;
//
//    // 更新処理
//    void Update(Game& game) override;
//
//    // 描画処理
//    void Draw() override;
//
//private:
//    // 敵生成
//    // void SpawnEnemy();
//
//    // スコア更新
//    void AddScore(int value);
//};
