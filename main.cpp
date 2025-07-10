#include <DxLib.h>
#include "Game.h"
#include "VirtualScreenManager.h"
#include "Random.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ログ出力無効化
    SetOutApplicationLogValidFlag(FALSE);

    // 仮想画面サイズ（ゲーム設計で定義）
    // NOTE: 将来的に設定ファイルなどから読み込めるようにすると、より柔軟になります。
    const int VIRTUAL_WIDTH = 1280;
    const int VIRTUAL_HEIGHT = 720;

    // ウィンドウモードに設定
    ChangeWindowMode(TRUE);

    // DxLibの初期化と画面設定
    // NOTE: DxLib_Initの前にウィンドウモードなどを設定しておく必要があります。
    SetGraphMode(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, 32);
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 3D描画のための設定
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    // 描画先をバックバッファに設定
    SetDrawScreen(DX_SCREEN_BACK);

    // 背景色
    SetBackgroundColor(0, 255, 255);

    // カメラのクリップ面設定
    SetCameraNearFar(0.01f, 1000.0f);

    // 仮想画面初期化
    VirtualScreenManager::Init(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

    // 乱数エンジンの初期化
    Random::Init();

    // Gameインスタンス生成（内部でリソース管理＆シーン初期化）
    Game game;

    // メインループ
    LONGLONG prevTime = GetNowHiPerformanceCount();
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        LONGLONG currentTime = GetNowHiPerformanceCount();
        float deltaTime = (currentTime - prevTime) / 1000000.0f; // マイクロ秒を秒に変換
        prevTime = currentTime;

        VirtualScreenManager::BeginDraw();  // 仮想画面に描画開始

        // 画面クリア（BeginDrawの後、個別の描画の前に呼ぶのが一般的）
        ClearDrawScreen();

        game.Update(deltaTime);  // ゲームロジック更新
        game.Draw();    // ゲーム描画

        VirtualScreenManager::EndDraw();    // 仮想画面の内容を実画面へ

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}