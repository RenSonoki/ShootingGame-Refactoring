#pragma once
#include "UIElement.h" // 新しい基底クラス
#include <vector>
#include <memory>

// UI要素を階層的にグループ化するためのパネルクラス
// 自身もUIElementであり、子として複数のUIElementを所有できる
class UIPanel : public UIElement
{
public:
    UIPanel();
    virtual ~UIPanel() = default;

    // 子要素を追加する（所有権もパネルに移る）
    void AddChild(std::unique_ptr<UIElement> child);

    // --- UIElementの仮想関数をオーバーライド ---

    // 自身と、全ての子要素のロジックを更新する
    void UpdateLogic() override;

    // 自身と、全ての子要素を描画する
    void Draw() override;

    // 自身と、全ての子要素の表示状態を一括で切り替える
    void SetVisible(bool visible) override;

protected:
    // パネルが所有する子要素のリスト
    std::vector<std::unique_ptr<UIElement>> m_children;
};