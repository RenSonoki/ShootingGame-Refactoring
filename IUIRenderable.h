#pragma once

// UI描画用インターフェース
class IUIRenderable
{
public:
    virtual ~IUIRenderable() = default;
    virtual void Draw() = 0; // 引数は不要。Rendererに任せるため。
};