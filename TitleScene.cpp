#include "TitleScene.h"
#include "Entity.h"
#include "CameraEntity.h"
#include "SpriteComponent.h"
#include "UIButton.h"
#include "LogoAnimatorComponent.h"
#include "EntitySystem.h"
#include "UISystem.h"
#include "CameraSystem.h"
#include "Game.h"
#include "PlayScene.h"
#include "ResourceManager.h"
#include "ResourceTraits.h"
#include <DxLib.h>

TitleScene::TitleScene()
{
    m_entitySystem = std::make_unique<EntitySystem>();
    m_uiSystem = std::make_unique<UISystem>();
    m_cameraSystem = std::make_unique<CameraSystem>();

    // --- カメラエンティティを生成・登録 ---
    auto cameraEntity = std::make_shared<CameraEntity>();
    m_entitySystem->AddEntity(cameraEntity);
    m_cameraSystem->Register(cameraEntity);
    m_cameraSystem->SetActiveCamera(cameraEntity->GetCameraComponent());

    // --- ロゴエンティティを生成・登録 ---
    auto logoEntity = std::make_shared<Entity>();
    logoEntity->AddComponent(std::make_shared<SpriteComponent>(L"Assets/UI/titleLogo.png"));
    logoEntity->AddComponent(std::make_shared<LogoAnimatorComponent>(200.0f, 15.0f, 2.0f));
    m_entitySystem->AddEntity(logoEntity);
    m_uiSystem->RegisterEntity(logoEntity);

    // --- スタートボタンエンティティを生成・登録 ---
    auto buttonEntity = std::make_shared<Entity>();
    auto button = std::make_shared<UIButton>(
        L"Assets/UI/startButton_normal.png",
        L"Assets/UI/startButton_hover.png"
    );
    button->GetTransform().SetPosition({ 640, 500 });
    button->SetOnClick([this]() {
        if (m_decideSEHandle != -1) PlaySoundMem(m_decideSEHandle, DX_PLAYTYPE_BACK);
        m_isStartRequested = true;
        });
    buttonEntity->AddComponent(button);
    m_entitySystem->AddEntity(buttonEntity);
    m_uiSystem->RegisterEntity(buttonEntity);
}

TitleScene::~TitleScene() {}

void TitleScene::OnEnter(Game& game)
{
    m_bgmHandle = ResourceManager::Instance().Get<SoundTag>(L"Assets/Sounds/title_bgm.mp3");
    m_decideSEHandle = ResourceManager::Instance().Get<SoundTag>(L"Assets/Sounds/decide.mp3");
    if (m_bgmHandle != -1) PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

void TitleScene::OnExit(Game& game)
{
    if (m_bgmHandle != -1) StopSoundMem(m_bgmHandle);
}

void TitleScene::Update(float deltaTime, Game& game)
{
    m_entitySystem->Update(deltaTime);
    m_uiSystem->Update();

    if (m_isStartRequested)
    {
        game.ChangeScene(std::make_unique<PlayScene>());
    }
}

void TitleScene::Draw()
{
    int bgHandle = ResourceManager::Instance().Get<ImageTag>(L"Assets/UI/background_title.png");
    DrawGraph(0, 0, bgHandle, FALSE);

    m_cameraSystem->ApplyActiveCamera();
    m_entitySystem->Draw();
    m_uiSystem->Draw();
}