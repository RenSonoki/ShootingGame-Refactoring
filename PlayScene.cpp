//#include "PlayScene.h"
//#include "Game.h"
//#include "ResourceManager.h"
//#include "UIText.h"
//#include "UIImage.h"
//#include "UISystem.h"
//#include "VirtualScreenManager.h"
//#include "CameraEntity.h"
//#include <DxLib.h>
//#include <cmath>
//
//PlayScene::PlayScene()
//{
//    std::wstring playerModelPath = L"Assets/Models/player.pmx";
//    std::wstring enemyModelPath = L"Assets/Models/enemy.mv1";
//
//    m_playerModelHandle = ResourceManager::Instance().GetModel(playerModelPath);
//    m_enemyModelHandle = ResourceManager::Instance().GetModel(enemyModelPath);
//
//    m_bulletPrototype = std::make_shared<BulletPrototype>(
//        L"Assets/Models/bullet.mv1",
//        0.3f,
//        120
//    );
//}
//
//void PlayScene::OnEnter(Game& game)
//{
//    m_bgmHandle = ResourceManager::Instance().GetSound(L"Assets/Sounds/play_bgm.mp3");
//    if (m_bgmHandle != -1) PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
//
//    m_shootSEHandle = ResourceManager::Instance().GetSound(L"Assets/SE/fire.mp3");
//    m_backgroundHandle = ResourceManager::Instance().GetImage(L"Assets/UI/background_play.png");
//    m_statusBackgroundHandle = ResourceManager::Instance().GetImage(L"Assets/UI/statusBackground.png");
//    m_groundTextureHandle = ResourceManager::Instance().GetImage(L"Assets/UI/ground.png");
//
//    m_player = std::make_shared<PlayerEntity>(
//        m_playerModelHandle,
//        &m_entitySystem,
//        m_bulletPrototype
//    );
//    m_entitySystem.AddEntity(m_player);
//
//    auto cameraEntity = std::make_shared<CameraEntity>();
//
//    auto controller = cameraEntity->GetCameraController();
//
//    controller->SetTarget(m_player->GetTransform());
//    controller->SetFPSMode(false);
//    controller->SetOffset(VGet(0.0f, 5.0f, -10.0f));  // 視界に入りやすい位置
//    controller->SetYaw(0.0f);
//    controller->SetPitch(0.0f);
//
//    m_entitySystem.AddEntity(cameraEntity);
//    m_cameraSystem.Register(cameraEntity->GetCamera(), cameraEntity->GetTransformComponent());
//    m_cameraSystem.SetActiveCamera(cameraEntity->GetCamera());
//
//    
//
//    m_enemyPrototype = std::make_shared<EnemyPrototype>(m_enemyModelHandle, m_player->GetTransform());
//    m_enemyPrototype->SetScoreCallback([this](int value) { AddScore(value); });
//
//    m_uiManager = std::make_unique<UIManager>();
//    auto mainUI = std::make_shared<UISystem>();
//
//    m_scoreText = std::make_shared<UIText>(L"Score: 0", GetColor(255, 255, 0));
//    m_scoreText->GetTransform().SetPosition({ 20, 20 });
//    mainUI->AddComponent(m_scoreText);
//
//    m_hpText = std::make_shared<UIText>(L"HP: 3", GetColor(255, 255, 255));
//    m_hpText->GetTransform().SetPosition({ 20, 50 });
//    mainUI->AddComponent(m_hpText);
//
//    m_uiManager->AddSystem("main", mainUI);
//
//    // ⭐ 重要：Entityの Start を呼び出してカメラやプレイヤーの初期化を完了させる
//    m_entitySystem.Start();
//}
//
//void PlayScene::OnExit(Game& game)
//{
//    if (m_bgmHandle != -1) {
//        StopSoundMem(m_bgmHandle);
//        DeleteSoundMem(m_bgmHandle);
//        m_bgmHandle = -1;
//    }
//}
//
//void PlayScene::Update(Game& game)
//{
//    m_entitySystem.Update();
//
//    if (CheckHitKey(KEY_INPUT_Z)) {
//        m_player->Shoot(m_bulletPrototype);
//        if (m_shootSEHandle != -1) PlaySoundMem(m_shootSEHandle, DX_PLAYTYPE_BACK);
//    }
//
//    if (++m_enemySpawnTimer > 120) {
//        m_enemySpawnTimer = 0;
//        VECTOR spawnPos = VGet((rand() % 21 - 10), 0, 80);
//        auto enemy = m_enemyPrototype->Clone(spawnPos, m_player->GetTransform());
//        m_entitySystem.AddEntity(enemy);
//    }
//
//    m_scoreText->SetText(L"Score: " + std::to_wstring(m_score));
//    m_hpText->SetText(L"HP: " + std::to_wstring(m_player->GetHP()));
//}
//
//void PlayScene::Draw()
//{
//    m_cameraSystem.ApplyActiveCamera();
//
//    int screenW = VirtualScreenManager::GetVirtualWidth();
//    int screenH = VirtualScreenManager::GetVirtualHeight();
//    DrawExtendGraph(0, 0, screenW, screenH, m_backgroundHandle, TRUE);
//    DrawExtendGraph(0, 0, 150, 150, m_statusBackgroundHandle, TRUE);
//
//    VERTEX3D v[6];
//    v[0].pos = VGet(-100, 0, -100); v[0].u = 0; v[0].v = 0;
//    v[1].pos = VGet(100, 0, -100);  v[1].u = 1; v[1].v = 0;
//    v[2].pos = VGet(100, 0, 100);   v[2].u = 1; v[2].v = 1;
//    v[3].pos = VGet(-100, 0, -100); v[3].u = 0; v[3].v = 0;
//    v[4].pos = VGet(100, 0, 100);   v[4].u = 1; v[4].v = 1;
//    v[5].pos = VGet(-100, 0, 100);  v[5].u = 0; v[5].v = 1;
//
//    for (int i = 0; i < 6; ++i) {
//        v[i].dif = GetColorU8(255, 255, 255, 255);
//        v[i].norm = VGet(0, 1, 0);
//    }
//    DrawPolygon3D(v, 6, m_groundTextureHandle, TRUE);
//
//    m_entitySystem.Draw();
//    m_uiManager->DrawAll();
//}
//
//void PlayScene::AddScore(int value)
//{
//    m_score += value;
//}