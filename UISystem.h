#pragma once

#include <vector>
#include <memory>
#include <string>
#include <algorithm>

// 前方宣言
class Entity;
class UIComponent;
class IUILogicUpdatable;
class IUIInteractable;

// UIComponentを持つエンティティを管理し、更新・描画・Zソートを行うシステム
class UISystem
{
public:
    UISystem() = default;

    // UIを持つエンティティの登録・解除
    void RegisterEntity(const std::shared_ptr<Entity>& entity);
    void UnregisterEntity(const std::shared_ptr<Entity>& entity);

    // 管理下の全UIコンポーネントのロジック更新
    void Update();
    // 管理下の全UIコンポーネントを描画（Zソート後）
    void Draw(int targetScreen = -1);

    // 全エンティティ（とコンポーネント）をクリア
    void Clear();

    // UIManagerが描画順を決定するための「レイヤー深度」を設定
    void SetLayerDepth(int depth);
    int GetLayerDepth() const;

private:
    // 描画順のソートを実行
    void SortComponents();
    // 管理対象のエンティティから、UIコンポーネントを再収集する
    void RefreshComponents();

    // Entityへの弱参照(weak_ptr)を保持し、所有権の循環を防ぐ
    std::vector<std::weak_ptr<Entity>> m_entities;

    // 描画や更新のためにキャッシュされたUIComponentのリスト
    std::vector<std::shared_ptr<UIComponent>> m_cachedComponents;

    // リストの再構築と再ソートが必要かを示すフラグ
    bool m_isDirty = true;

    // UIManager内での描画順を決定する深度
    int m_layerDepth = 0;
};