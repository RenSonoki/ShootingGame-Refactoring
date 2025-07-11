#pragma once

#include "IScene.h"
#include <memory>
#include <vector>

// 前方宣言
class EntitySystem;
class CameraSystem;
class UIManager;
class PlayerEntity;
class EnemyPrototype;
class BulletPrototype;
class UIText;
class Game;

// ゲームプレイシーン
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

    // システム
    std::unique_ptr<EntitySystem> m_entitySystem;
    std::unique_ptr<CameraSystem> m_cameraSystem;
    std::unique_ptr<UIManager> m_uiManager;

    // エンティティとプロトタイプ
    std::shared_ptr<PlayerEntity> m_player;
    std::shared_ptr<EnemyPrototype> m_enemyPrototype;
    std::shared_ptr<BulletPrototype> m_bulletPrototype;

    // UI要素への参照
    std::shared_ptr<UIText> m_scoreText;
    std::shared_ptr<UIText> m_hpText;

    // 状態変数
    int m_score = 0;
    float m_enemySpawnTimer = 0.0f;

    // リソースハンドル
    int m_bgmHandle = -1;
    int m_groundTextureHandle = -1;
};