#pragma once

#include "UIComponent.h"
#include <vector>
#include <memory>

// UIComponent を複数まとめて論理的にグループ化するためのパネル
class UIPanel : public UIComponent
{
public:
    UIPanel();
    virtual ~UIPanel() = default;

    // 子UIコンポーネントを追加
    void AddChild(const std::shared_ptr<UIComponent>& child);

    // 子要素のリストを取得（読み取り専用）
    const std::vector<std::shared_ptr<UIComponent>>& GetChildren() const;

    // パネル自身の描画処理（もしあれば）
    void Draw(int targetScreen = -1) override;

    // 表示制御（自身と、管理する子要素の表示状態を一括で切り替える）
    void SetVisible(bool visible) override;

private:
    // パネルが論理的に保持する子要素のリスト
    std::vector<std::shared_ptr<UIComponent>> m_children;
};