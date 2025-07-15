#define NOMINMAX
#include <windows.h>
#include <DxLib.h>

#include "Game.h"
#include "VirtualScreenManager.h"
#include "Random.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ログ出力無効化
    SetOutApplicationLogValidFlag(FALSE);

    // 仮想画面サイズ
    const int VIRTUAL_WIDTH = 1280;
    const int VIRTUAL_HEIGHT = 720;

    // ウィンドウモードに設定
    ChangeWindowMode(TRUE);

    // DxLibの初期化と画面設定
    SetGraphMode(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, 32);
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 3D描画のための設定
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    SetCameraNearFar(0.01f, 1000.0f);

    // 描画先をバックバッファに設定
    SetDrawScreen(DX_SCREEN_BACK);

    // --- 各シングルトンマネージャの初期化 ---

    // 仮想画面初期化 (GetInstance() を経由して呼び出す)
    // NOTE: 背景色はここで指定。WinMain側のSetBackgroundColorは不要。
    VirtualScreenManager::GetInstance().Init(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

    // 乱数エンジンの初期化
    // NOTE: GetInstance()が初めて呼ばれた時にコンストラクタが走り、シードが設定される
    Random::GetInstance();

    // Gameインスタンス生成
    Game game;

    // メインループ
    LONGLONG prevTime = GetNowHiPerformanceCount();
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // DeltaTimeの計算
        LONGLONG currentTime = GetNowHiPerformanceCount();
        float deltaTime = (currentTime - prevTime) / 1000000.0f;
        prevTime = currentTime;

        // --- 描画処理 ---
        // 描画の開始から終了までをVirtualScreenManagerに任せる
        VirtualScreenManager::GetInstance().BeginDraw();

        // ゲームの更新と描画
        game.Update(deltaTime);
        game.Draw();

        // 仮想画面の内容を実画面に転送
        VirtualScreenManager::GetInstance().EndDraw();

        // 実画面の内容をディスプレイに反映
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}