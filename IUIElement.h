#pragma once

#include "IUIVisible.h"
#include "IUIRenderable.h"
#include "IUILogicUpdatable.h"
#include "IUITransformable.h"

// 必須のUI機能をまとめた統合インターフェース
// 他のものと設計思想は異なるが、階層構造を持つものには有効である
class IUIElement :
    public IUIVisible,
    public IUIRenderable,
    public IUILogicUpdatable,
    public IUITransformable
{
public:
    virtual ~IUIElement() = default;

    // 必須実装要素：表示制御・描画・ロジック更新・Transform操作
};