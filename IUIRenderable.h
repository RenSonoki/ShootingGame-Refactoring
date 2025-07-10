#pragma once

// UI描画用インターフェース
class IUIRenderable
{
public:
    virtual ~IUIRenderable() = default;
    virtual void Draw(int targetScreen = -1) = 0; // -1: DX_SCREEN_BACK など
};