#pragma once

#include "Vector2I.h"
#include "Vector2F.h"
#include <DxLib.h>

class VirtualScreenManager
{
public:
	// スケーリングモードの列挙型
    enum class ScalingMode
    {
        StretchToFill,
        KeepAspect
    };

    // 初期化処理
    // NOTE: 背景色も指定できるように変更
    static void Init(int virtualW, int virtualH, ScalingMode mode = ScalingMode::KeepAspect, unsigned int backgroundColor = 0x00FFFF);

    // 描画開始（この中で画面クリアも行う）
    static void BeginDraw();

    // 描画終了と実画面への転送
    static void EndDraw();

    // 座標変換メソッド
    static Vector2I ConvertMousePositionToVirtual();
    static Vector2I ConvertVirtualToScreen(const Vector2I& virtualPos);

    // ゲッター
    static int GetVirtualWidth();
    static int GetVirtualHeight();
    static int GetVirtualScreenHandle();
    static bool IsInitialized();
    static ScalingMode GetScalingMode();

private:
    VirtualScreenManager() = delete;

    // スケーリングパラメータを更新するヘルパー関数
    static void UpdateScalingParameters();

    // 静的メンバ変数
    static int s_virtualWidth;
    static int s_virtualHeight;
    static int s_virtualScreenHandle;
    static bool s_initialized;
    static ScalingMode s_scalingMode;
    static unsigned int s_backgroundColor;

    static Vector2I s_windowSize;    // 現在のウィンドウサイズを保持
    static Vector2I s_drawOffset;    // 描画オフセット
	static Vector2F s_scaleRatio;    // XYそれぞれのスケーリング率(StretchToFillでのスケーリング率を保持する)
};