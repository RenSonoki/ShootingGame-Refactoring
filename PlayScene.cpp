#define NOMINMAX
#include <windows.h>
#include "PlayScene.h"
#include "TitleScene.h"
#include "ColliderManager.h"
#include "Game.h"
#include "ResourceManager.h"
#include "ResourceTraits.h"
#include "EntitySystem.h"
#include "CameraSystem.h"
#include "CameraController.h"
#include "UIManager.h"
#include "UISystem.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "EnemyPrototype.h"
#include "BulletPrototype.h"
#include "BulletShooterComponent.h"
#include "CameraEntity.h"
#include "UIText.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "DxLib.h"
#include <string>

// コンストラクタ
PlayScene::PlayScene()
{
    m_entitySystem = std::make_unique<EntitySystem>();
    m_cameraSystem = std::make_unique<CameraSystem>();
    m_uiManager = std::make_unique<UIManager>();

    m_bulletPrototype = std::make_shared<BulletPrototype>(
        L"Assets/Models/bullet.mv1", 50.0f, 3.0f
    );
    // 1. 引数なしで「空の設計図」を生成
    m_enemyPrototype = std::make_shared<EnemyPrototype>();

    // 2. セッターを使って、設計図のパラメータを設定
    m_enemyPrototype->SetModelPath(L"Assets/Models/enemy.mv1");
    m_enemyPrototype->SetSpeed(5.0f);
    m_enemyPrototype->SetCollisionRadius(1.5f);
    m_enemyPrototype->SetOnDestroyCallback([this](int score) { this->AddScore(score); });
}

PlayScene::~PlayScene() {}


void PlayScene::OnEnter(Game& game)
{
    m_bgmHandle = ResourceManager::Instance().Get<SoundTag>(L"Assets/Sounds/play_bgm.mp3");
    m_groundTextureHandle = ResourceManager::Instance().Get<ImageTag>(L"Assets/Textures/ground.png");
    if (m_bgmHandle != -1) PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);

    m_player = std::make_shared<PlayerEntity>(
        L"Assets/Models/player.pmx", m_entitySystem.get(), m_bulletPrototype
    );
    m_entitySystem->AddEntity(m_player);

    auto cameraEntity = std::make_shared<CameraEntity>();
    m_entitySystem->AddEntity(cameraEntity);
    m_cameraSystem->Register(cameraEntity);
    m_cameraSystem->SetActiveCamera(cameraEntity->GetCameraComponent());
    if (auto controller = cameraEntity->GetCameraController()) {
        controller->SetTarget(m_player->GetTransform());
    }

    auto gameUI = std::make_shared<UISystem>();
    m_uiManager->AddSystem("gameUI", gameUI);

    auto scoreEntity = std::make_shared<Entity>();
    m_scoreText = std::make_shared<UIText>(L"Score: 0", GetColor(255, 255, 0));
    m_scoreText->GetTransform().SetPosition({ 20, 20 });
    scoreEntity->AddComponent(m_scoreText);
    gameUI->RegisterEntity(scoreEntity);

    auto hpEntity = std::make_shared<Entity>();
    m_hpText = std::make_shared<UIText>(L"", GetColor(255, 255, 255));
    m_hpText->GetTransform().SetPosition({ 20, 50 });
    hpEntity->AddComponent(m_hpText);
    gameUI->RegisterEntity(hpEntity);

    m_entitySystem->Start();
}

void PlayScene::OnExit(Game& game) {
    if (m_bgmHandle != -1) StopSoundMem(m_bgmHandle);
}


void PlayScene::Update(float deltaTime, Game& game)
{
    // 1. システムの更新（deltaTimeを正しく渡す）
    m_entitySystem->Update(deltaTime);
    m_uiManager->UpdateAll();
    ColliderManager::Instance().CheckAllCollisions();

    // 2. ゲームロジック
    if (m_player && m_player->IsAlive())
    {
        if ((GetMouseInput() & MOUSE_INPUT_LEFT) || CheckHitKey(KEY_INPUT_Z)) {
            if (auto shooter = m_player->GetShooter()) {
                shooter->RequestShoot();
            }
        }
    }

    m_enemySpawnTimer += deltaTime;
    if (m_enemySpawnTimer > 3.0f) {
        m_enemySpawnTimer = 0.0f;
        SpawnEnemy();
    }

    // 3. UIの表示更新
    UpdateUI();

    // 4. ゲームオーバー判定
    if (m_player && !m_player->IsAlive())
    {
        game.ChangeScene(std::make_unique<TitleScene>());
    }
}

// Drawメソッドはほぼ変更なし
void PlayScene::Draw() {
    m_cameraSystem->ApplyActiveCamera();
    DrawModiGraph(0, 0, 1280, 0, 1280, 720, 0, 720, m_groundTextureHandle, TRUE);
    m_entitySystem->Draw();
    m_uiManager->DrawAll();
}

void PlayScene::SpawnEnemy() {
    float angle = Random::GetFloat(0, DX_PI_F * 2.0f);
    float distance = 60.0f;
    VECTOR spawnPos = VGet(sinf(angle) * distance, 0, cosf(angle) * distance);
    if (m_player && m_player->IsAlive()) {
        spawnPos = VAdd(m_player->GetTransform()->GetPosition(), spawnPos);
    }
    auto enemy = m_enemyPrototype->Clone(spawnPos, m_player->GetTransform());
    m_entitySystem->AddEntity(enemy);
}

void PlayScene::AddScore(int value) { m_score += value; }
void PlayScene::UpdateUI() {
    if (m_scoreText) m_scoreText->SetText(L"Score: " + std::to_wstring(m_score));
    if (m_hpText && m_player) m_hpText->SetText(L"HP: " + std::to_wstring(m_player->GetHP()));
}