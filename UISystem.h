#pragma once

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "UIComponent.h"
#include "IUILogicUpdatable.h"

// 単一のUIレイヤー（例：HUD、ポーズメニュー）を管理するシステム
class UISystem
{
public:
    UISystem() = default;

    // UIコンポーネントの登録・解除
    void AddComponent(const std::shared_ptr<UIComponent>& component);
    void RemoveComponent(const std::shared_ptr<UIComponent>& component);

    // UIの更新・描画ループ
    void Update();
    void Draw(int targetScreen = -1);

    // UIコンポーネントの取得
    std::shared_ptr<UIComponent> GetComponentByName(const std::string& name) const;
    const std::vector<std::shared_ptr<UIComponent>>& GetComponents() const;

    // 全コンポーネントをクリア
    void Clear();

    // UIManagerが描画順を決定するための「レイヤー深度」を設定
    void SetLayerDepth(int depth);
    int GetLayerDepth() const;

private:
    // Zオーダーでのソートを実行（Drawの中で必要に応じて呼ばれる）
    void SortByZOrder();

    std::vector<std::shared_ptr<UIComponent>> m_components;

    // Zオーダーの再ソートが必要かを示すフラグ
    bool m_isSortNeeded = false;

    // UIManager内での描画順を決定する深度
    int m_layerDepth = 0;
};